#include <DHT.h>
#include <LiquidCrystal.h>

// Define pin connections for components
#define DHTPIN A0       // DHT11 sensor pin
#define RELAY_PIN 6     // Relay pin

// Initialize DHT sensor
#define DHTTYPE DHT11   // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

// Initialize LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define rotary encoder pins
const int encoderCLK = 8;
const int encoderDT = 9;
const int encoderSW = 10;

// Define variables for holding encoder state
int lastCLKState;
int currentCLKState;
long encoderValue = 25; // Default set temperature

// Set temperature variable
float setTemperature = 25;  // Default set temperature

void setup() {
  // Initialize DHT sensor
  dht.begin();

  // Set relay pin as output
  pinMode(RELAY_PIN, OUTPUT);
  // Ensure relay is initially off
  digitalWrite(RELAY_PIN, LOW);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Set Temp: ");
  lcd.print(setTemperature);
  
  // Set encoder pins as inputs with internal pull-ups
  pinMode(encoderCLK, INPUT_PULLUP);
  pinMode(encoderDT, INPUT_PULLUP);
  pinMode(encoderSW, INPUT_PULLUP);
  
  // Read initial state of CLK pin
  lastCLKState = digitalRead(encoderCLK);
}

void loop() {
  // Read temperature from DHT11 sensor
  float roomTemperature = dht.readTemperature();

  // Print temperature to LCD
  lcd.setCursor(0, 1);
  lcd.print("Room Temp: ");
  lcd.print(roomTemperature);

  // Compare room temperature with set temperature
  if (roomTemperature <= setTemperature) {
    // If room temperature is equal to or below set temperature, turn off the relay
    digitalWrite(RELAY_PIN, LOW);
  } else {
    // Otherwise, keep the relay turned on
    digitalWrite(RELAY_PIN, HIGH);
  }

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

    // Update set temperature
    setTemperature = encoderValue;

    // Print the encoder value to LCD
    lcd.setCursor(9, 0); // Adjusted cursor position
    lcd.print("    ");   // Clear the existing number
    lcd.setCursor(9, 0); // Adjusted cursor position
    lcd.print(setTemperature);
  }

  // Update lastCLKState with current state for next iteration
  lastCLKState = currentCLKState;
}
