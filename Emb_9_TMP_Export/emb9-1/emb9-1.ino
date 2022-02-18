#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ThingSpeak.h>

int tmpPort = 0;
int lcdSda = 4;
int lcdScl = 5;

const char* ssid = "olleh_WiFi_306D"; // your ssid
const char* password = "0000003898"; // your wifi password
WiFiClient client;

unsigned long ChannelID = 1558077;
const char* WriteAPIKey = "OHFF4FM4G9ZQVFKI";
const char* server = "api.thingspeak.com";

OneWire oneWire(tmpPort);
DallasTemperature sensors(&oneWire);

int DATA = 999;

void setup() {
 Serial.begin(9600);
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
 ThingSpeak.begin(client);

}

void loop() {
  Serial.print("Requesting Temperatures.....");
  sensors.requestTemperatures();
  Serial.println("Done!");
  DATA = sensors.getTempCByIndex(0);
  Serial.print("Temp is : ");
  Serial.println(DATA);
  delay(1000);
  ThingSpeak.writeField(ChannelID, 1, DATA, WriteAPIKey);
  delay(30000);
}
