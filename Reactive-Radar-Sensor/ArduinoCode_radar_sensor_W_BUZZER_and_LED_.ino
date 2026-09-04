#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
const int ledPin = 5;

long duration;
int distance;
const int buzzerPin = 6;
Servo myServo;
void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin is the servo motor attached
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance(); 

    // Turns the LED on if something is detected within 20cm, off otherwise
    if (distance < 20) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    if (distance < 20) {
  digitalWrite(ledPin, HIGH);
  tone(buzzerPin, 1000); // beeps at 1000Hz
} else {
  digitalWrite(ledPin, LOW);
  noTone(buzzerPin);
}
    Serial.print(i);        
    Serial.print(",");      
    Serial.print(distance); 
    Serial.print(".");
  }
  // Repeats the previous lines from 165 to 15 degrees
  
  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();

    if (distance < 20) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    if (distance < 20) {
  digitalWrite(ledPin, HIGH);
  tone(buzzerPin, 1000); // beeps at 1000Hz
} else {
  digitalWrite(ledPin, LOW);
  noTone(buzzerPin);
}
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance = duration * 0.034 / 2;
  return distance;
  
}
