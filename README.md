<div align="center">

# 🕒 ESP32 Smart LED Matrix Clock

### Professional Wi-Fi Enabled LED Matrix Clock with Web Dashboard, NTP Time Sync & Live Message Display

NTP Clock • MAX7219 LED Matrix • Web Dashboard • DHT11 Temperature • Live Quote Update • ESP32

<p align="center">

![ESP32](https://img.shields.io/badge/ESP32-ESPRESSIF-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![MAX7219](https://img.shields.io/badge/MAX7219-LED_Matrix-success?style=for-the-badge)
![WiFi](https://img.shields.io/badge/WiFi-NTP_Clock-blue?style=for-the-badge)
![Dashboard](https://img.shields.io/badge/Web-Dashboard-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</p>

### 🌐 Smart Wi-Fi LED Matrix Information Display with Beautiful Web Dashboard

</div>

---

# 📸 Project Preview

<p align="center">

---

# 📖 Project Overview

The **ESP32 Smart LED Matrix Clock** is an advanced Embedded IoT project that combines a **MAX7219 LED Matrix Display**, **ESP32 Wi-Fi**, **NTP Internet Clock**, **DHT11 Temperature Sensor**, and a **Responsive Web Dashboard** into one smart information display system.

Once connected to Wi-Fi, the ESP32 automatically synchronizes time from an NTP server and continuously displays:

- 🕒 Current Time
- 📅 Date
- 📆 Day
- 🌡 Temperature
- 😊 Dynamic Greeting
- 💬 Custom Scrolling Quote
- 📶 Wi-Fi Status

The built-in web dashboard allows users to update the scrolling message directly from any web browser without reprogramming the ESP32.

---

# ✨ Features

✔ Automatic NTP Time Synchronization

✔ Offline Time Backup

✔ 12-Hour Digital Clock

✔ Current Date Display

✔ Day Display

✔ Smart Greeting (Morning / Afternoon / Evening)

✔ DHT11 Temperature Display

✔ Wi-Fi Status

✔ Beautiful Responsive Dashboard

✔ Live Quote Update

✔ LED Matrix Live Preview

✔ Browser Clock

✔ Mobile Friendly UI

✔ Dynamic Message Queue

✔ Smooth Scrolling Animation

✔ Non-Blocking Programming

✔ Fully Modular Code

---

# 🌐 Web Dashboard

The project includes a modern responsive dashboard hosted directly on the ESP32.

### Dashboard Features

- 🏠 Home Screen
- 📶 Wi-Fi Status
- 🌡 Live Temperature
- 🕒 Browser Clock
- 📺 LED Matrix Preview
- 💬 Update Scrolling Quote
- ⚙ Settings Page (Expandable)

---

# 🏗 System Architecture

```text
               Wi-Fi Router
                    │
                    ▼
               ESP32 Board
                    │
     ┌──────────────┼──────────────┐
     │              │              │
     ▼              ▼              ▼
 MAX7219 LED      DHT11        Web Dashboard
    Matrix      Temperature      (Browser)
     │
     ▼
Scrolling Messages
```

---

# 🛠 Hardware Required

| Component | Quantity |
|-----------|:--------:|
| ESP32 Dev Board | 1 |
| MAX7219 8×8 Matrix Module | 4 |
| DHT11 Sensor | 1 |
| Breadboard | 1 |
| Jumper Wires | As Required |
| USB Cable | 1 |

---

# 🔌 Wiring Diagram

| MAX7219 | ESP32 |
|----------|-------|
| VCC | VIN (5V) |
| GND | GND |
| DIN | GPIO23 |
| CS | GPIO5 |
| CLK | GPIO18 |

---

### DHT11

| DHT11 | ESP32 |
|--------|-------|
| DATA | GPIO4 |
| VCC | 3.3V |
| GND | GND |

---

# 📂 Project Structure

```text
ESP32_LED_MATRIX_CLOCK
│
├── ESP32_LED_MATRIX_CLOCK.ino
├── images
│   ├── dashboard.png
│   ├── matrix.jpg
│   ├── circuit.png
│   ├── demo.gif
│   └── mobile.png
│
├── README.md
└── LICENSE
```

---

# 📚 Required Libraries

Install the following libraries using Arduino Library Manager.

- WiFi
- WiFiUDP
- NTPClient
- TimeLib
- MD_MAX72XX
- MD_Parola
- SPI
- DHT Sensor Library
- WebServer

---

# 🚀 Getting Started

## Clone Repository

```bash
git clone https://github.com/Surya-8948/ESP32-LED-Matrix-Clock.git
```

---

## Open Arduino IDE

```
ESP32_LED_MATRIX_CLOCK.ino
```

---

## Install ESP32 Board

```
Boards Manager

↓

ESP32 by Espressif Systems
```

---

## Install Libraries

Use Arduino Library Manager and install all required libraries.

---

## Configure Wi-Fi

```cpp
char ssid[] = "YOUR_WIFI";
char pass[] = "YOUR_PASSWORD";
```

---

## Upload Code

Select

```
ESP32 Dev Module
```

Compile and Upload.

---

# 🌐 Web Dashboard

After connecting to Wi-Fi, open:

```
http://ESP32_IP_ADDRESS
```

Example

```
http://192.168.1.105
```

---

# 💬 Dynamic Quote Update

Open Dashboard

↓

Go to **Quote Tab**

↓

Type Your Message

↓

Click

```
Update Quote
```

The LED Matrix immediately starts displaying the new scrolling text.

---

# 📺 Display Sequence

The LED Matrix continuously displays:

```
✔ Good Morning

✔ Current Time

✔ Date

✔ Day

✔ Temperature

✔ Custom Quote

✔ Wi-Fi Status
```

---

# 📚 Concepts Covered

- ESP32 Programming
- Wi-Fi Networking
- Embedded Web Server
- HTML
- CSS
- JavaScript
- MAX7219 Matrix Display
- MD_Parola Animations
- NTP Clock
- Time Synchronization
- DHT11 Sensor
- SPI Communication
- Dynamic Web UI
- Non-Blocking Programming
- Embedded IoT

---

# 🎯 Learning Outcomes

After completing this project, you will learn:

- ESP32 Programming
- Wi-Fi Communication
- Web Dashboard Development
- HTML/CSS UI Design
- NTP Time Synchronization
- LED Matrix Programming
- MD_Parola Animations
- Sensor Interfacing
- Embedded Web Server
- Embedded IoT Application Design

---

# 💡 Applications

- Smart Office Display
- Digital Notice Board
- College Information Board
- Reception Display
- Smart Classroom
- Home Automation
- IoT Dashboard
- Industrial Information Display
- Smart Factory
- Smart Clock

---

# 🚀 Future Improvements

- 🌤 Weather API
- 📈 Stock Market Display
- 📰 Live News Headlines
- 🎂 Birthday Reminder
- 🎉 Festival Greetings
- 📅 Google Calendar Sync
- 📧 Email Notification
- 📲 Telegram Bot
- 📡 MQTT Support
- ☁ Firebase Integration
- 📱 Android App
- 🎙 Voice Commands

---

# ⭐ Support

If you found this project useful,

please consider giving this repository a ⭐ **Star**.

Your support motivates me to create more professional **ESP32**, **Embedded Systems**, **IoT**, **STM32**, and **FreeRTOS** projects.

### GitHub

https://github.com/Surya-8948

---

# 📜 License

This project is licensed under the **MIT License**.

Feel free to use, modify, and distribute this project for educational and personal purposes.

---

<div align="center">

## ⭐ If you found this project helpful, please Star ⭐ the repository!

### Made with ❤️ by **Surya Mani Bajpai**

### 🚀 Turning Embedded Ideas into Smart IoT Solutions

</div>
