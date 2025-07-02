#include <DHT11.h>
#define  dirPin         4
#define  stepPin        2
#define grainSwitch    13
#define coffeSwitch    14
#define onSwithPin     34
#define relayBulb      26
#define buzzer         23
const int stepsPerRevolution = 10000;
DHT11 dht11(18);

void setup()
{
  Serial.begin(115200);

  // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(relayBulb, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(grainSwitch, INPUT);
  pinMode(coffeSwitch, INPUT);
  pinMode (onSwithPin, INPUT);

  buzzer_beep();
}
void loop()
{
  // Set motor direction clockwise
  digitalWrite(dirPin, HIGH);
  switchControl();

}
