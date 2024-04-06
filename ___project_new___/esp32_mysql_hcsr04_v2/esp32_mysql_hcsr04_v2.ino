#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Wire.h>
const char* ssid     = "RMUTSV_IoT";
const char* password = "CoE39201";
const char* serverName = "http://172.16.8.8/waste_room/esp32/add.php?";
WiFiClientSecure client;
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN  "XcOu4QhlWlD2yUAATnexMP3V0rkT5Ulogb1N3KHyreA" //ใส่ รหัส TOKEN ที่ได้มาจากข้างบน
/*const int trigPin = 32;     int inPin = 33;  
const int trigPin2 = 25;    int inPin2 = 26;  
const int trigPin3 = 27;    int inPin3 = 14;  
const int trigPin4 = 12;    int inPin4 = 13;  
const int trigPin5 = 15;    int inPin5 = 2;
const int trigPin6 = 0;     int inPin6 = 4;
const int trigPin7 = 16;    int inPin7 = 17;
const int trigPin8 = 5;     int inPin8 = 18;*/
const int trigPins[] = {13, 14, 26, 25, 33, 32, 4, 17};
const int echoPins[] = {12, 27, 35, 34, 39, 36, 16, 5};
int pinA1 = 18; // A1    //tpm300
int pinB1 = 19; // B1
int pinA2 = 21; // A2
int pinB2 = 23; // B2
int a = 1;
int air1 = 0 , air2 = 0 , air3 = 0 , air4 = 0; 



void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println(LINE.getVersion());
  LINE.setToken(LINE_TOKEN);
  pinMode(pinA1, INPUT);    //tpm300 a1
  pinMode(pinB1, INPUT);    //tpm300 b1
  pinMode(pinA2, INPUT);    //tpm300 a2
  pinMode(pinB2, INPUT);    //tpm300 b2

  WiFi.begin(ssid, password);              //wifi
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  /*long duration0 = measureDistance(trigPins[0], echoPins[0]);
  long distances0 = microsecondsToCentimeters(duration0);
  long duration1 = measureDistance(trigPins[1], echoPins[1]);
  long distances1 = microsecondsToCentimeters(duration1);
  long duration2 = measureDistance(trigPins[2], echoPins[2]);
  long distances2 = microsecondsToCentimeters(duration2);
  long duration3 = measureDistance(trigPins[3], echoPins[3]);
  long distances3 = microsecondsToCentimeters(duration3);
  long duration4 = measureDistance(trigPins[4], echoPins[4]);
  long distances4 = microsecondsToCentimeters(duration4);
  long duration5 = measureDistance(trigPins[5], echoPins[5]);
  long distances5 = microsecondsToCentimeters(duration5);
  long duration6 = measureDistance(trigPins[6], echoPins[6]);
  long distances6 = microsecondsToCentimeters(duration6);
  long duration7 = measureDistance(trigPins[7], echoPins[7]);
  long distances7 = microsecondsToCentimeters(duration7);
  Serial.print("Sensor 1 : "); Serial.print(distances0);Serial.println(" cm");
  Serial.print("Sensor 2 : "); Serial.print(distances1);Serial.println(" cm");
  Serial.print("Sensor 3 : "); Serial.print(distances2);Serial.println(" cm");
  Serial.print("Sensor 4 : "); Serial.print(distances3);Serial.println(" cm");
  Serial.print("Sensor 5 : "); Serial.print(distances4);Serial.println(" cm");
  Serial.print("Sensor 6 : "); Serial.print(distances5);Serial.println(" cm");
  Serial.print("Sensor 7 : "); Serial.print(distances6);Serial.println(" cm");
  Serial.print("Sensor 8 : "); Serial.print(distances7);Serial.println(" cm");
  */
long  duration0 , distances0 ,
      duration1 , distances1 , 
      duration2 , distances2 ,
      duration3 , distances3 ,
      duration4 , distances4 ,
      duration5 , distances5 ,
      duration6 , distances6 ,
      duration7 , distances7 ;
pinMode(trigPins[0], OUTPUT);
pinMode(trigPins[1], OUTPUT);
pinMode(trigPins[2], OUTPUT);
pinMode(trigPins[3], OUTPUT);
pinMode(trigPins[4], OUTPUT);
pinMode(trigPins[5], OUTPUT);
pinMode(trigPins[6], OUTPUT);
pinMode(trigPins[7], OUTPUT);

digitalWrite(trigPins[0], LOW);
delayMicroseconds(2);
digitalWrite(trigPins[0], HIGH);
delayMicroseconds(10);
digitalWrite(trigPins[0], LOW);
pinMode(echoPins[0], INPUT);
duration0 = pulseIn(echoPins[0], HIGH);
distances0 = microsecondsToCentimeters(duration0);
Serial.print("Sensor 1 : "); Serial.print(distances0);Serial.println(" cm");

digitalWrite(trigPins[1], LOW);
delayMicroseconds(2);
digitalWrite(trigPins[1], HIGH);
delayMicroseconds(10);
digitalWrite(trigPins[1], LOW);
pinMode(echoPins[1], INPUT);
duration1 = pulseIn(echoPins[1], HIGH);
distances1 = microsecondsToCentimeters(duration1);
Serial.print("Sensor 2 : "); Serial.print(distances1);Serial.println(" cm");

digitalWrite(trigPins[2], LOW);
delayMicroseconds(2);
digitalWrite(trigPins[2], HIGH);
delayMicroseconds(10);
digitalWrite(trigPins[2], LOW);
pinMode(echoPins[2], INPUT);
duration2 = pulseIn(echoPins[2], HIGH);
distances2 = microsecondsToCentimeters(duration2);
Serial.print("Sensor 3 : "); Serial.print(distances2);Serial.println(" cm");

digitalWrite(trigPins[3], LOW);
delayMicroseconds(2);
digitalWrite(trigPins[3], HIGH);
delayMicroseconds(10);
digitalWrite(trigPins[3], LOW);
pinMode(echoPins[3], INPUT);
duration3 = pulseIn(echoPins[3], HIGH);
distances3 = microsecondsToCentimeters(duration3);
Serial.print("Sensor 4 : "); Serial.print(distances3);Serial.println(" cm");

digitalWrite(trigPins[4], LOW);
delayMicroseconds(2);
digitalWrite(trigPins[4], HIGH);
delayMicroseconds(10);
digitalWrite(trigPins[4], LOW);
pinMode(echoPins[4], INPUT);
duration4 = pulseIn(echoPins[4], HIGH);
distances4 = microsecondsToCentimeters(duration4);
Serial.print("Sensor 5 : "); Serial.print(distances4);Serial.println(" cm");

digitalWrite(trigPins[5], LOW);
delayMicroseconds(2);
digitalWrite(trigPins[5], HIGH);
delayMicroseconds(10);
digitalWrite(trigPins[5], LOW);
pinMode(echoPins[5], INPUT);
duration5 = pulseIn(echoPins[5], HIGH);
distances5 = microsecondsToCentimeters(duration5);
Serial.print("Sensor 6 : "); Serial.print(distances5);Serial.println(" cm");

digitalWrite(trigPins[6], LOW);
delayMicroseconds(2);
digitalWrite(trigPins[6], HIGH);
delayMicroseconds(10);
digitalWrite(trigPins[6], LOW);
pinMode(echoPins[6], INPUT);
duration6 = pulseIn(echoPins[6], HIGH);
distances6 = microsecondsToCentimeters(duration6);
Serial.print("Sensor 7 : "); Serial.print(distances6);Serial.println(" cm");

digitalWrite(trigPins[7], LOW);
delayMicroseconds(2);
digitalWrite(trigPins[7], HIGH);
delayMicroseconds(10);
digitalWrite(trigPins[7], LOW);
pinMode(echoPins[7], INPUT);
duration7 = pulseIn(echoPins[7], HIGH);
distances7 = microsecondsToCentimeters(duration7);
Serial.print("Sensor 8 : "); Serial.print(distances7);Serial.println(" cm");

  int valueA1 = digitalRead(pinA1);
  int valueB1 = digitalRead(pinB1);
  int valueA2 = digitalRead(pinA2);
  int valueB2 = digitalRead(pinB2);
  int airGrade1 = -1;
  int airGrade2 = -1;
  Serial.println("pinA1(H/L)=" + (String)valueA1 );
  Serial.println("pinB1(H/L)=" + (String)valueB1 );
  Serial.println("pinA2(H/L)=" + (String)valueA2 );
  Serial.println("pinB2(H/L)=" + (String)valueB2 );
  if      (valueA1 == LOW && valueB1 == LOW)  { airGrade1 = 3; } //อากศดี
  else if(valueA1 == LOW && valueB1 == HIGH)  { airGrade1 = 2; } 
  else if(valueA1 == HIGH && valueB1 == LOW)  { airGrade1 = 1; }
  else if(valueA1 == HIGH && valueB1 == HIGH) { airGrade1 = 0; } //อากาศแย่มาก
  if      (valueA2 == LOW && valueB2 == LOW)  { airGrade2 = 3; }
  else if(valueA2 == LOW && valueB2 == HIGH)  { airGrade2 = 2; }
  else if(valueA2 == HIGH && valueB2 == LOW)  { airGrade2 = 1; }
  else if(valueA2 == HIGH && valueB2 == HIGH) { airGrade2 = 0; }
  Serial.println("Air Grade 1 0~3 =" + (String)airGrade1 );     //แสดงคุณภาพอากาศ
  Serial.println("Air Grade 2 0~3 =" + (String)airGrade2 );


    if( (airGrade1 == 3 && airGrade2 == 3) && air4 == 0  )
    {     LINE.notify(" ไม่มีกลิ่นไม่พึงประสงค์ ");
          Serial.println(" ไม่มีกลิ่นไม่พึงประสงค์ ");
          air4 = 1;   air3 = 0;   air2 = 0;   air1 = 0; }
    else if((airGrade1 == 2 && airGrade2 == 2) && air3 == 0  )
    {     LINE.notify(" มีกลิ่นไม่พึงประสงค์ ระดับ 1 ");  
          Serial.println(" มีกลิ่นไม่พึงประสงค์ ระดับ 1 ");  
          air4 = 0;   air3 = 1;   air2 = 0;   air1 = 0; }
    else if((airGrade1 == 1 && airGrade2 == 1) && air2 == 0  )
    {     LINE.notify(" มีกลิ่นไม่พึงประสงค์ ระดับ 2 ");   
          Serial.println(" มีกลิ่นไม่พึงประสงค์ ระดับ 2 ");
          air4 = 0;   air3 = 0;   air2 = 1;   air1 = 0; }
    else if((airGrade1 == 0 && airGrade2 == 0) && air1 == 0  )
    {     LINE.notify(" มีกลิ่นไม่พึงประสงค์ ระดับ 3 ");          
          Serial.println(" มีกลิ่นไม่พึงประสงค์ ระดับ 3 ");  
          air4 = 0;   air3 = 0;   air2 = 0;   air1 = 1; }


    int detect  = 100 ;
    int minimum = 50 ; 
    /*int hc1 = 0 , hc1 = 0 , hc2 = 0 , hc3 = 0 , hc4 = 0, 
        hc5 = 0 , hc6 = 0 , hc7 = 0 ;
    if( ((distances0 <= detect) && (distances0 >= minimum ) ) && hc0 == 0  )
    {     LINE.notify("ถังขยะใบที่ 1 เต็ม");    hc0 = 1;      }
    else if( ((distances0 > detect) && (distances0 >= minimum ) ) && hc0 == 1  )
    {     LINE.notify("ถังขยะใบที่ 1 เต็ม");    hc0 = 0;      }

    if( ((distances1 <= detect) && (distances1 >= minimum ) ) && hc1 == 0  )
    {    LINE.notify("ถังขยะใบที่ 2 เต็ม");     hc1 = 1;}
    else if( ((distances1 > detect) && (distances1 >= minimum ) ) && hc1 == 1  )
    {     LINE.notify("ถังขยะใบที่ 2 เต็ม");    hc1 = 0;      }

    if( ((distances2 <= detect) && (distances2 >= minimum ) ) && hc2 == 0  )
    {    LINE.notify("ถังขยะใบที่ 3 เต็ม");     hc2 = 1;}
    else if( ((distances2 > detect) && (distances2 >= minimum ) ) && hc2 == 1  )
    {     LINE.notify("ถังขยะใบที่ 3 เต็ม");    hc2 = 0;      }

    if( ((distances3 <= detect) && (distances3 >= minimum ) ) && hc3 == 0  )
    {    LINE.notify("ถังขยะใบที่ 4 เต็ม");     hc3 = 1;}
    else if( ((distances3 > detect) && (distances3 >= minimum ) ) && hc3 == 1  )
    {     LINE.notify("ถังขยะใบที่ 4 เต็ม");    hc3 = 0;      } 

    if( ((distances4 <= detect) && (distances4 >= minimum ) ) && hc4 == 0  )
    {    LINE.notify("ถังขยะใบที่ 5 เต็ม");     hc4 = 1;}
    else if( ((distances4 > detect) && (distances4 >= minimum ) ) && hc4 == 1  )
    {     LINE.notify("ถังขยะใบที่ 5 เต็ม");    hc4 = 0;      } 

    if( ((distances5 <= detect) && (distances5 >= minimum ) ) && hc5 == 0  )
    {    LINE.notify("ถังขยะใบที่ 6 เต็ม");     hc5 = 1;}
    else if( ((distances5 > detect) && (distances5 >= minimum ) ) && hc5 == 1  )
    {     LINE.notify("ถังขยะใบที่ 6 เต็ม");    hc5 = 0;      } 

    if( ((distances6 <= detect) && (distances6 >= minimum ) ) && hc6 == 0  )
    {    LINE.notify("ถังขยะใบที่ 7 เต็ม");    hc6 = 1;}
    else if( ((distances6 > detect) && (distances6 >= minimum ) ) && hc6 == 1  )
    {    LINE.notify("ถังขยะใบที่ 7 เต็ม");    hc6 = 0;      } 

    if( ((distances7 <= detect) && (distances7 >= minimum ) ) && hc7 == 0  )
    {    LINE.notify("ถังขยะใบที่ 8 เต็ม");    hc7 = 1;}
    else if( ((distances7 > detect) && (distances7 >= minimum ) ) && hc7 == 1  )
    {    LINE.notify("ถังขยะใบที่ 8 เต็ม");    hc7 = 0;      } */
    
    int hc[8] = {0}; // ประกาศตัวแปร hc เพื่อเก็บสถานะของถังขยะทั้ง 8 ใบ
    int distances[8]; // ประกาศตัวแปร distances เพื่อเก็บระยะทางจากเซ็นเซอร์ HCSR04 ของถังขยะทั้ง 8 ใบ
    for (int i = 0; i < 8; ++i) {
        if (((distances[i] <= detect) && (distances[i] >= minimum)) && hc[i] == 0) {
            LINE.notify("ถังขยะใบที่ " + String(i + 1) + " เต็ม");
            Serial.println("ถังขยะใบที่ " + String(i + 1) + " เต็ม");
            hc[i] = 1;
        } else if (((distances[i] > detect) && (distances[i] >= minimum)) && hc[i] == 1) {
            LINE.notify("ถังขยะใบที่ " + String(i + 1) + " ว่าง");
            Serial.println("ถังขยะใบที่ " + String(i + 1) + " ว่าง");
            hc[i] = 0;
        }
    }



if (WiFi.status() == WL_CONNECTED) {             //http mysql
      HTTPClient http;
      String url = serverName;
      url += "&airGrade_1=";       url +=  airGrade1;
      url += "&airGrade_2=";       url +=  airGrade2;
      url += "&rubbish_1=";     url +=  hc[0];
      url += "&rubbish_2=";     url +=  hc[1];
      url += "&rubbish_3=";     url +=  hc[2];
      url += "&rubbish_4=";     url +=  hc[3];
      url += "&rubbish_5=";     url +=  hc[4];
      url += "&rubbish_6=";     url +=  hc[5];
      url += "&rubbish_7=";     url +=  hc[6];
      url += "&rubbish_8=";     url +=  hc[7];
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

//delay(500);

} //loop



long microsecondsToCentimeters(long microseconds) {
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    return microseconds / 29 / 2;
}

/*long measureDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    //return pulseIn(echoPin, HIGH);
}*/


