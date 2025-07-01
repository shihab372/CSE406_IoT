# 💧 Water Level Detection with Arduino

This project demonstrates how to interface a **water level sensor** with an **Arduino UNO** to detect the water level in a container and indicate the status using **LEDs**. It’s a basic but practical system for tank monitoring, irrigation, or flood detection applications.

---

## 🔧 Components Used

- Arduino UNO  
- Analog Water Level Sensor Module  
- 3 LEDs (Red, Yellow, Green)  
- 3 × 220Ω Resistors  
- Breadboard & Jumper Wires  
- USB Cable  
- Water Container  

---

## 🖥️ Pin Connections

| Component      | Arduino Pin         |
|----------------|---------------------|
| Sensor VCC     | D7 (Digital Output) |
| Sensor GND     | GND                 |
| Sensor Signal  | A0 (Analog Input)   |
| Red LED        | D2                  |
| Yellow LED     | D3                  |
| Green LED      | D4                  |

---

## 🚦 LED Indication Logic

| Water Level | Sensor Value | LED ON     |
|-------------|--------------|------------|
| Empty       | 0            | (No LED)   |
| Low         | 1 – 200      | 🟢 Green   |
| Medium      | 201 – 400    | 🟡 Yellow  |
| High        | 401+         | 🔴 Red     |

---

## 🧠 Code Overview

The Arduino reads analog values from the water level sensor and powers the sensor briefly during each reading to reduce corrosion. Based on the sensor value, the Arduino lights up a specific LED to indicate whether the water level is low, medium, or high. If the sensor reads zero, no LEDs will turn on to indicate an empty tank. The reading is also printed on the Serial Monitor for real-time debugging.

---

## 🎥 Demo Video

▶️ [Click here to watch the demo video](https://youtu.be/36NUGwWR_ZU )


---

## 🖼️ Image

![Setup Image](https://github.com/shihab372/CSE406_IoT/blob/main/Lab2/initial%20setup.jpg)

---

## 📊 Sensor Value Table

| Water Level | Sensor Reading |
|-------------|----------------|
| Low         | 1 – 200        |
| Medium      | 201 – 400      |
| High        | 401+           |

---

## 🧑‍🎓 Author

**MD Shahrukh Hossain Shihab**  
ID: 2022-1-60-372  
Course: CSE406 - Embedded Systems  
Semester: Summer 2025
