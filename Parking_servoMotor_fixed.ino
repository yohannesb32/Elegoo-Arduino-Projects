#include <Servo.h>

Servo myservo;

int pos = 0;
int cm = 0;

bool gateOpen = false;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() {
  digitalWrite(12, LOW);
  myservo.attach(9);
  Serial.begin(9600);
}

void loop() {
  cm = 0.01723 * readUltrasonicDistance(6, 7);

  // Debug: print distance EVERY loop, not just when triggered.
  // Watch this with nothing near the sensor - if it's under 30
  // even with your hand away, the sensor/mounting is the problem,
  // not the code.
  Serial.print(cm);
  Serial.println("cm");

  if (cm < 30 && !gateOpen) {
    // Something just got close - open the gate
    for (pos = 0; pos <= 120; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
    gateOpen = true;
    delay(2000);
  }
  else if (cm >= 30 && gateOpen) {
    // Object has left - close the gate
    for (pos = 120; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    gateOpen = false;
  }

  delay(100); // short pause between sensor checks, NOT a long blocking delay
}
