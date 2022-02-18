#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String    rss ="http://www.kma.go.kr/weather/forecast/mid-term-rss3.jsp?stnId=109";      //   자신의 원하는 위치에 대한 RSS
const String endpoint = "http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=";

String line = "";
String message ="";               //create an empty string to store the future received data 

// 와이파이 ssid을 입력.
const char* ssid     = "olleh_WiFi_306D";

//와이파이 비밀번호를 입력.
const char* password = "0000003898";

int lcdSda = 4;
int lcdScl = 5;

void setup() {
    Serial.begin(9600);
    delay(10);
    // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    lcd.begin();
    lcd.backlight();
    lcd.print("ChiHyeon Lee");
    Serial.println("Booting Procedure Comp.");
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    Serial.println("Starting connection to server...");
    HTTPClient http;
    String rss_url = endpoint+rss;
    
    http.begin(rss_url);        //Specify the URL
    int httpCode = http.GET();  //Make the request
    if (httpCode > 0) {         //Check for the returning code
      line = http.getString();
    }
    else {
      Serial.println("Error on HTTP request");
    }
    message = parsing();
    http.end(); //Free the resources
  }
  delay(20000);
}

String parsing() {
  lcd.clear();
  String announce_time;     //  기상청 예보 발표시간

  int tm_start= line.indexOf(F("<tm>")); // "<tm>"문자가 시작되는 인덱스 값('<'의 인덱스)을 반환한다. 
  int tm_end= line.indexOf(F("</tm>"));  
  announce_time = line.substring(tm_start + 4, tm_end); // +4: "<tm>"스트링의 크기 4바이트, 4칸 이동
  Serial.print(F("announce_time: ")); Serial.println(announce_time);

  String hours;                                    // 첫번째 시간 예보
  int hour_start= line.indexOf(F("<hour>"));
  int hour_end= line.indexOf(F("</hour>"));
  hours = line.substring(hour_start + 6, hour_end);
  Serial.print(F("hour: ")); Serial.println(hours);
  lcd.setCursor(0,0);
  lcd.print("HOUR : ");
  lcd.setCursor(0,1);
  lcd.print(hours);
  delay(500);
  lcd.clear();

  String temp;
  int temp_start= line.indexOf(F("<temp>"));
  int temp_end= line.indexOf(F("</temp>"));
  temp = line.substring(temp_start + 6, temp_end);
  Serial.print(F("temp: ")); Serial.println(temp);
  lcd.setCursor(0,0);
  lcd.print("TEMP : ");
  lcd.setCursor(0,1);
  lcd.print(temp);
  delay(500);
  lcd.clear();
 
  String wfEn;
  int wfEn_start= line.indexOf(F("<wfEn>"));
  int wfEn_end= line.indexOf(F("</wfEn>"));
  wfEn = line.substring(wfEn_start + 6, wfEn_end);
  Serial.print(F("weather: ")); Serial.println(wfEn);
  lcd.setCursor(0,0);
  lcd.print("WTR : ");
  lcd.setCursor(0,1);
  lcd.print(wfEn);
  delay(500);
  lcd.clear();

  delay(1000);

//  두번째 시간 예보
  int del_index = line.indexOf(F("</data>")); 
  line.remove(0, del_index + 7);                     // 시작 인덱스 부터 "</data>" 스트링 포함 삭제
  hour_start= line.indexOf(F("<hour>"));
  hour_end= line.indexOf(F("</hour>"));
  hours = line.substring(hour_start + 6, hour_end);
  Serial.print(F("hour: ")); Serial.println(hours);   // 두번째 시간 예보
  lcd.setCursor(0,0);
  lcd.print("HOUR : ");
  lcd.setCursor(0,1);
  lcd.print(hours);
  delay(500);
  lcd.clear();

  
  temp_start= line.indexOf(F("<temp>"));
  temp_end= line.indexOf(F("</temp>"));
  temp = line.substring(temp_start + 6, temp_end);
  Serial.print(F("temp: ")); Serial.println(temp);
  lcd.setCursor(0,0);
  lcd.print("TEMP : ");
  lcd.setCursor(0,1);
  lcd.print(temp);
  delay(500);
  lcd.clear();


  wfEn_start= line.indexOf(F("<wfEn>"));
  wfEn_end= line.indexOf(F("</wfEn>"));
  wfEn = line.substring(wfEn_start + 6, wfEn_end);
  Serial.print(F("weather: ")); Serial.println(wfEn);
  lcd.setCursor(0,0);
  lcd.print("WTR : ");
  lcd.setCursor(0,1);
  lcd.print(wfEn);
  delay(500);
  lcd.clear();

  delay(1000);


  // 세번째 예보
  del_index = line.indexOf(F("</data>"));
  line.remove(0, del_index + 7);                     // 시작 인덱스 부터 "</data>" 스트링 포함 삭제
  hour_start= line.indexOf(F("<hour>"));
  hour_end= line.indexOf(F("</hour>"));
  hours = line.substring(hour_start + 6, hour_end);
  Serial.print(F("hour: ")); Serial.println(hours);
  lcd.setCursor(0,0);
  lcd.print("HOUR : ");
  lcd.setCursor(0,1);
  lcd.print(hours);
  delay(500);
  lcd.clear();
  
  temp_start= line.indexOf(F("<temp>"));
  temp_end= line.indexOf(F("</temp>"));
  temp = line.substring(temp_start + 6, temp_end);
  Serial.print(F("temp: ")); Serial.println(temp);
  lcd.setCursor(0,0);
  lcd.print("TEMP : ");
  lcd.setCursor(0,1);
  lcd.print(temp);
  delay(500);
  lcd.clear();
  
  wfEn_start= line.indexOf(F("<wfEn>"));
  wfEn_end= line.indexOf(F("</wfEn>"));
  wfEn = line.substring(wfEn_start + 6, wfEn_end);
  Serial.print(F("weather: ")); Serial.println(wfEn);
  lcd.setCursor(0,0);
  lcd.print("WTR : ");
  lcd.setCursor(0,1);
  lcd.print(wfEn);
  delay(500);
  lcd.clear();

  delay(1000);
  
  
  line = ""; // 스트링 변수 line 데이터 추출 완료 

}
