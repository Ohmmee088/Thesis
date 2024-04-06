#include <Keypad_I2C.h>      //Keypad
//#include <Keypad.h>
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
  {'A', 'B', 'C', 'D'}  };
byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {4, 5, 6, 7};
String password1 = "159A";
String password2 = "159B";
String password3 = "159C";
String password4 = "159D";
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

int digitalPin1 = 34;     //pir senser 
int digitalPin2 = 35;
int val1 = 0;
int val2 = 0;


int val = 0;           //PN532_I2C   
/**#if 0
#include <SPI.h>
#include <PN532_SPI.h>
#include "PN532.h"
PN532_SPI pn532spi(SPI, 10);
PN532 nfc(pn532spi);
#elif 0
#include <PN532_HSU.h>
#include <PN532.h>
PN532_HSU pn532hsu(Serial1);
PN532 nfc(pn532hsu);
#else**/
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);
//#endif

void setup() {
  Serial.begin(115200);
  //Wire.begin();
  keypad.begin();
  myservo1.attach(23);   //servo
  myservo2.attach(22);
  myservo3.attach(1);
  myservo4.attach(3);
  pinMode(digitalPin1, INPUT);   //pir senser 
  pinMode(digitalPin2, INPUT);

  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion(); //pn535
  if (! versiondata) {
    Serial.print("ไม่พบบอร์ด PN53x");
    while (1); // halt
  }
  Serial.print("ตรวจพบชิป PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware เวอร์ชั่น. "); Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();
  Serial.println("กำลังรอการสแกนบัตร");
}


void door1(int D1) {
  if(val1 == 0){
    Serial.print("val1 = ");    Serial.println(val1);
    if (D1 == 1 ){    Serial.println("Door 1 Open"); myservo1.write(155);         } 
    if (D1 == 0) {    Serial.println("Door 1 Close"); myservo1.write(35);         }   
  } 
}
void door2(int D2) {
  if(val1 == 0){ 
    Serial.print("val1 = ");    Serial.println(val1); 
    if (D2 == 1 ){    Serial.println("Door 2 Open");  myservo2.write(155);        } 
    if (D2 == 0) {    Serial.println("Door 2 Close");  myservo2.write(35);        } 
  } 
}
void door3(int D3) {
  if(val2 == 0){
    Serial.print("val2 = ");    Serial.println(val2);
    if (D3 == 1 ){    Serial.println("Door 3 Open"); myservo3.write(155);         } 
    if (D3 == 0) {    Serial.println("Door 3 Close"); myservo3.write(35);         }
  } 
}
void door4(int D4) {
  if(val2 == 0){
    Serial.print("val2 = ");    Serial.println(val2);
    if (D4 == 1 ){    Serial.println("Door 4 Open"); myservo4.write(155);         } 
    if (D4 == 0) {    Serial.println("Door 4 Close"); myservo4.write(35);         }
  } 
}



void loop() 
{
  val1 = digitalRead(digitalPin1);    //pir senser 
  val2 = digitalRead(digitalPin2);
  unsigned long time = millis();
  if (millis() - time > 30000) 
  {
  //lcd.noBacklight();
  //lcd.noDisplay();             
  }
  //lcd.setCursor(2, 0);
  //lcd.print(">>> LOCK <<<");
  //lcd.setCursor(0, 1);
  //lcd.print("PASSWORD : ");
  for (int d = 0; d < 4; d++) {
    if (d >= keyindex) {break;}
    //lcd.setCursor(d + 12, 1);
    //lcd.print("*");
  }
  key = keypad.getKey();
  if (key != NO_KEY) {                  //1.ถ้ามีการกดเกิดขึ้น
    //time = millis();
    keyinput += key;
    keyindex++;
    Serial.println(keyinput);
    if ( keyindex <= 1 ) {    //2.กดABCD เพื่อปิดประตู
            if (keyinput == A) {      D1 = 0;     door1(D1);     keyinput = "";keyindex = 0;   }
            if (keyinput == B) {      D2 = 0;     door2(D2);     keyinput = "";keyindex = 0;   }
            if (keyinput == C) {      D3 = 0;     door3(D3);     keyinput = "";keyindex = 0;   }
            if (keyinput == D) {      D4 = 0;     door4(D4);     keyinput = "";keyindex = 0;   }
            if (keyinput == "#") {    Serial.println("  Cancel");     keyinput = ""     ;keyindex = 0;   }      
     }
    else if ( keyindex >= 4 ) {               //3.ถ้ามีการกด 4 ครั้ง
      if (keyinput == password1) {
        Serial.println("Unlock 1");
        keyinput = "";
        keyindex = 0;
        delay(500);
        D1 = 1; 
        door1(D1);
        }
      else if (keyinput == password2) {
        Serial.println("Unlock 2");
        keyinput = "";
        keyindex = 0;
        delay(500);
        D2 = 1; 
        door2(D2);
        }
      else if (keyinput == password3) {
        Serial.println("Unlock 3");
        keyinput = "";
        keyindex = 0;
        delay(500);
        D3 = 1; 
        door3(D3);
        }
      else if (keyinput == password4) {
        Serial.println("Unlock 4");
        keyinput = "";
        keyindex = 0;
        delay(500);
        D4 = 1; 
        door4(D4);
        }


      else {
        keyinput = "";
        keyindex = 0;
        if (faildelay >= 10) {
          Serial.println("Password fail");
          Serial.println("Fail delay " + String(faildelay) + " S");
          for (int i = faildelay; i >= 0; i--) 
          {
            Serial.println(i);
            delay(1000);
          }
          //time = millis();
          faildelay += 10;
          Serial.println("Delay End");
        } 
        else{
        faildelay++;
        }
      }
    }
  }  //คีย์แพด

  pn535(); 
}   //loop



void pn535(){  
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;
  
  //success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  //success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 1 );
  //success = nfc.read();
  /*if (keyinput == "*"){
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength); 
  keyinput == "";
  keyindex = 0;
  }*/
  Serial.println("kk 5");
  
  if (success) {  // ทำงานเมื่อการสแกนบัตร RFID ประสบความสำเร็จ
      Serial.println("ตรวจพบบัตร!");
      Serial.print("UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
      Serial.print("UID Value: ");
      for (uint8_t i = 0; i < uidLength; i++)
      {
        Serial.print(" -"); Serial.print(uid[i], DEC);
      }
      Serial.println("");
      delay(1000);
    }
    //else {  // ทำงานเมื่อการสแกนบัตร RFID ไม่ประสบความสำเร็จ
    //  Serial.println("หมดเวลาในการสแกนบัตรรอบนี้ กรุณาสแกนบัตรอีกครั้ง");
    //}

    if ((uid[0] == 3 || uid[1] == 247 || uid[2] == 170 || uid[3] == 21) ||  (uid[0] == 211 || uid[1] == 94 || uid[2] == 161 || uid[3] == 14))
    {
      val++;               //กำหนดค่า val ให้เพิ่มขึ้นตามที่กำหนดไว้ เมื่อมีการ์ดหรือแท๊กที่มีชุดข้อมูลตรงกับ uid ด้านบนเข้าในระยะสแกน
        if (val == 1) {     // กำหนดการใช้งาน เมื่อค่า val = 1 แล้ว ประตู 1-4 เปิด
          delay(100);       
          D1 = 1;   D2 = 1;   D3 = 1;   D4 = 1;
          door1(D1);  delay(1000);   
          door2(D2);  delay(1000); 
          door4(D3);  delay(1000);
          door1(D4);  delay(1000);
          //pnkey_open();
        }
        if (val == 2) {     // เมื่อค่า val = 1 แล้ว ประตู 1-4 ปิด
          delay(100);
          D1 = 0;   D2 = 0;   D3 = 0;   D4 = 0;
          door1(D1);  delay(1000);   
          door2(D2);  delay(1000); 
          door4(D3);  delay(1000);
          door1(D4);  delay(1000);
          val = 0;
        }
    }
}   //pn535()









