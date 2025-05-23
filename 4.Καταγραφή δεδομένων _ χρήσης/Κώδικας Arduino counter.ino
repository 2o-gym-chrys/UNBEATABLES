 #include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 7
#define ECHO_PIN 6
#define LED_PIN 13

const int thresholdDistance = 60; // in cm
const unsigned long detectionCooldown = 2000;

int peopleCount = 0;
bool personDetected = false;
unsigned long lastDetectionTime = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Address may vary: 0x27 or 0x3F

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
 
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("People: 0");
  lcd.setCursor(0, 1);
  lcd.print("Status: OK");
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print("People: ");
  lcd.print(peopleCount);
  lcd.print("   "); // clear old digits if needed

  lcd.setCursor(0, 1);
  if (peopleCount >= 10) {
    lcd.print("Status: CLEAN!  ");
    digitalWrite(LED_PIN, HIGH);
  } else {
    lcd.print("Status: OK      ");
    digitalWrite(LED_PIN, LOW);
  }
}

void loop() {
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < thresholdDistance && !personDetected && millis() - lastDetectionTime > detectionCooldown) {
    personDetected = true;
    peopleCount++;
    lastDetectionTime = millis();
    updateLCD();
  }

  if (distance > thresholdDistance) {
    personDetected = false;
  }

  delay(100);
}
