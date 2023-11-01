const int buttonPin1 = 6;
const int buttonPin2 = 7;
const int buttonPin3 = 8;

const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 4;
const int ledPin4 = 5;
const int buzzer = 9;

int buttonState1 = LOW;
int buttonState2 = LOW;
int buttonState3 = LOW;

int lastButtonState1 = LOW;
int lastButtonState2 = LOW;
int lastButtonState3 = LOW;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long lastBlinkTime = 0;

const long debounceDelay = 60;
const long blinkDuration = 2000; // Adjust this for the desired blink duration

int currentLED = -1;  // To keep track of the currently lit LED

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
}

void turnOffLED(int ledPin) {
    digitalWrite(ledPin4, HIGH);
    tone(buzzer,2000);
    digitalWrite(ledPin, HIGH); // Blink the LED
    delay(200); // Adjust the blink speed if needed
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, HIGH); // Blink the LED
    delay(200); // Adjust the blink speed if needed
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(200);
    noTone(buzzer);
  digitalWrite(ledPin, LOW); // Turn off the LED after blinking
  digitalWrite(ledPin4, LOW);
}

void loop() {
  int reading1 = digitalRead(buttonPin1);
  int reading2 = digitalRead(buttonPin2);
  int reading3 = digitalRead(buttonPin3);

  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = millis();
  }
  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis();
  }
  if (reading3 != lastButtonState3) {
    lastDebounceTime3 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      if (buttonState1 == HIGH) {
        if (currentLED != ledPin1) {
          if(currentLED == ledPin3){
          turnOffLED(currentLED); // Turn off the previously lit LED with a blink
          digitalWrite(ledPin2, HIGH);
          delay(800);
          currentLED = ledPin2;
          turnOffLED(currentLED);
          digitalWrite(ledPin1, HIGH);
          }
          turnOffLED(currentLED); // Turn off the previously lit LED with a blink
          delay(400);
          digitalWrite(ledPin1, HIGH);
          currentLED = ledPin1;
        }
      }
    }
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      if (buttonState2 == HIGH) {
        if (currentLED != ledPin2) {
          turnOffLED(currentLED); // Turn off the previously lit LED with a blink
          digitalWrite(ledPin2, HIGH);
          currentLED = ledPin2;
        }
      }
    }
  }

  if ((millis() - lastDebounceTime3) > debounceDelay) {
    if (reading3 != buttonState3) {
      buttonState3 = reading3;

      if (buttonState3 == HIGH) {
        if (currentLED != ledPin3) {
          if(currentLED == ledPin1){
          turnOffLED(currentLED); // Turn off the previously lit LED with a blink
          digitalWrite(ledPin2, HIGH);
          delay(800);
          currentLED = ledPin2;
          turnOffLED(currentLED);
          digitalWrite(ledPin2, HIGH);
          }
          turnOffLED(currentLED); // Turn off the previously lit LED with a blink
          delay(400);
          digitalWrite(ledPin3, HIGH);
          currentLED = ledPin3;
        }
      }
    }
  }

  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;
}
