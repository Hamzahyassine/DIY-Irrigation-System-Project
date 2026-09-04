#include <Arduino.h>

// put function declarations here:
const int SENSOR1_PWR_PIN = 26;
const int SENSOR2_PWR_PIN = 27;
const int SENSOR1_AIN_PIN = 34;
const int SENSOR2_AIN_PIN = 35;
const int PUMP1_RELAY_PIN = 33;
const int PUMP2_RELAY_PIN = 32;
const int DRY_THRESHOLD   = 2500; // sensor is completly dry at 3150, adjust based on calibration
const int PUMP_TIME_MS    = 1000; // 1 second

void setup() {
  Serial.begin(9600);// baud rate, bits/seconds. Tells the computer how fast to talk to the ESP32. The ESP32 can talk faster than 9600, but this is a safe value that works with most computers.
  // 1. Tell the hardware which direction electricity moves
  
  pinMode(PUMP1_RELAY_PIN, OUTPUT);
  pinMode(PUMP2_RELAY_PIN, OUTPUT);
  pinMode(SENSOR1_PWR_PIN, OUTPUT);
  pinMode(SENSOR2_PWR_PIN, OUTPUT);

  // 2. Set initial safe voltages
  digitalWrite(PUMP1_RELAY_PIN, HIGH); // OFF on active-LOW relays
  digitalWrite(PUMP2_RELAY_PIN, HIGH);
  digitalWrite(SENSOR1_PWR_PIN, LOW);  // Sensors off
  digitalWrite(SENSOR2_PWR_PIN, LOW);

  
  Serial.println("Powering up...");
}

void loop() {
  // ================= PLANT 1 =================
  digitalWrite(SENSOR1_PWR_PIN, HIGH); // Power sensor 1
  delay(50);
  int sensor1Val = analogRead(SENSOR1_AIN_PIN);
  digitalWrite(SENSOR1_PWR_PIN, LOW);  // Power off sensor 1

  Serial.print("Plant 1 Moisture: ");
  Serial.println(sensor1Val);

  if (sensor1Val > DRY_THRESHOLD) {
    Serial.println("Watering Plant 1...");
    digitalWrite(PUMP1_RELAY_PIN, LOW);  // Turn pump 1 ON
    delay(PUMP_TIME_MS);
    digitalWrite(PUMP1_RELAY_PIN, HIGH); // Turn pump 1 OFF
  }

  // ================= PLANT 2 =================
  digitalWrite(SENSOR2_PWR_PIN, HIGH); // Power sensor 2
  delay(50);
  int sensor2Val = analogRead(SENSOR2_AIN_PIN);
  digitalWrite(SENSOR2_PWR_PIN, LOW);  // Power off sensor 2

  Serial.print("Plant 2 Moisture: ");
  Serial.println(sensor2Val);

  if (sensor2Val > DRY_THRESHOLD) {
    Serial.println("Watering Plant 2...");
    digitalWrite(PUMP2_RELAY_PIN, LOW);  // Turn pump 2 ON
    delay(PUMP_TIME_MS);
    digitalWrite(PUMP2_RELAY_PIN, HIGH); // Turn pump 2 OFF
  }
  Serial.println("Cycle complete. Waiting for next check...");
  Serial.println("--------------------------------------------------");
  Serial.println();
  delay(60000); // Wait 60 seconds
  Serial.println("Starting next cycle...");

}