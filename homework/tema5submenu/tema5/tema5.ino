#include <EEPROM.h>

const int photocellPin = A0;
const int ledPin1 = 4;
const int ledPin2 = 2;
const int ledPin3 = 3;
const int trigPin = 9;
const int echoPin = 10;
int mappedValue;
int photocellValue;
int duration;
int distance;
int  saveDis;
unsigned long previousMillis = 0;
const long interval = 5000;  // 5 seconds
bool submenuActive = false;
unsigned long submenuStartTime = 0;

const int EEPROM_ADDR_LDR = 100;        // EEPROM address to store LDR value
const int EEPROM_ADDR_DISTANCE = 102;   // EEPROM address to store distance value

void setup(void) {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void saveValuesToEEPROM() {
  // Save LDR value to EEPROM
  EEPROM.update(EEPROM_ADDR_LDR, mappedValue);
  // Save distance value to EEPROM
  EEPROM.update(EEPROM_ADDR_DISTANCE,saveDis);
  Serial.println("Values saved to EEPROM");
}

void readValuesFromEEPROM() {
  // Read LDR value from EEPROM
  int savedLDRValue;
  savedLDRValue = EEPROM.read(EEPROM_ADDR_LDR);
  Serial.print("Saved LDR Value: ");
  Serial.println(savedLDRValue);

  // Read distance value from EEPROM
  int savedDistanceValue;
  savedDistanceValue = EEPROM.read(EEPROM_ADDR_DISTANCE);
  Serial.print("Saved Distance Value: ");
  Serial.println(savedDistanceValue);
}

void ledControl() {
  unsigned long currentMillis = millis();

  if (currentMillis - submenuStartTime < interval) {
    // Execute LED control as long as the elapsed time is less than 5 seconds
    photocellValue = analogRead(photocellPin);
    mappedValue = map(photocellValue, 0, 1023, 0, 255);

    Serial.print("Mapped value = ");
    Serial.println(mappedValue);

    if (mappedValue < 4) {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
    } else if (mappedValue < 10) {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);
    } else if (mappedValue < 20) {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, HIGH);
    } else {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
    }
  } else {
    // 5 seconds have passed, reset LED states and exit submenu
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    submenuActive = false;
  }
}

void distanceMeasurement() {
  unsigned long currentMillis = millis();

  if (currentMillis - submenuStartTime < interval) {
    // Execute distance measurement as long as the elapsed time is less than 5 seconds
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.println(distance);
    saveDis=distance;
  } else {
    // 5 seconds have passed, exit submenu
    submenuActive = false;
  }
}

void loop(void) {
  if (!submenuActive) {
    Serial.println("Main Menu:");
    Serial.println("A) LED Control & Distance measure  B) save values c) read values");

    while (Serial.available() == 0) {}

    char menuInput = Serial.read();

    switch (menuInput) {
      case 'a':
        Serial.println("Selected Option A - LED Control");
        submenuActive = true;
        submenuStartTime = millis();  // Record the start time of the submenu
        break;
      case 'b':
        Serial.println("Selected Option B - Save values to EEPROM");
        saveValuesToEEPROM();
        submenuActive = false;
        submenuStartTime = millis();  // Record the start time of the submenu
        break;
      case 'c':
        Serial.println("Selected Option C - Read values from EEPROM");
        readValuesFromEEPROM();
        submenuActive = false;
        submenuStartTime = millis();  // Record the start time of the submenu
        break;
      default:
        Serial.println("Invalid Option. Please select A, B, or C");
    }
  } else {
    Serial.println("Submenu:");
    Serial.println("1) Execute LED Control  2) Execute Distance Measurement");

    while (Serial.available() == 0) {}

    char submenuInput = Serial.read();

    switch (submenuInput) {
      case '1':
        Serial.println("Executing LED Control");
        ledControl();
        break;
      case '2':
        Serial.println("Executing Distance Measurement");
        distanceMeasurement();
        break;
      default:
        Serial.println("Invalid Submenu Option. Please select 1 or 2");
        submenuActive=false;
    }
  }

  delay(100);
}
