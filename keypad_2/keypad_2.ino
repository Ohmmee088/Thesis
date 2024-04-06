#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define I2CADDR 0x20
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'}
};
byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {4, 5, 6, 7};
String password1 = "123A";
String password2 = "456B";
String password3 = "789C";
String password4 = "*0#D";
int D1 = 0;
int D2 = 0;
int D3 = 0;
int D4 = 0;
String A = "A";
String B = "B";
String C = "C";
String D = "D";
char key;
String keyinput = "";
byte keyindex = 0;
byte faildelay = 0;
Keypad_I2C keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR);

#include <ESP32Servo.h>   //servo
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
//int pos = 0;

void door1(int D1) {
  if (D1 == 1 ){    Serial.println("Door 1 Open"); myservo1.write(155);         } 
  if (D1 == 0) {    Serial.println("Door 1 Close"); myservo1.write(35);         }   
  }
void door2(int D2) {
  if (D2 == 1 ){    Serial.println("Door 2 Open");  myservo2.write(155);        } 
  if (D2 == 0) {    Serial.println("Door 2 Close");  myservo2.write(35);        } 
}
void door3(int D3) {
  if (D3 == 1 ){    Serial.println("Door 3 Open"); myservo3.write(155);         } 
  if (D3 == 0) {    Serial.println("Door 3 Close"); myservo3.write(35);         }
}
void door4(int D4) {
  if (D4 == 1 ){    Serial.println("Door 4 Open"); myservo4.write(155);         } 
  if (D4 == 0) {    Serial.println("Door 4 Close"); myservo4.write(35);         }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  keypad.begin();
  lcd.begin();
  lcd.display();
  lcd.backlight();
  lcd.clear();
  myservo1.attach(23);   //servo
  myservo2.attach(22);
  myservo3.attach(1);
  myservo4.attach(3);
}


void loop() {

  unsigned long time = millis();
  if (millis() - time > 30000) 
  {
  lcd.noBacklight();
  lcd.noDisplay();             
  }
  lcd.setCursor(2, 0);
  lcd.print(">>> LOCK <<<");
  lcd.setCursor(0, 1);
  lcd.print("PASSWORD : ");
  for (int d = 0; d < 4; d++) {
    if (d >= keyindex) {break;}
    lcd.setCursor(d + 12, 1);
    lcd.print("*");
  }

  key = keypad.getKey();
  if (key != NO_KEY) {                  //1.ถ้ามีการกดเกิดขึ้น
    time = millis();
    lcd.backlight();
    lcd.display();
    keyinput += key;
    keyindex++;
    Serial.println(keyinput);

    if ( keyindex <= 1 ) {               //2.กดABCD เพื่อปิดประตู
            if (keyinput == A) {      D1 = 0;     door1(D1);     keyinput = "";keyindex = 0;   }
            if (keyinput == B) {      D2 = 0;     door2(D2);     keyinput = "";keyindex = 0;   }
            if (keyinput == C) {      D3 = 0;     door3(D3);     keyinput = "";keyindex = 0;   }
            if (keyinput == D) {      D4 = 0;     door4(D4);     keyinput = "";keyindex = 0;   }
            if (keyinput == "#") {    Serial.println("  Cancel");     keyinput = ""     ;keyindex = 0;   }      
     }

    if ( keyindex >= 4 ) {               //3.ถ้ามีการกด 4 ครั้ง
        if (keyinput == password1) {
        lcd.setCursor(1, 0);
        lcd.print("*** UNLOCK ***");
        Serial.println("Unlock 1");
        keyinput = "";
        keyindex = 0;
        delay(500);
        lcd.clear();
        D1 = 1; 
        door1(D1);
        }

      if (keyinput == password2) {
        lcd.setCursor(1, 0);
        lcd.print("*** UNLOCK ***");
        Serial.println("Unlock 2");
        keyinput = "";
        keyindex = 0;
        delay(500);
        lcd.clear();
        D2 = 1; 
        door2(D2);
        }
      else if (keyinput == password3) {
        lcd.setCursor(1, 0);
        lcd.print("*** UNLOCK ***");
        Serial.println("Unlock 3");
        keyinput = "";
        keyindex = 0;
        delay(500);
        lcd.clear();
        D3 = 1; 
        door3(D3);
        }
      else if (keyinput == password4) {
        lcd.setCursor(1, 0);
        lcd.print("*** UNLOCK ***");
        Serial.println("Unlock 4");
        keyinput = "";
        keyindex = 0;
        delay(500);
        lcd.clear();
        D4 = 1; 
        door4(D4);
        }

      else {
        keyinput = "";
        keyindex = 0;
        lcd.clear();
        if (faildelay >= 10) {
          lcd.setCursor(1, 0);
          lcd.print("PASSWORD FAIL");
          lcd.setCursor(0, 1);
          lcd.print("TIME COUNT : ");
          Serial.println("Password fail");
          Serial.println("Fail delay " + String(faildelay) + " S");
          for (int i = faildelay; i >= 0; i--) 
          {
            lcd.setCursor(13, 1);
            lcd.print("   ");
            lcd.setCursor(13, 1);
            lcd.print(i);
            Serial.println(i);
            delay(1000);
          }
          lcd.clear();
          time = millis();
          faildelay += 10;
          Serial.println("Delay End");
        } 
        else{
        faildelay++;
        }
      }
    }
  }  //คีย์แพด







}







