#include <LiquidCrystal.h>
#include <DHT.h>

// Initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define rotary encoder pins
const int encoderCLK = 8;
const int encoderDT = 9;
const int encoderSW = 10;

// Define DHT11 sensor pin
const int dhtPin = A0;
DHT dht(dhtPin, DHT11);

// Define variables for holding encoder state
int lastCLKState;
int currentCLKState;
float encoderValue = 0;

// Define variables for temperature setting mode
bool tempSettingMode = false;
float setTemperature = 20; // Default set temperature

void setup() {
  // Set encoder pins as inputs with internal pull-ups
  pinMode(encoderCLK, INPUT_PULLUP);
  pinMode(encoderDT, INPUT_PULLUP);
  pinMode(encoderSW, INPUT_PULLUP);

  // Start the LCD display
  lcd.begin(16, 2);

  // Print initial message
  lcd.print("Set Temp: ");
  lcd.print(setTemperature);
  lcd.setCursor(0, 1);
  lcd.print("Room Temp: ");
}

void loop() {
  // Read temperature from DHT11 sensor
  float temperature = dht.readTemperature();

  // Print the current temperature on the LCD
  lcd.setCursor(11, 1);
  lcd.print(temperature);
  lcd.print(" C");

  // If the encoder button is pressed, toggle temperature setting mode
  if (digitalRead(encoderSW) == LOW) {
    tempSettingMode = !tempSettingMode;
    delay(100); // Debounce delay
  }

  // If in temperature setting mode, adjust setTemperature using the rotary encoder
  if (tempSettingMode) {
    // Read the current state of the CLK pin
    currentCLKState = digitalRead(encoderCLK);

    // Check for a state change of the CLK pin
    if (currentCLKState != lastCLKState) {
      // If DT pin is different from CLK pin, increment/decrement setTemperature
      if (digitalRead(encoderDT) != currentCLKState) {
        setTemperature += 0.5;
      } else {
        setTemperature -= 0.5;
      }
      
      // Print the set temperature on the LCD
      lcd.setCursor(9, 0);
      lcd.print("    "); // Clear previous value
      lcd.setCursor(9, 0);
      lcd.print(setTemperature);
    }

    // Update lastCLKState with the current state for the next iteration
    lastCLKState = currentCLKState;
  }

  // Delay before the next iteration
  delay(100);
}
