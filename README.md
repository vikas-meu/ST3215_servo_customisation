# ST3215 Smart Servo Toolkit (ESP32 + Waveshare)

A complete toolkit for working with **ST3215** servos using **ESP32** and the Waveshare serial bus servo driver.

This repository helps you:

✅ Detect servo IDs
✅ Change servo IDs permanently
✅ Set mechanical motion limits in EEPROM
✅ Read saved servo limits
✅ Build robotic arms, grippers, actuators, and precision mechanisms safely

---

# Hardware Required

## Main Components

* **ESP32**
* **ST3215**
* Waveshare Serial Bus Servo Driver
* External Servo Power Supply (recommended 12V)
* USB cable for programming

---

# Wiring

Connect your ESP32 to the Waveshare driver:

| ESP32  | Waveshare Driver |
| ------ | ---------------- |
| GPIO16 | RX               |
| GPIO17 | TX               |
| GND    | GND              |

⚠ Always power the servo using an external supply.

Do **not** power the servo directly from the ESP32.

---

# Software Setup

Install **Arduino IDE**

Install required library:

### SCServo Library

Install:

**SCServo.h**

inside Arduino Library Manager or manually.

---

# Repository Structure

```bash
.
├── 01_Servo_ID_Scanner
├── 02_Servo_ID_Change
├── 03_Servo_EEPROM_Limit_Setup
└── README.md
```

---

# STEP 1 — Detect Servo ID

Before doing anything, detect the servo ID.

Upload:

```bash
01_Servo_ID_Scanner
```

Then open:

### Serial Monitor

Settings:

```text
Baud Rate = 115200
Line Ending = No line ending
```

You will see:

```text
Scanning for ST3215 servo IDs...
Servo Found! ID = 1 | Position = 2048
```

Example:

If you see:

```text
ID = 1
```

your servo currently uses ID 1.

---

# STEP 2 — Change Servo ID

If you want to change the servo ID permanently:

Upload:

```bash
02_Servo_ID_Change
```

Example in code:

```cpp
Old ID = 1
New ID = 3
```

Then open Serial Monitor.

Expected output:

```text
Changing servo ID...
Done!
Servo ID changed from 1 to 3
```

Now power-cycle the servo.

Run scanner again to verify.

Expected:

```text
Servo Found! ID = 3
```

Your ID is now permanently stored in EEPROM.

---

# STEP 3 — Set Servo Motion Limits

Now set the mechanical limits of your servo.

Upload:

```bash
03_Servo_EEPROM_Limit_Setup
```

Then open:

### Serial Monitor

Settings:

```text
115200 baud
No line ending
```

You will see:

```text
===== ST3215 EEPROM LIMIT SETUP =====

L = Save current position as LOWEST limit
H = Save current position as HIGHEST limit
R = Read saved limits
```

---

## Setting Minimum Limit

### Step 1

Rotate/move the servo manually to your desired minimum mechanical position.

### Step 2

Type:

```text
L
```

Press send.

Expected output:

```text
Minimum limit saved = 650
```

Now the minimum limit is permanently stored.

---

## Setting Maximum Limit

### Step 1

Move the servo to your desired maximum position.

### Step 2

Type:

```text
H
```

Press send.

Expected output:

```text
Maximum limit saved = 3200
```

Now the maximum limit is permanently stored.

---

## Verify Saved Limits

Type:

```text
R
```

Press send.

Expected output:

```text
Saved Min = 650
Saved Max = 3200
```

These values are stored inside the servo EEPROM.

---

# What Happens After Saving?

After calibration:

Servo motion becomes limited to:

\text{Min Limit} \leq \text{Servo Position} \leq \text{Max Limit}

This means:

✅ Power OFF → ON → values remain
✅ Upload new code → values remain
✅ Use another controller → values remain

Only changing EEPROM again will overwrite them.

---

# Serial Monitor Commands

| Command | Function                         |
| ------- | -------------------------------- |
| L       | Save current position as minimum |
| H       | Save current position as maximum |
| R       | Read saved limits                |

---

# Troubleshooting

## Servo Not Detected

Check:

### Power

Make sure external servo power is connected.

### Wiring

Verify:

* TX ↔ RX
* RX ↔ TX
* GND ↔ GND

### Baud Rate

ST3215 default baud:

```text
1000000
```

---

# Applications

This project can be used for:

* Robotic arms
* Prosthetic hands
* Linear actuators
* Rehabilitation devices
* CNC automation
* Precision motion systems

---

# Author

**Vikas Singh Thakur**

Robotics | Embedded Systems | Computer Vision | Human-Robot Interaction

---

# License

MIT License

Third-party libraries such as **SCServo** retain their original licenses.

---

This structure makes it much easier for others to reproduce your setup from scratch.
