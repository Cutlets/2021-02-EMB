#include <OneWire.h>
#include <DallasTemperature.h>

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLkRL1EzGp"
#define BLYNK_DEVICE_NAME "NodeMCU test1"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#include "BlynkEdgent.h"

int tmpPort = 14;
int R = 16;
int G = 2;
int B = 5;
OneWire oneWire(tmpPort);
DallasTemperature sensors(&oneWire);

BlynkTimer timer01;     //   타이머 선언

float temp;             //  온도 변수

void setup(){
  Serial.begin(9600);
  delay(100);
  
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);

  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
  
  BlynkEdgent.begin();
  sensors.begin();
  timer01.setInterval(2000L, sendSensor);
}

void loop() {
  BlynkEdgent.run();
  timer01.run();
}

BLYNK_WRITE(V0){
  int virtual_pin_value = param.asInt();
  if(virtual_pin_value){
    digitalWrite(R, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
    Serial.print("virtual_pin_value : ");
    Serial.println(virtual_pin_value);
  }
  else{
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  }
}

BLYNK_WRITE(V1){
  int virtual_pin_value = param.asInt();
  if(virtual_pin_value){
    analogWrite(R, virtual_pin_value);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
    Serial.print("virtual_pin_value : ");
    Serial.println(virtual_pin_value);
  }
  else{
    analogWrite(R, 0);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  }
}

BLYNK_WRITE(V3){
  int virtual_pin_value = param.asInt();
  if(virtual_pin_value){
    analogWrite(G, virtual_pin_value);
    Serial.print("virtual_pin_value : ");
    Serial.println(virtual_pin_value);
  }
  else{
    analogWrite(G, 0);
  }
}

BLYNK_WRITE(V4){
  int virtual_pin_value = param.asInt();
  if(virtual_pin_value){
    analogWrite(B, virtual_pin_value);
    Serial.print("virtual_pin_value : ");
    Serial.println(virtual_pin_value);
  }
  else{
    analogWrite(B, 0);
  }
}

BLYNK_WRITE(V5){
  int virtual_pin_value = param.asInt();
  if(virtual_pin_value){
    analogWrite(R, virtual_pin_value);
    Serial.print("virtual_pin_value : ");
    Serial.println(virtual_pin_value);
  }
  else{
    analogWrite(R, 0);
  }
}

void sendSensor(){
    Serial.print(" Requesting temperatures..."); 
    sensors.requestTemperatures(); // Send the command to get temperature readings 
    Serial.println("DONE"); 
    temp = sensors.getTempCByIndex(0);
    Serial.print("Temperature is: "); 
    Serial.println(temp);   
    Blynk.virtualWrite(V2, temp);
}
