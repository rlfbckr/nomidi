

void updateSoftPWM() {
  for (int i = 0; i < 10; i++) {
    if ((softPWMtic % softPWMres) < ledIntesity[i]) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
  softPWMtic++;
}
