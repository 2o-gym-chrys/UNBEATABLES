#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with the I2C address (0x27 is typical, but may vary)
// LCD width: 16 characters, height: 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Analog pin for the soil moisture sensor
const int soilMoisturePin = A0;

void setup() {
  // Start the serial communication for debugging
  Serial.begin(9600);

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Soil Moisture:");

  delay(1000); // Wait for a moment before reading the sensor
}

void loop() {
  // Read the analog value from the soil moisture sensor
  int sensorValue = analogRead(soilMoisturePin);

  // Map the sensor value to a range from 0 to 100 (percentage)
  int moisturePercentage = map(sensorValue, 0, 1023, 0, 100);

    lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("");
  lcd.setCursor(2,1);
  lcd.print("moisturePercentage");
   lcd.setCursor(0,2);
  lcd.print("Moisture:");
   lcd.setCursor(2,3);
  lcd.print(moisturePercentage);

  // Wait for a short time before the next reading
  delay(1000);
}
