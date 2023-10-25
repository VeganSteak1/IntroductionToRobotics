#define LED_PIN_1 11
#define LED_PIN_2 9
#define LED_PIN_3 6
#define POTENTIOMETER_PIN_1 A0
#define POTENTIOMETER_PIN_2 A1
#define POTENTIOMETER_PIN_3 A3

void setup()
{
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
}

void loop()
{
  int potentiometerValue1 = analogRead(POTENTIOMETER_PIN_1);
  int potentiometerValue2 = analogRead(POTENTIOMETER_PIN_2);
  int potentiometerValue3 = analogRead(POTENTIOMETER_PIN_3);
  // int brightness1 = potentiometerValue1 / 4;
  
  int brightness1 = map(potentiometerValue1, 0, 1023, 0, 255);
  int brightness2 = map(potentiometerValue2, 0, 1023, 0, 255);
  int brightness3 = map(potentiometerValue3, 0, 1023, 0, 255);
  analogWrite(LED_PIN_1, brightness1);
  analogWrite(LED_PIN_2, brightness2);
   analogWrite(LED_PIN_3, brightness3);
  // digitalWrite(LED_PIN_3,HIGH);

}
