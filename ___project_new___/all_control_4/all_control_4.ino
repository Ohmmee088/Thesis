//#include <stddef.h> // for C
//#include <cstddef>  // for C++
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Keypad_I2C.h>      //Keypad
#include <Keypad.h>
//#include <Wire.h>
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
int digitalPin1 = 25;     //pir senser 
int digitalPin2 = 33;
int motion1 = 0;
int motion2 = 0;
int val = 0;           //PN532_I2C   
int pos1 = 0;          //pos ประตู
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int st1 = 0;
int st2 = 0;
int st3 = 0;
int st4 = 0;
#if 0
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
#else
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);
#endif
const char* ssid     = "RMUTSV_IoT";
const char* password = "CoE39201";
#include <TridentTD_LineNotify.h>
//const char* ssid     = "WIFI_AOM";
//const char* password = "33262537";
const char* serverName = "http://172.16.8.8/waste_room/esp32/add2.php?";
WiFiClientSecure client;
#define LINE_TOKEN "XcOu4QhlWlD2yUAATnexMP3V0rkT5Ulogb1N3KHyreA"

void setup() {
  Serial.begin(115200);
  Serial.println(LINE.getVersion());
  LINE.setToken(LINE_TOKEN);
  lcd.begin();
  lcd.backlight();
  //Wire.begin();
  WiFi.begin(ssid, password);              //wifi
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
  Serial.print(".");}
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  keypad.begin();                 //keypad
  myservo1.attach(12);            //servo
  myservo2.attach(14);
  myservo3.attach(27);
  myservo4.attach(26);
  pinMode(digitalPin1, INPUT);    //pir senser 
  pinMode(digitalPin2, INPUT);

  nfc.begin();                    //pn532
  uint32_t versiondata = nfc.getFirmwareVersion(); 
  if (! versiondata) {
    Serial.print("ไม่พบบอร์ด PN53x");
    while (1); // halt
  }
  Serial.print("ตรวจพบชิป PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware เวอร์ชั่น. "); Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();
}


void door1(int D1) {
  Serial.print("motion1 = ");    Serial.println(motion1);
  if(motion1 == 0){
    if (D1 == 0 && st1 == 0) {     
      lcd.setCursor(0, 0);
      lcd.print(" >>> LOCK 1 <<< "); 
      LINE.notify("ประตูบานที่ 1 สถานะ = ปิด");    
        for (pos1 = 3; pos1 < 133; pos1 += 1){
          Serial.println("ประตู 1 ปิด");     
          myservo1.write(pos1);   
          delay(35);  
          st1 = 1;
        }
    }
    if (D1 == 1 && st1 == 1){    
     lcd.setCursor(0, 0);
      lcd.print(">>> UNLOCK 1 <<<"); 
      LINE.notify("ประตูบานที่ 1 สถานะ = เปิด");
      for (pos1 = 133; pos1 >= 3; pos1 -= 1){ 
        Serial.println("ประตู 1 เปิด");                      
        myservo1.write(pos1);   
        delay(35);  
        st1 = 0;
      }
    }              
  }
  else if(motion1 == 1){
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("   OBSTRUCT 1   ");
    delay(500);
    lcd.clear();
  }    
}

void door2(int D2) {
  Serial.print("motion1 = ");    Serial.println(motion1); 
  if(motion1 == 0){
    if (D2 == 0 && st2 == 0) {   
      lcd.setCursor(0, 0);
      lcd.print(" >>> LOCK 2 <<< ");  
      LINE.notify("ประตูบานที่ 2 สถานะ = ปิด");    
        for (pos2 = 133; pos2 >= 3; pos2 -= 1){
          Serial.println("ประตู 2 ปิด");           
          myservo2.write(pos2);   
          delay(35);  
          st2 = 1;
        }
    }
    if (D2 == 1 && st2 == 1){   
      lcd.setCursor(0, 0);
      lcd.print(">>> UNLOCK 2 <<<");
      LINE.notify("ประตูบานที่ 2 สถานะ = เปิด");  
        for (pos2 = 3; pos2 < 133; pos2 += 1){ 
          Serial.println("ประตู 2 เปิด"); 
          myservo2.write(pos2);   
          delay(35);  
          st2 = 0;
        }
    }              
  }
  else if(motion1 == 1){
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("   OBSTRUCT 2   ");
    delay(500);
    lcd.clear();
  }   
}

void door3(int D3) {
  Serial.print("motion2 = ");    Serial.println(motion2);
  if(motion2 == 0){
    if (D3 == 0 && st3 == 0) {
      lcd.setCursor(0, 0);
      lcd.print(" >>> LOCK 3 <<< "); 
      LINE.notify("ประตูบานที่ 3 สถานะ = ปิด");   
        for (pos3 = 3; pos3 < 133; pos3 += 1){
          Serial.println("ประตู 3 ปิด");       
          myservo3.write(pos3);   
          delay(35);  
          st3 = 1;
        }
    }
    if (D3 == 1 && st3 == 1){
      lcd.setCursor(0, 0);
      lcd.print(">>> UNLOCK 3 <<<");
      LINE.notify("ประตูบานที่ 3 สถานะ = เปิด");         
        for (pos3 = 133; pos3 >= 3; pos3 -= 1){ 
          Serial.println("ประตู 3 เปิด");  
          myservo3.write(pos3);   
          delay(35);  
          st3 = 0;
        }
    }         
  }
  else if(motion2 == 1){
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("   OBSTRUCT 3   ");
    delay(500);
    lcd.clear();
  }   
}

void door4(int D4) {
  Serial.print("motion2 = ");    Serial.println(motion2);
  if(motion2 == 0){
    if (D4 == 0 && st4 == 0) {    
      lcd.setCursor(0, 0);
      lcd.print(" >>> LOCK 4 <<< "); 
      LINE.notify("ประตูบานที่ 4 สถานะ = ปิด");     
        for (pos4 = 133; pos4 >= 3; pos4 -= 1){
          Serial.println("ประตู 4 ปิด");  
          myservo4.write(pos4);   
          delay(35);  
          st4 = 1;
        } 
    }
    if (D4 == 1  && st4 == 1){ 
      lcd.setCursor(0, 0);
      lcd.print(">>> UNLOCK 4 <<<");
      LINE.notify("ประตูบานที่ 4 สถานะ = เปิด");   
        for (pos4 = 3; pos4 < 133; pos4 += 1){ 
          Serial.println("ประตู 4 เปิด");     
          myservo4.write(pos4);   
          delay(35);  
          st4 = 0;
        }
    }           
  } 
  else if(motion2 == 1){
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("   OBSTRUCT 4   ");
    delay(500);
    lcd.clear();
  }   
}



void loop() 
{
  motion1 = digitalRead(digitalPin1);    //pir senser 
  motion2 = digitalRead(digitalPin2);
  unsigned long time = millis();
  if (millis() - time > 30000) 
  {
  lcd.noBacklight();
  lcd.noDisplay();             
  }

  lcd.setCursor(0, 0);
  lcd.print(">>> WELCOME <<<");
  lcd.setCursor(0, 1);
  lcd.print("PASSWORD :");
  /*for (int d = 0; d < 4; d++) {
    if (d >= keyindex) {break;}
    lcd.setCursor(d + 12, 1);
    lcd.print("*");
  }*/
  key = keypad.getKey();
  if (key != NO_KEY) {                  //1.ถ้ามีการกดเกิดขึ้น
    time = millis();
    keyinput += key;
    keyindex++;    
    Serial.println(keyinput);
    lcd.setCursor(11, 1);
    lcd.print(keyinput);
    if ( keyindex <= 1 ) {    //2.กดABCD เพื่อปิดประตู
            if (keyinput == A) {    D1 = 0; door1(D1);  lcd.clear();  keyinput = ""; keyindex = 0;   }
            if (keyinput == B) {    D2 = 0; door2(D2);  lcd.clear();  keyinput = ""; keyindex = 0;   }
            if (keyinput == C) {    D3 = 0; door3(D3);  lcd.clear();  keyinput = ""; keyindex = 0;   }
            if (keyinput == D) {    D4 = 0; door4(D4);  lcd.clear();  keyinput = ""; keyindex = 0;   }
            if (keyinput == "#") {  Serial.println("Cancel");       
                                    delay(500);         lcd.clear();  keyinput = ""; keyindex = 0;   }   
            if (keyinput == "*") {  keyinput = "";      keyindex = 0; pn535();}   
            mqtt();
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

      else{
        lcd.clear();
        keyinput = "";
        keyindex = 0;
        if (faildelay >= 10) {
          Serial.println("Password fail");
          lcd.setCursor(6, 1);
          lcd.print("FAIL");
          delay(1000);
          lcd.clear();
          Serial.println("Fail delay " + String(faildelay) + " S");
          for (int i = faildelay; i >= 0; i--) 
          {
            Serial.println(i);
            lcd.setCursor(8, 1);
            lcd.print(i);
            delay(1000);
          }
          time = millis();
          faildelay += 10;
          Serial.println("Delay End");
          //lcd.setCursor(11, 1);
          //lcd.print("END ");
          lcd.clear();
        } 
        else{
        faildelay++;
        }
        lcd.clear();
      }
      mqtt();
      //lcd.setCursor(11, 1);
      //lcd.print("    ");
      lcd.clear();
    } // =4 
  }  //คีย์แพด
}   //loop



void pn535(){
  lcd.setCursor(0, 1);
  lcd.print("   RFID MODE    ");
  Serial.println("  RFID MODE ");
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 250 );
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
          door1(D1);  //delay(1000);   
          door2(D2);  //delay(1000); 
          door3(D3);  //delay(1000);
          door4(D4);  //delay(1000);
        }
        if (val == 2) {     // เมื่อค่า val = 1 แล้ว ประตู 1-4 ปิด
          delay(100);
          D1 = 0;   D2 = 0;   D3 = 0;   D4 = 0;
          door1(D1);  //delay(1000);   
          door2(D2);  //delay(1000); 
          door3(D3);  //delay(1000);
          door4(D4);  //delay(1000);
          val = 0;
        }
      mqtt();
    }
    lcd.setCursor(0, 1);
    lcd.print("                ");
    Serial.println("  RFID MODE END  ");
}   //pn535()



void mqtt(){
    if (WiFi.status() == WL_CONNECTED) {             //http mysql
      HTTPClient http;
      String url = serverName;
      url +="&motion_1=";     url+=motion1 ;
      url +="&motion_2=";     url+=motion2 ;
      url +="&servo_1=";    url+=D1 ;
      url +="&servo_2=";    url+=D2 ;
      url +="&servo_3=";    url+=D3 ;
      url +="&servo_4=";    url+=D4 ;

      Serial.println(url);
      http.begin(url);              //HTTP
      int httpCode = http.GET();
      if (httpCode > 0){
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);
          if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
          }
      } 
      else{
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    }
}






