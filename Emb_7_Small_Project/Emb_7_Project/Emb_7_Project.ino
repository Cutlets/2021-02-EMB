#include <Wire.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
void ICACHE_RAM_ATTR chg_state();
// GPIO Pin(s)
int swtPort = 14;
int tmpPort = 2;
int lcdSda = 4;
int lcdScl = 5;

OneWire oneWire(tmpPort);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button
volatile int power_state = 0;

// Temperature
int tempC = 0;

void setup() {
  Serial.println("Booting Procedure Init.");
  Serial.begin(9600);
  sensors.begin();

  pinMode(swtPort, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(swtPort), chg_state, RISING);

  lcd.begin();
  lcd.backlight();
  lcd.print("ChiHyeon Lee");
  Serial.println("Booting Procedure Comp.");
  delay(1000);
}

void ICACHE_RAM_ATTR chg_state()
{
  Serial.println("Int Called");
  if(power_state == 0)
  {
    power_state = 1;
  }
  else
  {
    power_state = 2;
  }
}

void loop() {
  Serial.print("State : ");
  Serial.println(power_state);
  if(power_state == 1)
  {
    // Get the info.
    Serial.print("Requesting Temperatures.....");
    sensors.requestTemperatures();
    Serial.println("Done!");
    tempC = sensors.getTempCByIndex(0);
    Serial.print("Temp is : ");
    Serial.println(tempC);

    // Display the info.
    lcd.setCursor(0,0);
    lcd.print("[Current Temp.]");
    lcd.setCursor(0,1);
    lcd.print(tempC);
    lcd.write(223);
    lcd.print("C");
    delay(3000);
    lcd.clear();
  }

  if(power_state == 2)
  {
    lcd.setCursor(0,0);
    lcd.print("ChiHyeon Lee");
    power_state = 0;
  }
  
  delay(2000);
}
