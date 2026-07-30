#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <Servo.h>

// -------- RFID (RC522) --------
#define SS_PIN 10   // SDA
#define RST_PIN 9   // RST
MFRC522 rfid(SS_PIN, RST_PIN);

// -------- SERVO --------
Servo lockServo;
const int servoPin = 6;

// -------- OUTPUTS --------
const int greenLED = A4;
const int redLED   = A5;
const int buzzer   = 7;

// -------- KEYPAD --------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {A0, A1, A2, A3};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// -------- PASSWORDS --------
String masterPassword = "9999";   // Owner password
String userPassword   = "2580";   // Default user password
String enteredInput   = "";

// -------- SYSTEM STATES --------
enum State { NORMAL, SET_PASSWORD };
State currentState = NORMAL;

// -------- AUTO LOCK --------
unsigned long unlockTime = 0;
const unsigned long autoLockDelay = 5000; // 5 seconds
bool doorUnlocked = false;

// -------- AUTHORIZED RFID UID --------
// 1) Run once, scan card, copy UID from Serial Monitor
// 2) Paste it here (uppercase, no spaces)
String allowedUID = "01020304";  // 🔁 CHANGE THIS AFTER FIRST SCAN

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lockServo.attach(servoPin);
  lockServo.write(0); // LOCKED

  Serial.println("Smart Lock Ready");
  Serial.println("Scan RFID or Enter Password");
}

void unlockDoor() {
  Serial.println("ACCESS GRANTED");
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);

  lockServo.write(90);   // UNLOCK
  unlockTime = millis();
  doorUnlocked = true;
}

void lockDoor() {
  lockServo.write(0);    // LOCK
  digitalWrite(greenLED, LOW);
  doorUnlocked = false;
  Serial.println("Door Auto-Locked");
}

void accessDenied() {
  Serial.println("ACCESS DENIED");
  digitalWrite(redLED, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(1500);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);
}

void handleKeypad() {
  char key = keypad.getKey();
  if (!key) return;

  Serial.print("Key: ");
  Serial.println(key);

  if (key == '*') {
    enteredInput = "";
    Serial.println("Input Cleared");
    return;
  }

  if (key == '#') {
    if (currentState == NORMAL) {
      if (enteredInput == masterPassword) {
        Serial.println("MASTER VERIFIED");
        Serial.println("Enter New Password");
        currentState = SET_PASSWORD;
      } 
      else if (enteredInput == userPassword) {
        unlockDoor();
      } 
      else {
        accessDenied();
      }
    } 
    else if (currentState == SET_PASSWORD) {
      userPassword = enteredInput;
      Serial.println("PASSWORD UPDATED");
      currentState = NORMAL;
    }
    enteredInput = "";
  } 
  else {
    enteredInput += key;
  }
}

void handleRFID() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  String uidStr = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uidStr += "0";
    uidStr += String(rfid.uid.uidByte[i], HEX);
  }
  uidStr.toUpperCase();

  Serial.print("RFID UID: ");
  Serial.println(uidStr);

  if (uidStr == allowedUID) {
    unlockDoor();
  } else {
    accessDenied();
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void loop() {
  handleKeypad();
  handleRFID();

  if (doorUnlocked && (millis() - unlockTime >= autoLockDelay)) {
    lockDoor();
  }
}
