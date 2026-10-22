# RFID Access Control System (Arduino Mega)

A card access system built on an Arduino Mega 2560. Scan an RFID tag and the system checks it against an authorized tag. An authorized scan shows **Access Granted** on an LCD, lights a green LED, and plays a rising chime. Any other tag shows **Denied**, lights a red LED, and sounds two low beeps.

Built with parts from the Elegoo Mega 2560 Most Complete Starter Kit.

## Features

- Reads the unique ID (UID) of RFID cards and key fobs with an RC522 reader
- Compares each scan to a stored authorized UID
- 16x2 LCD feedback ("Scan your card", "Access Granted", "Denied")
- Green and red LED status indicators
- Different buzzer sounds for granted (rising chime) and denied (two low beeps)
- Prints every scanned UID to the Serial Monitor, so new tags are easy to look up

## How it works

1. The RC522 reader constantly checks for a tag in range.
2. When a tag is scanned, the Arduino reads its 4 byte UID over SPI.
3. The UID is compared byte by byte to `validUID` in the code.
4. If every byte matches, the granted routine runs. Otherwise the denied routine runs.
5. After about 2 seconds the LCD returns to "Scan your card".

## Parts list

| Part | Quantity |
|---|---|
| Elegoo Mega 2560 R3 (or any Arduino Mega 2560) | 1 |
| RC522 RFID module with card and key fob | 1 |
| LCD1602 display | 1 |
| 10k potentiometer (LCD contrast) | 1 |
| Green LED | 1 |
| Red LED | 1 |
| 220 ohm resistor (LEDs) | 2 |
| Passive buzzer | 1 |
| Breadboard | 1 |
| Jumper wires | about 30 |

## Wiring

See [WIRING.md](WIRING.md) for the full wiring description. Pin summary:

| Part | Mega pins |
|---|---|
| RC522 | 53 (SDA), 52 (SCK), 51 (MOSI), 50 (MISO), 5 (RST), 3.3V, GND |
| LCD | 7 (RS), 8 (E), 9 (D4), 10 (D5), 2 (D6), 3 (D7) |
| Green LED | 12 |
| Red LED | 11 |
| Buzzer | 6 |

**Important:** the RC522 must be powered from **3.3V**, not 5V. 5V can damage it. The Mega's SPI pins (50 to 53) are also different from the Uno's, so Uno wiring guides will not work for this board.

## Setup

1. Install the **MFRC522** library: Arduino IDE, Library Manager, search "MFRC522", install. (`SPI` and `LiquidCrystal` come with the IDE.)
2. Wire everything as described in [WIRING.md](WIRING.md).
3. Open `rfid_access_control.ino`. The sketch folder must be named `rfid_access_control` so the IDE accepts it.
4. Upload the sketch and open the Serial Monitor at **9600 baud**.
5. Scan the tag you want to authorize. The Serial Monitor prints its UID, for example `UID: 11 02 1C 07`.
6. Copy that UID into the code in hex format:

   ```cpp
   byte validUID[4] = {0x11, 0x02, 0x1C, 0x07};
   ```

7. Re-upload. The authorized tag should now give Access Granted, and every other tag should give Denied.

## Usage

| Scan | Serial Monitor | LCD | LED | Sound |
|---|---|---|---|---|
| Authorized tag | MATCH | Access Granted | Green | Rising chime |
| Any other tag | NO MATCH | Denied | Red | Two low beeps |

## Troubleshooting

| Problem | Likely cause |
|---|---|
| Everything says Denied | `validUID` still has the placeholder values. Replace them with your tag's real UID |
| Nothing prints in the Serial Monitor | Baud rate is not 9600, or the wrong COM port is selected |
| Reader does nothing | Recheck the SPI wiring (53, 52, 51, 50, 5) and that the module is on 3.3V |
| LCD is lit but blank or shows solid blocks | Turn the contrast potentiometer |
| LED does not light | LED is backwards (long leg toward the pin through the resistor, short leg to GND) |
| Buzzer is silent | Make sure it is the passive buzzer, on pin 6 and GND |
| Old behavior after editing code | The upload failed. Wait for "Done uploading" and check for red errors |

## What I learned

- RFID tags are identified by a UID, and the RC522 talks to the Arduino over SPI
- SPI pins are board specific (the Mega uses 50 to 53)
- The RC522 is a 3.3V device, so voltage levels matter when mixing parts
- Planning pin assignments up front avoids conflicts between the LCD, LEDs, and reader
- Building and testing one part at a time (reader, then LEDs, then LCD, then buzzer) makes bugs much easier to find