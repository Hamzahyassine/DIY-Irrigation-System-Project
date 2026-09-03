#include <Arduino.h>

// put function declarations here:
const int SENSOR1_PWR_PIN = 3;
const int SENSOR2_PWR_PIN = 4;
const int SENSOR1_AIN_PIN = A0;
const int SENSOR2_AIN_PIN = A1;
const int PUMP1_RELAY_PIN = 8;
const int PUMP2_RELAY_PIN = 7;
const int DRY_THRESHOLD   = 300;
const int PUMP_TIME_MS    = 1000; // 1 second

void setup() {
  // 1. Tell the hardware which direction electricity moves
  Serial.println("Starting up...");
  pinMode(PUMP1_RELAY_PIN, OUTPUT);
  pinMode(PUMP2_RELAY_PIN, OUTPUT);
  pinMode(SENSOR1_PWR_PIN, OUTPUT);
  pinMode(SENSOR2_PWR_PIN, OUTPUT);

  // 2. Set initial safe voltages
  digitalWrite(PUMP1_RELAY_PIN, HIGH); // OFF on active-LOW relays
  digitalWrite(PUMP2_RELAY_PIN, HIGH);
  digitalWrite(SENSOR1_PWR_PIN, LOW);  // Sensors off
  digitalWrite(SENSOR2_PWR_PIN, LOW);

  Serial.begin(9600);
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
    Serial.println("Turning pump1 on");
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
    Serial.println("Turning pump2 on");
    digitalWrite(PUMP2_RELAY_PIN, LOW);  // Turn pump 2 ON
    delay(PUMP_TIME_MS);
    digitalWrite(PUMP2_RELAY_PIN, HIGH); // Turn pump 2 OFF
  }

  delay(60000); // Wait 60 seconds
}