#include <Wire.h> 
int pinA = 18; // A
int pinB = 19; // B
void setup()

{
  Serial.begin(115200);
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);  
}

void loop(){

  int valueA = digitalRead(pinA);
  int valueB = digitalRead(pinB);
  int airGrade = -1;
  Serial.println("pinA(H/L)=" + (String)valueA + " ");
  Serial.println("pinB(H/L)=" + (String)valueB + " ");

if(valueA == LOW && valueB == LOW)
  {     airGrade = 3;     }
  else if(valueA == LOW && valueB == HIGH)
  {     airGrade = 2;     }
  else if(valueA == HIGH && valueB == LOW)
  {     airGrade = 1;     }
  else if(valueA == HIGH && valueB == HIGH)
  {     airGrade = 0;     }
  Serial.println("Air Grade 0~3=" + (String)airGrade + " ");
  delay(800);

}
