#include <WiFi.h>
#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESPAsyncWebServer.h>
#include "secrets.h" 
#include "html.h" // Include the HTML content for the web page

unsigned long lastCheckTime = 0;


// put function declarations here:
const int SENSOR1_PWR_PIN = 26;
const int SENSOR2_PWR_PIN = 27;
const int SENSOR1_AIN_PIN = 34;
const int SENSOR2_AIN_PIN = 35;
const int PUMP1_RELAY_PIN = 33;
const int PUMP2_RELAY_PIN = 32;
const int DRY_THRESHOLD   = 2500; // sensor is completely dry at 3150, adjust based on calibration
const int PUMP_TIME_MS    = 1000; // 1 second
void logMessage(const String& message) {//helper function to log messages to both Serial and WebSocket clients
  Serial.println(message);
  ws.textAll(message); // Send the message to all connected WebSocket clients
}
#include "OTA_setup.h" // Include the OTA setup header


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
  logMessage("Pump relays initialized to HIGH.");
  digitalWrite(SENSOR1_PWR_PIN, LOW);  // Sensors off
  digitalWrite(SENSOR2_PWR_PIN, LOW);

  
  logMessage("Powering up...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    logMessage("Connecting to WiFi...");
  }
  logMessage("Connected to WiFi!");
  //Serial.print("IP Address: ");
  logMessage("IP Address: " + WiFi.localIP().toString());

  
  setupOTACallbacks(); // Initialize OTA callbacks
  ArduinoOTA.begin();// Start OTA (ON THE AIR) service, WIFI based firmware update feature.
  // 1. Attach the WebSocket endpoint to the server
  logMessage("OTA service started.");
  server.addHandler(&ws);

  // 2. Serve the webpage when someone visits the ESP32's IP address
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send_P(200, "text/html", index_html);
});

// 3. Start the web server listening
server.begin();

}



void loop() {

  ArduinoOTA.handle();// chekk for OTA updates on wifi network
  if (millis() - lastCheckTime >= 60000){// check if 60 seconds have passed since last check while looping
    lastCheckTime = millis();
    
    // ================= PLANT 1 =================
    digitalWrite(SENSOR1_PWR_PIN, HIGH); // Power sensor 1
    delay(50);
    int sensor1Val = analogRead(SENSOR1_AIN_PIN);
    digitalWrite(SENSOR1_PWR_PIN, LOW);  // Power off sensor 1

    //Serial.print("Plant 1 Moisture: ");
    logMessage("Plant 1 Moisture: " + String(sensor1Val));
    if (sensor1Val > DRY_THRESHOLD) {
      logMessage("Watering Plant 1...");
      digitalWrite(PUMP1_RELAY_PIN, LOW);  // Turn pump 1 ON
      delay(PUMP_TIME_MS);
      digitalWrite(PUMP1_RELAY_PIN, HIGH); // Turn pump 1 OFF
    
    }
       // ================= PLANT 2 =================
    digitalWrite(SENSOR2_PWR_PIN, HIGH); // Power sensor 2
    delay(50);
    int sensor2Val = analogRead(SENSOR2_AIN_PIN);
    digitalWrite(SENSOR2_PWR_PIN, LOW);  // Power off sensor 2

    //Serial.print("Plant 2 Moisture: ");
    logMessage("Plant 2 Moisture: " + String(sensor2Val));
    if (sensor2Val > DRY_THRESHOLD) {
      logMessage("Watering Plant 2...");
      digitalWrite(PUMP2_RELAY_PIN, LOW);  // Turn pump 2 ON
      delay(PUMP_TIME_MS);
      digitalWrite(PUMP2_RELAY_PIN, HIGH); // Turn pump 2 OFF
    }
  
  logMessage("Cycle complete. Waiting for next check...");
  logMessage("--------------------------------------------------");
  logMessage("Next check in 60 seconds...");
  logMessage("Starting next cycle...");

  }


 

 



}