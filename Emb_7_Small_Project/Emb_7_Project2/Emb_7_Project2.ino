#include <LiquidCrystal_I2C.h>
void ICACHE_RAM_ATTR chg_state();
// GPIO Pin(s)
int swtPort = 14;
int lcdSda = 4;
int lcdScl = 5;

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button
volatile int power_state = 0;
volatile int string_state = 0;

void setup() {
  Serial.println("Booting Procedure Init.");
  Serial.begin(9600);

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
    string_state = 1;
  }
  else
  {
    if(string_state == 1)
    {
      string_state = 2;
    }
    else if(string_state == 2)
    {
      string_state = 3;
    }
    else
    {
      string_state = 0;
      power_state = 2;
    }
  }
}

void loop() {
  Serial.print("State : ");
  Serial.println(power_state);
  if(power_state == 1)
  {
    switch(string_state)
    {
      case 1:
      {
        // Display the info.
        lcd.setCursor(0,0);
        lcd.print("[1]  2   3 ");
        lcd.setCursor(0,1);
        lcd.print("Lorem ipsum...");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Lorem ipsum");
        lcd.setCursor(0,1);
        lcd.print("dolor sit amet");
        delay(3000);
        lcd.clear();
        break;
      }
      case 2:
      {
        // Display the info.
        lcd.setCursor(0,0);
        lcd.print(" 1  [2]  3 ");
        lcd.setCursor(0,1);
        lcd.print("consectetur...");
        delay(2000);
        lcd.clear();
        delay(1000);
        lcd.setCursor(0,0);
        lcd.print("consectetur");
        lcd.setCursor(0,1);
        lcd.print("adipiscing elit");
        delay(4000);
        lcd.clear();
        break;
      }
      case 3:
      {
        // Display the info.
        lcd.setCursor(0,0);
        lcd.print(" 1   2  [3]");
        lcd.setCursor(0,1);
        lcd.print("sed do...");
        delay(2000);
        lcd.clear();
        delay(1000);
        lcd.setCursor(0,0);
        lcd.print("sed do");
        lcd.setCursor(0,1);
        lcd.print("eiusmod tempor");
        delay(4000);
        lcd.clear();
        break;
      }
      default:
      {
        // Display the info.
        lcd.setCursor(0,0);
        lcd.print("ERR");
        lcd.setCursor(0,1);
        lcd.print("ERR : string_state");
        delay(2000);
        lcd.clear();
        delay(1000);
        lcd.setCursor(0,0);
        lcd.print("ERR");
        lcd.setCursor(0,1);
        lcd.print("ERR : string_state");
        delay(4000);
        lcd.clear();
        break;
      }
    }
    
  }

  if(power_state == 2)
  {
    lcd.setCursor(0,0);
    lcd.print("ChiHyeon Lee");
    power_state = 0;
  }
  
  delay(1000);
}
