#include <LiquidCrystal_I2C.h>
#define BUTTON 7
#define CLEARBUTTON 8
LiquidCrystal_I2C lcd(0x27,20,4); 
unsigned long currTime = 0;
unsigned long pressTime = 0;
unsigned long pressDuration = 0;
bool oldState = HIGH;
bool buttonState;
bool longPress = false;
int intervalButton = 50;
unsigned long startBreak;
int startPoint = 0; 
unsigned long endBreak = 0;
unsigned long previousTime = 0;
bool clearState = HIGH;
String code = "";
byte customChar0[] = {
  B01100,
  B11110,
  B11111,
  B00011,
  B11111,
  B11111,
  B11110,
  B10010
};
byte customChar1[] = {
  B00110,
  B01111,
  B11111,
  B11000,
  B11111,
  B11111,
  B01111,
  B01001
};
void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar0);
  lcd.createChar(1, customChar1);
  lcd.setCursor(0,0);
  lcd.write(0);
  lcd.setCursor(15,0);
  lcd.write(1);
  lcd.setCursor(2,0);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(CLEARBUTTON, INPUT_PULLUP);
}
void loop()
{
  currTime = millis();
  pressButton();
}
void pressButton()
{
  if(currTime - previousTime > intervalButton)
  {
    buttonState = digitalRead(BUTTON);
    clearState = digitalRead(CLEARBUTTON);
    if (clearState == LOW)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.write(0);
        lcd.setCursor(15,0);
        lcd.write(1);
        lcd.setCursor(2,0);
      }
    endBreak = millis();
    if (endBreak - startBreak > 1000 && startPoint == 2 )
      {
        startPoint = 0;
        morse();
      }
    if (buttonState == LOW && oldState == HIGH && longPress == false)
      {
        pressTime = currTime;
        oldState = LOW;
      }
    pressDuration = currTime - pressTime;
    if (buttonState == LOW && longPress == false && pressDuration >= 200)
      {
        longPress = true;
        code += '1';
        startPoint = 1;
      }
    if (buttonState == HIGH && oldState == LOW)
      {
      oldState = HIGH;
      longPress = false;
        if (pressDuration >= 50 && pressDuration < 200)
        {
          code += '0';
          startPoint = 1;
        }
      if (startPoint == 1)
        {
          startBreak = currTime;
          startPoint = 2;
        }
      }
    previousTime = currTime;
  }
}
void morse()
{
  static String morsecode[] = {"01", "1000", "1010", "100", "0", "0010", "110", "0000",
"00", "0111", "101", "0100", "11", "10", "111", "0110", "1101",
"010", "000", "1", "001", "0001", "011", "1001", "1011", "1100", "!"};
  int i = 0;
  while (morsecode[i] != "!" )
  {
    if (morsecode[i] == code)
    {
      lcd.print(char('A'+i));
      break;
    }
    i++;
  }
  if (morsecode[i] == "!")
    lcd.print("ERROR");
  code = "";
}