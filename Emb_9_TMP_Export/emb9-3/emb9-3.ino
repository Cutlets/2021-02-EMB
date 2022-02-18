#include <LiquidCrystal_I2C.h>
#include <DS1302.h>
#include <time.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

int RST = 15;
int DAT = 13;
int CLK = 12;
int lcdSda = 4;
int lcdScl = 5;

char* ssid       = "olleh_WiFi_306D"; //와이파이 SSID
const char* password   = "0000003898";  //와이파이 패스워드
const char* ntpServer  = "kr.pool.ntp.org";

//3200초는 1시간, 우리나라는 GMT+9 이므로 3600초x9 = 32400 해 줌
const long  gmtOffset_sec = 32400; 

DS1302 rtc(RST,DAT,CLK);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int curr_wday = 0;

int wday_convert[7] = {7,1,2,3,4,5,6};
String DOW[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
WiFiUDP udp;
NTPClient timeClient(udp, ntpServer, gmtOffset_sec);

void setup() {
 Serial.begin(9600);

 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED)
 {
   delay(500);
   Serial.println(".");
 }
 // 접속성공!
 Serial.println();
 Serial.println("Connected WiFi");
 //사용하는 ip출력
 Serial.println(WiFi.localIP());
 Serial.println();
  
 timeClient.begin();
 timeClient.update();
 unsigned long epochTime = timeClient.getEpochTime();
 time_t t = static_cast<time_t>(epochTime);
 struct tm *timeinfo = gmtime(&t);

 rtc.halt(false);
 rtc.writeProtect(false);
 rtc.setTime(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
 rtc.setDate(timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900);
 rtc.setDOW(wday_convert[timeinfo->tm_wday]);
 curr_wday = timeinfo->tm_wday;
 rtc.writeProtect(true);

 lcd.begin();
 lcd.backlight();
 lcd.print("ChiHyeon Lee");
 Serial.println("Booting Procedure Comp.");
}

void loop() {
 // Send Day-of-Week
 Serial.print(DOW[curr_wday]);
 Serial.print(" ");
 // Send date
 Serial.print(rtc.getDateStr(2,1,'-'));
 Serial.print(" -- ");
 Serial.println(rtc.getTimeStr());
 // Wait one second before repeating :)

 lcd.setCursor(0,0);
 lcd.print("[");
 lcd.print(DOW[curr_wday]);
 lcd.print(" ");
 lcd.print(rtc.getDateStr(2,1,'-'));
 lcd.print("]");
 lcd.setCursor(0,1);
 lcd.print("[   ");
 lcd.print(rtc.getTimeStr());
 lcd.print("   ]");
 
 delay (1000);
}
