float temperature;  // Global or pass from sensor read function

void switchControl() {
  Serial.println("Entering switchControl...");

  while (digitalRead(onSwithPin) == 1) {
    getTempHum();  // Update temperature and humidity
    int grainSieve = digitalRead(grainSwitch);
    int coffeeSieve = digitalRead(coffeSwitch);

//    Serial.print("Temp: ");
//    Serial.println(temperature);
//    Serial.print("Grain: ");
//    Serial.println(grainSieve);
//    Serial.print("Coffee: ");
//    Serial.println(coffeeSieve);

    // Bulb control: turn off if temp too high
    if (temperature > 50.0) {
      digitalWrite(relayBulb, LOW);  // Safety: turn off the bulb
    } else {
      digitalWrite(relayBulb, HIGH); // Turn on if needed (see below)
    }

    if (grainSieve == 1 && coffeeSieve == 0) {
      if (temperature <= 50.0) {
        digitalWrite(relayBulb, HIGH); // Bulb ON only if temp is safe
      }
      for (int x = 0; x < stepsPerRevolution; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(400);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(400);
      }
    } else if (coffeeSieve == 1 && grainSieve == 0) {
      if (temperature <= 50.0) {
        digitalWrite(relayBulb, HIGH); // Bulb ON only if temp is safe
      }
      for (int x = 0; x < stepsPerRevolution; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(800);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(800);
      }
    } else {
      // No valid selection
      digitalWrite(stepPin, LOW);
      digitalWrite(relayBulb, LOW);
      buzzer_beep();
    }

    delay(100); // Debounce
  }

  // Turn off outputs when switch is off
  digitalWrite(stepPin, LOW);
  digitalWrite(relayBulb, LOW);
  Serial.println("Exiting switchControl...");
}
