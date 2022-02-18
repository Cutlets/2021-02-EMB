#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

int statusCode;

const char* ssid = "olleh_WiFi_306D"; // your ssid
const char* password = "0000003898"; // your wifi password
WiFiClient client;

//Write
unsigned long ChannelID = 1558077;
const char* WriteAPIKey = "OHFF4FM4G9ZQVFKI";
const char* server = "api.thingspeak.com";

//Read
unsigned long RChannelID = 316120;
const char* ReadAPIKey = "KLSPXGIXQ0W4CW8L";

int convTmp = 0;

void setup() {
 Serial.begin(9600);
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

 delay(1000);
}

void loop() {

  Serial.println("Reading from the channel.....");
  //---------------- Channel Read ----------------//
  long rtmp = ThingSpeak.readLongField(RChannelID, 3, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
   Serial.print("TMP : ");
   Serial.println(rtmp);
  }
  else
  {
   Serial.println("Unable to read channel / No internet connection");
  }
  delay(100);

  convTmp = (rtmp * 9/5) +32;
  Serial.print("Fahrenheit Scale : ");
  Serial.println(convTmp);
  ThingSpeak.writeField(ChannelID, 2, convTmp, WriteAPIKey);

  delay(30000);
}
