const int latchPin = 11;
const int clockPin = 10;
const int dataPin = 12;
const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;
int displayDigits[] = {segD1, segD2, segD3, segD4};
const int displayCount = 4;
const int encodingsNumber = 16;
byte byteEncodings[encodingsNumber] = {
  B11111100,
  B01100000,
  B11011010,
  B11110010,
  B01100110,
  B10110110,
  B10111110,
  B11100000,
  B11111110,
  B11110110,
  B11101110,
  B00111110,
  B10011100,
  B01111010,
  B10011110,
  B10001110
};
unsigned long lastIncrement = 0;
unsigned long delayCount = 100;
unsigned long number = 0;
const int buttonPin = 2;
const int pauseButtonPin = 13;
const int newButtonPin = 8; // New button on pin 8
bool isPaused = false;
int buttonState = LOW;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lapNumber = 0;
int pauseButtonState = LOW;
int lastPauseButtonState = LOW;
unsigned long lastPauseDebounceTime = 0;
int buttonPresses[] = {0,0,0,0,0,0,0,0,0,0};
int buttonPressIndex = 0;
int newButtonState = LOW;
int lastNewButtonState = LOW;
unsigned long lastNewDebounceTime = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
  writeReg(B00000001);
  digitalWrite(displayDigits[2], LOW);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(pauseButtonPin, INPUT_PULLUP);
  pinMode(newButtonPin, INPUT_PULLUP); 
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (!isPaused) {
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
        buttonState = reading;
        if (buttonState == LOW) {
          buttonPresses[lapNumber++] = number;
          number = 0;
        }
      }
    }
    lastButtonState = reading;
  }

  int pauseButtonReading = digitalRead(pauseButtonPin);
  if (pauseButtonReading != lastPauseButtonState) {
    lastPauseDebounceTime = millis();
  }
  if ((millis() - lastPauseDebounceTime) > debounceDelay) {
    if (pauseButtonReading != pauseButtonState) {
      pauseButtonState = pauseButtonReading;
      if (pauseButtonState == LOW) {
        isPaused = !isPaused;
      }
    }
  }
  lastPauseButtonState = pauseButtonReading;

  int newButtonReading = digitalRead(newButtonPin); 
    if (newButtonReading != lastNewButtonState) {
      lastNewDebounceTime = millis();
    }
    if ((millis() - lastNewDebounceTime) > debounceDelay) {
      if (newButtonReading != newButtonState) {
        newButtonState = newButtonReading;
        if (newButtonState == LOW && isPaused) {
          if(lapNumber>1)
          {lapNumber--;
          number = buttonPresses[lapNumber];}
        }
      }
    }
    lastNewButtonState = newButtonReading;

  if (!isPaused) {
    if (millis() - lastIncrement > delayCount) {
      number++;
      number %= 1000;
      lapNumber %= 10;
      lastIncrement = millis();
    }
  }

  Serial.println(number + lapNumber * 1000);
  writeNumber(number + lapNumber * 1000);
}

void writeReg(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}

void activateDisplay(int displayNumber) {
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeNumber(int number) {
  if (number > 1000) {
    activateDisplay(0);
    writeReg(byteEncodings[number / 1000]);
    writeReg(B00000000);
  }
  int currentNumber = number;
  int displayDigit = 3;
  int lastDigit = 0;
  for (int i = 0; i < 3; i++) {
    lastDigit = currentNumber % 10;
    activateDisplay(displayDigit);
    if (displayDigit == 2) {
      writeReg(byteEncodings[lastDigit] | B00000001);
    } else {
      writeReg(byteEncodings[lastDigit]);
    }
    displayDigit--;
    currentNumber /= 10;
    writeReg(B00000000);
  }
}
