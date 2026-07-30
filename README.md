# IoT-Based Smart Door Lock System

An IoT-inspired Smart Door Lock System developed using **Arduino Uno**, **RFID (RC522)**, and a **4×4 Matrix Keypad** to provide secure dual-factor authentication for access control. The system allows authorized users to unlock the door using either an RFID card or a password while preventing unauthorized access through audio-visual alerts.

---

# Project Overview

Traditional mechanical locks are vulnerable to key duplication, theft, and unauthorized access. This project replaces conventional locking mechanisms with a secure embedded access control system.

The system authenticates users using either:

- RFID Card (Primary Authentication)
- Password using Keypad (Backup Authentication)

After successful authentication, the servo motor unlocks the door for **5 seconds** before automatically locking it again.

Additionally, the project includes a **Master Password** feature that allows the owner to change the user password without modifying the Arduino code.

The entire system was designed and validated using **Tinkercad** and **Wokwi** simulators before hardware implementation. :contentReference[oaicite:1]{index=1}

---

# Features

- RFID-based authentication
- Password-based authentication
- Dual authentication mechanism
- Master password for password reset
- Automatic door locking after 5 seconds
- Servo motor door locking mechanism
- Green LED for successful authentication
- Red LED for unauthorized access
- Buzzer alarm for invalid authentication
- Simulation using Tinkercad and Wokwi

---

# Hardware Components

| Component | Quantity |
|-----------|---------:|
| Arduino Uno | 1 |
| RC522 RFID Reader | 1 |
| RFID Cards | 2 |
| 4×4 Matrix Keypad | 1 |
| Servo Motor | 1 |
| Red LED | 1 |
| Green LED | 1 |
| Buzzer | 1 |
| Breadboard | 1 |
| Jumper Wires | As Required |

---

# Software Used

- Arduino IDE
- Wokwi Simulator
- Git
- GitHub

---

# Repository Structure

```
IoT-Based-Smart-Door-Lock
│
├── Code
│   └── smart_door_lock.ino
│
├── Circuit_Diagram
│   └── circuit_diagram.png
│
├── Simulation
│   └── simulation.mp4
│
├── Test_Cases
│   └── Test_Cases.pdf
│
├── Report
│   └── College_Report.pdf
│
└── README.md
```

---

# Circuit Diagram

The complete circuit diagram is available in:

```
Circuit_Diagram/Project Circuit.png
```

The circuit consists of:

- Arduino Uno
- RC522 RFID Reader
- 4×4 Matrix Keypad
- Servo Motor
- Buzzer
- Red LED
- Green LED

---

# Working Principle

1. The user scans an RFID card or enters a password using the keypad.
2. Arduino verifies the entered credentials.
3. If authentication is successful:
   - Green LED turns ON.
   - Servo motor unlocks the door.
   - Door remains unlocked for **5 seconds**.
   - Door locks automatically.
4. If authentication fails:
   - Red LED turns ON.
   - Buzzer sounds.
5. The owner can enter the Master Password to update the user password without modifying the program. :contentReference[oaicite:2]{index=2}

---

#  Test Cases

The project has been validated through multiple test scenarios.

| Test Case | Result |
|-----------|--------|
| Authorized RFID Access | ✅ Pass |
| Authorized Keypad Access | ✅ Pass |
| Wrong Password | ✅ Pass |
| Unauthorized RFID Card | ✅ Pass |
| Password Reset | ✅ Pass |
| Login Using New Password | ✅ Pass |
| Login Using Old Password | ✅ Pass |

All test cases passed successfully. :contentReference[oaicite:3]{index=3}

---

# Simulation

The simulation demonstrates:

- RFID Authentication
- Password Authentication
- Wrong Password Detection
- Unauthorized RFID Detection
- Password Reset
- Automatic Door Locking
- Servo Motor Operation
- LED Status Indication
- Buzzer Alarm

The simulation video is available inside:

```
Simulation/Project Simulation.mp4
```

---

# Applications

- Smart Home Security
- Office Access Control
- Hostel & PG Security
- Locker Security
- Laboratory Access Control
- Restricted Area Entry Systems

---

# Advantages

- Dual authentication mechanism
- Improved security over traditional locks
- Contactless RFID access
- Automatic door locking
- Password reset without code modification
- Easy to upgrade for IoT deployment

---

# Limitations

- Simulation-based implementation
- Supports a single authorized RFID UID
- No cloud database integration
- No mobile application support

---

# Future Improvements

- ESP32 Wi-Fi Integration
- Blynk Mobile App
- Fingerprint Sensor
- Face Recognition
- Multiple RFID Users
- Cloud Database
- Access Logs
- OTP Verification
- Remote Door Unlock
- Smart Home Integration

---

# Documentation

Detailed project documentation is available in:

```
Report/IOT Project Report (1).pdf
```

---

# Author

**Gaurav Kumar**

B.Tech Electrical Engineering

Delhi Technological University (DTU)

---

## If you found this project useful, please consider giving it a Star.
