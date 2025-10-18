# Smart Posture Monitoring System

## Project Overview
This project is a wearable device that monitors the user’s posture using motion sensing and provides instant feedback through a buzzer when poor posture is detected.  
It aims to help users maintain a healthy posture and prevent back or neck pain caused by prolonged incorrect sitting.

## Objectives
- Detect incorrect sitting or standing posture in real time.  
- Alert the user immediately using a buzzer sound.  
- Encourage long-term improvement in posture habits.  
- Keep the system low-cost, simple, and portable.

## Components Used
- **Arduino Uno** – main controller for reading and processing sensor data  
- **MPU6050** – 6-axis accelerometer and gyroscope for tilt detection  
- **Buzzer** – provides audio alert when posture deviates from the correct position  
- **Battery / USB Power Supply** – powers the device  

## Working Principle
1. The **MPU6050** continuously measures the tilt angles of the user’s back.  
2. The Arduino calculates the orientation and checks if it exceeds a preset threshold.  
3. If incorrect posture is detected (forward, backward, left, or right), the **buzzer** activates to alert the user.  
4. When the user corrects their posture, the buzzer stops automatically.

## Features
- Detects posture deviation in four directions (forward, backward, left, right).  
- Simple audio alert through a buzzer.  
- Adjustable sensitivity (angle threshold).  
- Compact and low power consumption.  
- Easy to wear or mount on the back or shoulder.

## Future Improvements
- Replace buzzer alerts with **voice or vibration feedback**.  
- Add **Bluetooth connectivity** to send posture data to a mobile app.  
- Include **logging features** to track posture data over time.  

## 🧠 Conclusion
The **Smart Posture Monitoring System** provides a practical and affordable way to improve posture awareness.  
By combining a motion sensor and a simple buzzer alert, it offers an immediate and effective reminder to maintain correct posture during daily activities.
