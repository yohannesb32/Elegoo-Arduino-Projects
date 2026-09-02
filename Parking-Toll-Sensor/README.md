# Parking Toll Sensor 🚗

Hey! This is my first sensor-triggered mechanism project — an ultrasonic sensor detects when a car (or hand, for testing) gets close, and a servo lifts a toll gate arm automatically.

## What it uses
- Arduino Mega 2560
- Ultrasonic Sensor (HC-SR04)
- SG90 Servo Motor

## Wiring
| Component | Pin |
|---|---|
| Ultrasonic Trigger | Pin 6 |
| Ultrasonic Echo | Pin 7 |
| Servo Signal | Pin 9 |
| Servo Power | 5V |
| Servo Ground | GND |

The ultrasonic sensor sits facing outward (like at a toll booth entrance) and constantly measures distance. The servo is mounted with the gate arm attached to its horn, starting in the closed (down) position.

## How it works
1. Sensor continuously measures distance in front of it.
2. If something gets within 30cm, the servo sweeps up to open the gate.
3. Gate stays open while the object is still detected.
4. Once the object moves away, the servo sweeps back down to close the gate.

## What I learned
- The Serial Monitor is a separate window from the compile console (accessed via the magnifying glass icon or Ctrl+Shift+M) — tripped me up at first.
- Long `delay()` calls block the whole program, including sensor readings — had to restructure the logic to check object presence instead of using a fixed timer.
