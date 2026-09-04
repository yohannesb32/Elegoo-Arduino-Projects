# Reactive Radar Sensor 📡

Hello! This is my second project with my Arduino, an ultrasonic sensor that is attached to a
Servo, and rotating in a 180 degree plane, detects any objects in the premise and lets the user
know, by letting off an LED and releasing sound from an active buzzer. This was my first time
really branching off and creating one of my own real projects using the lessons I learned in the
Elegoo Most Complete Starter Kit.

## What it uses
- Arduino Mega 2560
- Ultrasonic Sensor (HC-SR04)
- SG90 Servo Motor
- Active Buzzer
- Red LED

## Wiring
| Component | Pin |
|---|---|
| Ultrasonic Sensor  TRIG | D9 |
| Ultrasonic Sensor  ECHO | D10 |
| Servo Signal  | D6 |
| Servo VCC | 5V |
| Servo GND | GND |
| Red LED (Anode/Long Side) | D7 (through 220 resistor) |
| Red LED (Cathode/Short Side) | GND |
| Buzzer Positive | D8 |
| Buzzer Negative | GND |


## How it works
1. The servo rotates the ultrasonic sensor back and forth across a 180 degree sweep.
2. As it sweeps, the ultrasonic sensor keeps checking the distance in front of it. If something gets within a limited 25cm range, it counts that as an object detected.
3. When an object is detected, the red LED turns on to give a visual signal that something's there.
4. At the same time, the active buzzer goes off to give an audible alert too.

## What I learned
- Getting the Arduino and Processing to actually talk to each other over serial was trickier than I expected, but once I figured out how to send the servo angle and distance reading together, I could get Processing to draw a radar sweep on screen that matched what the sensor was doing in real life. Took a few tries to get the numbers lined up, but seeing it actually sweep and pick up objects in real time made it worth it.
