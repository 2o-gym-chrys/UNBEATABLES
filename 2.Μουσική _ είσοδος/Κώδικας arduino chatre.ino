#include <SoftwareSerial.h>

// DFPlayer on SoftwareSerial (pins 5 = RX, 6 = TX)
SoftwareSerial mySerial(5, 6); // RX, TX

// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;

// Playback timing
unsigned long playbackStartTime = 0;
unsigned long playbackDuration = 10000; // 10 seconds
unsigned long lastTriggerTime = 0;
unsigned long debounceDelay = 3000; // Optional delay between triggers
bool isPlaying = false;

// DFPlayer command variables
byte command[6];
byte commandLength;
int checkSum = 0;

void sendCommand() {
  for (int q = 0; q < commandLength; q++) {
    mySerial.write(command[q]);
    Serial.print(command[q], HEX);
    Serial.print(" ");
  }
  Serial.println("End");
}

// Set volume (0–31)
void setVolume(byte vol) {
  command[0] = 0xAA;
  command[1] = 0x13;
  command[2] = 0x01;
  command[3] = vol;
  checkSum = 0;
  for (int q = 0; q < 4; q++) checkSum += command[q];
  command[4] = lowByte(checkSum);
  commandLength = 5;
  sendCommand();
}

// Set random playback mode
void setRandomMode() {
  command[0] = 0xAA;
  command[1] = 0x18;
  command[2] = 0x01;
  command[3] = 0x03; // Random mode
  checkSum = 0;
  for (int q = 0; q < 4; q++) checkSum += command[q];
  command[4] = lowByte(checkSum);
  commandLength = 5;
  sendCommand();
}

// Play a track (random mode will randomly pick one)
void playTrack() {
  command[0] = 0xAA;
  command[1] = 0x02;
  command[2] = 0x00;
  command[3] = 0xAC;
  commandLength = 4;
  sendCommand();
}

// Stop playback
void stopPlayback() {
  command[0] = 0xAA;
  command[1] = 0x03;
  command[2] = 0x00;
  command[3] = 0xAD;
  commandLength = 4;
  sendCommand();
}

// Measure distance using ultrasonic sensor
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000); // 25ms timeout
  long distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("System Initialized");

  delay(500); // Allow DFPlayer to boot

  setVolume(17);      // Set desired volume
  delay(100);
  setRandomMode();    // Enable random playback
  delay(100);
}

void loop() {
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  unsigned long currentMillis = millis();

  // Trigger playback on close proximity
  if (distance > 0 && distance < 20) {
    if (currentMillis - lastTriggerTime > debounceDelay) {
      playTrack();
      Serial.println("Triggered playback");
      playbackStartTime = currentMillis;
      lastTriggerTime = currentMillis;
      isPlaying = true;
    }
  }

  // Stop after 10 seconds of playback
  if (isPlaying && (currentMillis - playbackStartTime >= playbackDuration)) {
    stopPlayback();
    Serial.println("Playback stopped after 10 seconds");
    isPlaying = false;
  }

  delay(200);
}
