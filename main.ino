// Pin Definitions
const int SENSOR_POWER_PIN = 8; // Powers the soil sensor
const int SENSOR_READ_PIN  = A0; // Reads the sensor voltage
const int RELAY_PIN        = 7;  // Controls the water pump relay

const int DRY_THRESHOLD    = 600; // Moisture threshold
const int PUMP_TIME_MS     = 500; // Pump run time (1 second)
const int DELAY_TIME       =60000; // 60 seconds

void setup() {
  pinMode(SENSOR_POWER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  // Ensure components start turned OFF
  digitalWrite(SENSOR_POWER_PIN, LOW);
  digitalWrite(RELAY_PIN, HIGH); // Active LOW relay: HIGH is OFF
  
  Serial.begin(9600);
  delay(500); // Allow serial line to stabilize
  
  // If you see this printed multiple times repeatedly, your Arduino is resetting!
  Serial.println("========================================");
  Serial.println("  Automated Irrigation System Online!   ");
  Serial.println("========================================");
  //delay(20000);// This is a temporary fix for the bug where the system crashes and restarts from the beginnning, and to avoid double watering, I srill place the delay time her.
}

void loop() {
  // 1. Power on sensor
  digitalWrite(SENSOR_POWER_PIN, HIGH);
  delay(50); // Allow voltage to settle

  // 2. Read and average multiple samples to filter noise
  int rawSum = 0;
  for (int i = 0; i < 5; i++) {
    rawSum += analogRead(SENSOR_READ_PIN);
    delay(10);
  }
  int avgValue = rawSum / 5;
  
  // 3. Power off sensor to prevent corrosion
  digitalWrite(SENSOR_POWER_PIN, LOW);

  // 4. Print value
  Serial.print("Filtered Soil Reading: ");
  Serial.print(avgValue);

  // 5. Decision Logic
  if (avgValue > DRY_THRESHOLD) {
    Serial.println(" --> [ DRY SOIL! Turning Pump ON 💧 ]");
    digitalWrite(RELAY_PIN, LOW);  // Turn pump ON
    delay(PUMP_TIME_MS);           // Keep pump ON for 1 full second
    digitalWrite(RELAY_PIN, HIGH); // Turn pump OFF
  } else {
    Serial.println(" --> [ SOIL MOIST. Pump OFF 🛑 ]");
    digitalWrite(RELAY_PIN, HIGH);  // Ensure pump stays OFF
    delay(43200000UL);// if soil is moist sleep for 12 hrs
  }

  // 6. Pause before next check (e.g., 30 seconds)
  Serial.print("waiting ");
  Serial.print(DELAY_TIME/1000);
  Serial.println(" s");
  //delay(12UL * 60UL * 60UL * 1000UL);// delay for 12 hrs
  delay(DELAY_TIME);

}
