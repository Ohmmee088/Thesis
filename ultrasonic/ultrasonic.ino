
 const int trigPin = 13;     int inPin = 12;  
const int trigPin2 = 14;    int inPin2 = 27;  
const int trigPin3 = 26;    int inPin3 = 35;  
const int trigPin4 = 25;    int inPin4 = 34;  

//const int trigPin4 = 35;    int inPin5 = 34;
const int trigPin5 = 33;    int inPin5 = 39;
const int trigPin6 = 32;    int inPin6 = 36;
const int trigPin7 = 4;    int inPin7 = 16;
const int trigPin8 = 17;    int inPin8 = 5;

/*const int trigPins[] = {32, 25, 27, 12, 15, 0, 16, 5};
const int echoPins[] = {33, 26, 14, 13, 2, 4, 17, 18};
const int numSensors = sizeof(trigPins) / sizeof(trigPins[0]);*/

void setup() 
{
    Serial.begin(115200);
    /*for (int i = 0; i < numSensors; i++) {
        pinMode(trigPins[i], OUTPUT);
        pinMode(echoPins[i], INPUT);
    }*/
}
 

void loop()
{
long  duration , cm ,
      duration2, cm2 , 
      duration3 , cm3 ,
      duration4 , cm4 ,
      duration5 , cm5 ,
      duration6 , cm6 ,
      duration7 , cm7 ,
      duration8 , cm8 ;


 
pinMode(trigPin, OUTPUT);
pinMode(trigPin2, OUTPUT);
pinMode(trigPin3, OUTPUT);
pinMode(trigPin4, OUTPUT);
pinMode(trigPin5, OUTPUT);
pinMode(trigPin6, OUTPUT);
pinMode(trigPin7, OUTPUT);
pinMode(trigPin8, OUTPUT);


digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
pinMode(inPin, INPUT);
duration = pulseIn(inPin, HIGH);
cm = microsecondsToCentimeters(duration);
 
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
pinMode(inPin2, INPUT);
duration2 = pulseIn(inPin2, HIGH);
cm2 = microsecondsToCentimeters(duration2);

digitalWrite(trigPin3, LOW);
delayMicroseconds(2);
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);
pinMode(inPin3, INPUT);
duration3 = pulseIn(inPin3, HIGH);
cm3 = microsecondsToCentimeters(duration3);

digitalWrite(trigPin4, LOW);
delayMicroseconds(2);
digitalWrite(trigPin4, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin4, LOW);
pinMode(inPin4, INPUT);
duration4 = pulseIn(inPin4, HIGH);
cm4 = microsecondsToCentimeters(duration4);

digitalWrite(trigPin5, LOW);
delayMicroseconds(2);
digitalWrite(trigPin5, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin5, LOW);
pinMode(inPin5, INPUT);
duration5 = pulseIn(inPin5, HIGH);
cm5 = microsecondsToCentimeters(duration5);

digitalWrite(trigPin6, LOW);
delayMicroseconds(2);
digitalWrite(trigPin6, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin6, LOW);
pinMode(inPin6, INPUT);
duration6 = pulseIn(inPin6, HIGH);
cm6 = microsecondsToCentimeters(duration6);

digitalWrite(trigPin7, LOW);
delayMicroseconds(2);
digitalWrite(trigPin7, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin7, LOW);
pinMode(inPin7, INPUT);
duration7 = pulseIn(inPin7, HIGH);
cm7 = microsecondsToCentimeters(duration7);

digitalWrite(trigPin8, LOW);
delayMicroseconds(2);
digitalWrite(trigPin8, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin8, LOW);
pinMode(inPin8, INPUT);
duration8 = pulseIn(inPin8, HIGH);
cm8 = microsecondsToCentimeters(duration8);

Serial.print("s1  ");
Serial.print(cm);
Serial.print("cm");
Serial.println( );

Serial.print("s2  ");
Serial.print(cm2);
Serial.print("cm");
Serial.println( );

Serial.print("s3  ");
Serial.print(cm3);
Serial.print("cm");
Serial.println();

Serial.print("s4  ");
Serial.print(cm4);
Serial.print("cm");
Serial.println();

Serial.print("s5  ");
Serial.print(cm5);
Serial.print("cm");
Serial.println();

Serial.print("s6  ");
Serial.print(cm6);
Serial.print("cm");
Serial.println();

Serial.print("s7  ");
Serial.print(cm7);
Serial.print("cm");
Serial.println();

Serial.print("s8  ");
Serial.print(cm8);
Serial.print("cm");
Serial.println();

Serial.println();
//delay(500);
}
 

long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}