#include <LiquidCrystal.h>
#include <IRremote.hpp>

// ---- Dice ----
int buttonPin = 2;
LiquidCrystal lcd(22, 23, 4, 5, 8, 7); // RS, EN, D4, D5, D6, D7

// ---- Lamp ----
int redPin = 9, greenPin = 10, bluePin = 6;

// ---- IR remote ----
#define IR_PIN 11

#define CODE_1 0xF30CFF00
#define CODE_2 0xE718FF00
#define CODE_3 0xA15EFF00
#define CODE_4 0xF708FF00
#define CODE_5 0xE31CFF00
#define CODE_6 0xA55AFF00

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  randomSeed(analogRead(A0));

  lcd.begin(16, 2);
  lcd.print("Press to roll!");

  IrReceiver.begin(IR_PIN);
}

void loop() {
  checkDiceButton();
  checkRemote();
}

// ---------- DICE ----------
void checkDiceButton() {
  if (digitalRead(buttonPin) == LOW) {
    for (int i = 0; i < 15; i++) {
      int flash = random(1, 7);
      showNumber(flash);
      delay(50 + i * 10);
    }
    int result = random(1, 7);
    showNumber(result);
    delay(300); // simple debounce
  }
}

void showNumber(int num) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You rolled:");
  lcd.setCursor(0, 1);
  lcd.print(num);
}

// ---------- LAMP ----------
void checkRemote() {
  if (IrReceiver.decode()) {
    unsigned long code = IrReceiver.decodedIRData.decodedRawData;

    if (code == CODE_1) setColor(255, 0, 0);     // red
    if (code == CODE_2) setColor(0, 255, 0);     // green
    if (code == CODE_3) setColor(0, 0, 255);     // blue
    if (code == CODE_4) setColor(255, 255, 0);   // yellow
    if (code == CODE_5) setColor(255, 0, 255);   // purple
    if (code == CODE_6) setColor(0, 255, 255);   // cyan

    IrReceiver.resume();
  }
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}