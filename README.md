# VAF Device

 **VAF (Verification and Attendance using Fingerprint)** is a life-saving biometric authentication device designed for rapid identification of accident victims in emergency medical situations. The core objective of VAF is to provide **immediate access to critical patient information** such as **name, age, blood group, and emergency contact number** using fingerprint recognition — especially in scenarios where the victim is unconscious and unable to communicate.

---

## 🎯 Real-World Purpose

In many road accidents or medical emergencies, time becomes the most crucial factor. Often, by the time a victim is transported to the hospital, **precious minutes are lost** due to:
- Lack of access to the victim’s **blood group** for urgent transfusions  
- Inability to contact **family or emergency contacts**  
- No knowledge of the victim’s **age or medical history**

To solve this, the **VAF device is installed in ambulances** and acts as a **portable, lightweight, and energy-efficient biometric reader**. When a victim’s fingerprint is scanned:
- The device retrieves their essential medical and identification data instantly
- This helps paramedics begin **treatment en route**, alert **family members**, and **prepare hospitals** in advance

This not only increases the chance of survival but also brings structure and urgency to emergency response systems.

---

## ✅ Key Features

-  Fingerprint-based identity retrieval  
-  Real-time LCD display with scan results  
-  Emergency contact info fetch  
-  Blood group and age access for quick treatment  
-  Designed for ambulance integration (portable, low power)  
-  MongoDB backend for secure and scalable patient data storage  

---

## 🛠️ Hardware Components

| Component                | Purpose                             |
|--------------------------|-------------------------------------|
| Arduino UNO              | Microcontroller base                |
| Adafruit Fingerprint Sensor | Captures and matches fingerprints  |
| 16x2 I2C LCD Display     | Shows patient information and system messages |
| 4x4 Matrix Keypad        | User input for enrolling/printing   |
| Jumper Wires             | Wiring and interfacing              |
| Power Bank / Battery     | For portable power supply           |

---

## ⚙️ Installation & Usage

###  Hardware Setup
1. Connect the fingerprint sensor to Arduino via SoftwareSerial pins (2, 3).
2. Connect the 16x2 I2C LCD to SDA/SCL (A4, A5 on Arduino UNO).
3. Connect the matrix keypad to digital pins 5–12.
4. Power the system via USB or portable battery.

###  Software Setup
1. Install Arduino IDE.
2. Add required libraries:
   - Adafruit Fingerprint Sensor Library
   - Keypad
   - LiquidCrystal_I2C
3. Upload the Arduino `.ino` code provided below.
4. Run the Node.js script to set up the MongoDB patient records.

---


