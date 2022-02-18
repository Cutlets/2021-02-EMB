#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <ThingSpeak.h>

int tmpPort = 0;
int lcdSda = 4;
int lcdScl = 5;
int statusCode;

LiquidCrystal_I2C lcd(0x27, 16, 2);

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

 lcd.begin();
 lcd.backlight();
 lcd.print("ChiHyeon Lee");
 Serial.println("Booting Procedure Comp.");
 delay(1000);
}

void displayLCD(int optnum, long ReadValue)
{
  lcd.clear();
  switch(optnum)
  {
    case 1:
    {
      lcd.setCursor(0,0);
      lcd.print("[Current PM2.5.]");
      lcd.setCursor(0,1);
      lcd.print(ReadValue);
      delay(3000);
      lcd.clear();
      break;
    }
    case 2:
    {
      lcd.setCursor(0,0);
      lcd.print("[Current PM10 .]");
      lcd.setCursor(0,1);
      lcd.print(ReadValue);
      delay(3000);
      lcd.clear();
      break;
    }
    case 3:
    {
      lcd.setCursor(0,0);
      lcd.print("[Current TMP  .]");
      lcd.setCursor(0,1);
      lcd.print(ReadValue);
      delay(3000);
      lcd.clear();
      break;
    }
    default:
    {
      lcd.setCursor(0,0);
      lcd.print("[ERR OCCURED!!]");
      lcd.setCursor(0,1);
      lcd.print("9999");
      delay(3000);
      lcd.clear();
      break;
    }
  }
  
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
  
  Serial.println("Reading from the channel.....");
  //---------------- Channel Read ----------------//
  long pm2 = ThingSpeak.readLongField(RChannelID, 1, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
   Serial.print("PM2.5 : ");
   Serial.println(pm2);
   displayLCD(1,pm2);
  }
  else
  {
   Serial.println("Unable to read channel / No internet connection");
  }
  delay(100);

  long pm10 = ThingSpeak.readLongField(RChannelID, 2, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
   Serial.print("PM10 : ");
   Serial.println(pm10);
   displayLCD(2,pm10);
  }
  else
  {
   Serial.println("Unable to read channel / No internet connection");
  }
  delay(100);

  long rtmp = ThingSpeak.readLongField(RChannelID, 3, ReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
   Serial.print("TMP : ");
   Serial.println(rtmp);
   displayLCD(3,rtmp);
  }
  else
  {
   Serial.println("Unable to read channel / No internet connection");
  }
  delay(100);

  lcd.setCursor(0,0);
  lcd.print("[Waiting Read]");
  lcd.setCursor(0,1);
  lcd.print("Please Stand By");

  delay(21000);
}
