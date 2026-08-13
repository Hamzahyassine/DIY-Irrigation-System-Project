# DIY Irrigation System

An automated plant watering system powered by an Arduino Uno. The system reads soil moisture levels to intelligently deliver water via a 5V mini pump, preventing both over-watering and dry soil.

## 🛠️ Components Used
* **Microcontroller:** Arduino Uno R3
* **Sensor:** Capacitive Soil Moisture Sensor
* **Actuator:** 5V Submersible Water Pump via Relay Module
* **Power Supply:** Independent battery power for the pump and USB supply for the Arduino

## ⚙️ Logic & Operation
1. Reads moisture sensor data at scheduled intervals.
2. If soil is dry, activates the pump for a designated pulse duration.
3. Allows water to soak before taking subsequent readings.
4. Pauses monitoring for 12 hours once target moisture is achieved.

## Future upgrades
**DS3231 RTC Module:** Integrate a Real-Time Clock (RTC) module to replace simple software delays, enabling precise schedule timing and wake-up alarms.
**Deep Sleep Power Optimization:** Implement AVR low-power sleep modes triggered by hardware interrupts from the DS3231 to maximize battery life.
**HC-SR04 Ultrasonic Sensor:** Add a sound wave/distance sensor inside the reservoir to monitor water levels in real time and alert when the tank needs a refill.

## 👎🐞 Known issues & troubleshooting
**Unexpected Resets/Crashes:** Switching the relay and water pump occasionally causes a voltage dip or inductive kickback (flyback voltage), causing the Arduino Uno to brown out and restart. 
  * *Planned Fix:* Add a flyback diode (e.g., 1N4007) across the pump terminals and a decoupling capacitor across the power rails to smooth out voltage spikes.
