/* 18B20 센서 데이터를 google spread sheet로 보내는 예제 */
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <OneWire.h>
#include <DallasTemperature.h>
 
const char* ssid = "olleh_WiFi_306D";              // 여러분들의 무선랜 이름(바꿔줘야 함)
const char* password = "0000003898";     //  무선랜 비밀번호 (바꿔줘야함)

const char* host = "script.google.com";
const int httpsPort = 443;
// finger print, do not change
const char* fingerprint = "46 B2 C3 44 9C 59 09 8B 01 B6 F8 BD 4C FB 00 74 91 2F EF F6";

//웹 배포 주소에서 가져옴 id값
String GS_ID = "AKfycbwVOYRactr4Khc198bq0W4CslBQhgxlGxqrfUHZ8aLXSeEz9Og";

// GPIO where the DS18B20 is connected to  D2
const int oneWireBus = 14;  
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();     // 센서 시작
  connectWiFi();       // 무선랜 연결
}

void loop() {
      sensors.requestTemperatures();
      float t = sensors.getTempCByIndex(0);   // temperatureC 

      Serial.print("Temperature: ");
      Serial.println(t);
      Serial.println("------------");
  
      sendData(t);   //  데이터 전송함수 실행
      delay(30000); //  30초 : 30000 원하는 간격을 줌
}

void sendData(float x){
      Serial.print("connecting to ");
      Serial.println(host);
      WiFiClientSecure client;
      client.setInsecure();          
      if (!client.connect(host, httpsPort)) {
          Serial.println("connection failed");
          return;
      }

      if (client.verify(fingerprint, host)) {
          Serial.println("certificate matches");
      } else {
         Serial.println("certificate doesn't match");
      }

      // google sheet로 보내기 전 스트링으로 변환
      String string_x     =  String(x);

      //배포주소 뒤에 파미터명을 주고 값을 대입해서 최종 주소를 완성한다. 필요하면 다른 데이트도 추가 가능. 
      String url = "/macros/s/" + GS_ID + "/exec?temperature=" + string_x;   //   + "&humidity=" + string_y;
      Serial.print("requesting URL: ");
      Serial.println(url);

      //전송
      client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +
      "User-Agent: BuildFailureDetectorESP8266\r\n" + "Connection: close\r\n\r\n");
      Serial.println("request sent");

      //결과처리(반환된 데이터와 맞지 않아서 제대로 안됨. 동작에는 상관없음)
      while (client.connected()) {
          String line = client.readStringUntil('\n');
      if (line == "\r") {
          Serial.println("headers received");
          break;
          }
      }
      
      String line = client.readStringUntil('\n');
          if (line.startsWith("{\"state\":\"success\"")) {
          Serial.println("esp8266/Arduino CI successfull!");
          } else {
          Serial.println("esp8266/Arduino CI has failed");
      }
      Serial.println("reply was:");
      Serial.println("==========");
      Serial.println(line);
      Serial.println("==========");
      Serial.println("closing connection");
}


void connectWiFi(){
      Serial.println();
      Serial.println();
      Serial.println("Connecting to ");
      Serial.print(ssid);
      WiFi.hostname("Name");
      WiFi.begin(ssid, password);

      while(WiFi.status() != WL_CONNECTED){
          delay(500);
          Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
}
