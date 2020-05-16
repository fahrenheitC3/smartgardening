/**
   Authorization.ino

    Created on: 09.12.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("PYUR F876E", "nQ68d4cNeuw6");
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;
    HTTPClient http2;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url


    http.begin(client, "http://ec2-63-32-88-214.eu-west-1.compute.amazonaws.com:8081/api/v1/profiles/login");
    http.addHeader("Content-Type", "application/json");

    /*
      // or
      http.begin(client, "http://jigsaw.w3.org/HTTP/Basic/");
      http.setAuthorization("guest", "guest");

      // or
      http.begin(client, "http://jigsaw.w3.org/HTTP/Basic/");
      http.setAuthorization("Z3Vlc3Q6Z3Vlc3Q=");
    */

DynamicJsonDocument doc(2048);
doc["username"] = "alexp";
doc["password"] = "test123";
// Serialize JSON document
String json;
serializeJson(doc, json);
    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
   int httpCode = http.POST(json);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
        // Parse response
DynamicJsonDocument doc(2048);
deserializeJson(doc, http.getStream());

// Read values
Serial.println(doc["message"].as<String>());

const char* world = doc["message"];
  http2.begin(client, "http://ec2-63-32-88-214.eu-west-1.compute.amazonaws.com:8081/api/v1/profiles/efan");
    http2.addHeader("Content-Type", "application/json");
    http2.addHeader("Authorization", "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJVc2VybmFtZSI6ImFsZXhwIn0.1jazj1WcDzA--2TG4siezhIK6__VdDvuQamd1NHJIrE");

    int httpCode2 = http2.GET();

    // httpCode will be negative on error
    if (httpCode2 > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode2 == HTTP_CODE_OK) {
        String payload2 = http.getString();
        Serial.println(payload2);
        // Parse response
DynamicJsonDocument doc2(2048);
deserializeJson(doc2, http2.getStream());

// Read values
Serial.println(doc2["email"].as<String>());
      }
    }
    else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http2.errorToString(httpCode2).c_str());
    }
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(10000);
}
