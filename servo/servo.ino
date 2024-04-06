#include <ESP32Servo.h>
 
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position
 
void setup() {
  
Serial.begin(9600);
  myservo.attach(19);  // attaches the servo on pin 9 to the servo object
}
 
void loop() {

Serial.println("start"); 
  for (pos = 35; pos <= 155; pos += 1) { // goes from 35 degrees to 155 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }

delay(1000);

  for (pos = 155; pos >= 35; pos -= 1) { // goes from 155 degrees to 35 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }//155

delay(1000);


}