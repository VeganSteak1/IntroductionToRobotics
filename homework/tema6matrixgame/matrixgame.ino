#include <LedControl.h>
  byte wall[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
  };
int DIN = 12;
int CS = 10;
int CLK = 11;
const int buttonPin = 2;
int initX = 1;
int initY = 1;
int xValue = 0;
int yValue = 0;
const int a1 = A1;
const int a0 = A0;
int lastBlinkTime2 = 0;
LedControl lc = LedControl(DIN, CLK, CS, 0);

void setup() {
  Serial.begin(9600);
  pinMode(a1, INPUT);
  pinMode(a0, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  lc.shutdown(0, false);
  lc.setIntensity(0, 15);
  lc.clearDisplay(0);
  printByte(wall);
}

void joystick() {
  static unsigned long lastBlinkTime = 0;
  static boolean playerVisible = true;
  static boolean blink = false;
  xValue = analogRead(A0);
  yValue = analogRead(A1);
  char x_translate = map(xValue, 1021, 0, 0, 4);
  char y_translate = map(yValue, 1021, 0, 0, 4);
  Serial.print("x = ");
  Serial.print(initX);
  Serial.print(", y = ");
  Serial.println(initY);

  lc.setLed(0, initX, initY, false);

  if (x_translate == 4) {
    if (initX < 7 && wall[initX + 1][initY] != 1) {
      initX++;
    }
  } else if (x_translate == 0) {
    if (initX > 0 && wall[initX - 1][initY] != 1) {
      initX--;
    }
  }
  if (y_translate == 4) {
    if (initY < 7 && wall[initX][initY + 1] != 1) {
      initY++;
    }
  } else if (y_translate == 0) {
    if (initY > 0 && wall[initX][initY - 1] != 1) {
      initY--;
    }
  }

  lc.setLed(0, initX, initY, playerVisible);

  unsigned long currentTime = millis();
  if (currentTime - lastBlinkTime >= 200) {
    playerVisible = !playerVisible;
    lastBlinkTime = currentTime;
  }

  if (digitalRead(buttonPin) == LOW) {

    unsigned long previousMillisLoop = 0;
    const long intervalLoop = 50;

    unsigned long currentMillisLoop = millis();

    lc.setLed(0, initX, initY - 1, true);
    wall[initX][initY - 1] = 0;
    lc.setLed(0, initX, initY + 1, true);
    wall[initX][initY + 1] = 0;
    lc.setLed(0, initX - 1, initY, true);
    wall[initX - 1][initY] = 0;
    lc.setLed(0, initX + 1, initY, true);
    wall[initX + 1][initY] = 0;

    if (currentMillisLoop - previousMillisLoop >= intervalLoop) {

      previousMillisLoop = currentMillisLoop;

      lc.setLed(0, initX, initY - 1, false);
      lc.setLed(0, initX, initY + 1, false);
      lc.setLed(0, initX - 1, initY, false);
      lc.setLed(0, initX + 1, initY, false);
    }

    if (currentMillisLoop - previousMillisLoop >= intervalLoop) {

      previousMillisLoop = currentMillisLoop;

      lc.setLed(0, initX, initY - 1, true);
      lc.setLed(0, initX, initY + 1, true);
      lc.setLed(0, initX - 1, initY, true);
      lc.setLed(0, initX + 1, initY, true);
    }

    if (currentMillisLoop - previousMillisLoop >= intervalLoop) {

      previousMillisLoop = currentMillisLoop;

      lc.setLed(0, initX, initY - 1, false);
      lc.setLed(0, initX, initY + 1, false);
      lc.setLed(0, initX - 1, initY, false);
      lc.setLed(0, initX + 1, initY, false);
    }

  }
}

unsigned long previousMillisLoop = 0;
const long intervalLoop = 200;

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisLoop >= intervalLoop) {

    previousMillisLoop = currentMillis;

    joystick();
  }

}

void printByte(byte test[8][8]) {
  int i = 0;
  for (i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (test[i][j] == 0)
        lc.setLed(0, i, j, false);
      else
        lc.setLed(0, i, j, true);
    }
  }
}