#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AM2320.h>
#include "Credentials.h" // Include the credentials header file

// AM2320 sensor
Adafruit_AM2320 am2320 = Adafruit_AM2320();

void setup() {
  Serial.begin(115200);

  delay(3000);

  // Connect to Wi-Fi using credentials from Credentials.h
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (!am2320.begin()) {
    Serial.println("Failed to find AM2320 sensor!");
    while (1);
  }
}

void loop() {
  // Read from AM2320 sensor
  float humidity = am2320.readHumidity();
  float temperature = am2320.readTemperature();

  // Prepare the message
  String msg = String("The current temperature is ") + temperature + "C and the humidity is " + humidity + "%.";

  // Send to WhatsApp
  sendWhatsAppMessage(msg);
  
  // Wait for 60 seconds before sending the next message
  delay(60000);
}

void sendWhatsAppMessage(String message) {
  HTTPClient http;
  http.begin("https://api.twilio.com/2010-04-01/Accounts/" + String(account_sid) + "/Messages.json");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.setAuthorization(account_sid, auth_token);
  
  String msgBody = "Body=" + message + "&From=whatsapp:" + String(twilio_from) + "&To=whatsapp:" + String(twilio_to);
  
  int httpResponseCode = http.POST(msgBody);
  if(httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
