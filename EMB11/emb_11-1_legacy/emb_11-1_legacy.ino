#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLkRL1EzGp"
#define BLYNK_DEVICE_NAME "NodeMCU test1"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#include "BlynkEdgent.h"

int tmpPort = 0;

const char* ssid = "olleh_WiFi_306D"; // your ssid
const char* password = "0000003898"; // your wifi password
WiFiClient client;

OneWire oneWire(tmpPort);
DallasTemperature sensors(&oneWire);

int DATA = 999;

void setup(){
  Serial.begin(9600);
  delay(100);
  pinMode(5,OUTPUT);    //  D1 is GPIO 5
  sensors.begin();
  delay(10);
  Serial.println("Connectiong to ssid ...");
  // attempt to connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }
  // 접속성공!
  Serial.println();
  Serial.println("Connected WiFi");
  //사용하는 ip출력
  Serial.println(WiFi.localIP());
  Serial.println();
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}

BLYNK_WRITE(V0){
  int virtual_pin_value = param.asInt();
  if(virtual_pin_value){
    digitalWrite(5, HIGH);
    Serial.print("virtual_pin_value : ");
    Serial.println(virtual_pin_value);
  }
  else{
    digitalWrite(5, LOW);
  }

}
