#include <LiquidCrystal.h>

// Initialize the library by associating any needed LCD interface pin
// with the Arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define rotary encoder pins
const int encoderCLK = 8;
const int encoderDT = 9;
const int encoderSW = 10;

// Define variables for holding encoder state
int lastCLKState;
int currentCLKState;
long encoderValue = 0;

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Number: ");
  
  // Set encoder pins as inputs with internal pull-ups
  pinMode(encoderCLK, INPUT_PULLUP);
  pinMode(encoderDT, INPUT_PULLUP);
  pinMode(encoderSW, INPUT_PULLUP);
  
  // Read initial state of CLK pin
  lastCLKState = digitalRead(encoderCLK);
}

void loop() {
  // Read current state of CLK pin
  currentCLKState = digitalRead(encoderCLK);

  // Check for state change of CLK pin
  if (currentCLKState != lastCLKState) {
    // If DT pin is different from CLK pin, increment encoder value
    if (digitalRead(encoderDT) != currentCLKState) {
      encoderValue++;
    } else { // Otherwise, decrement encoder value
      encoderValue--;
    }

    // Print the encoder value to LCD
    lcd.setCursor(8, 0);
    lcd.print("      "); // Clear the existing number
    lcd.setCursor(8, 0);
    lcd.print(encoderValue);
  }

  // Update lastCLKState with current state for next iteration
  lastCLKState = currentCLKState;
}
