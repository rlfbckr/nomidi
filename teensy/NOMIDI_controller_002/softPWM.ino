void updateSoftPWM() {
  for (int i = 0; i < 10; i++) {
    if ((softPWMtic % softPWMres) < ledIntesity[i]) {
      digitalWrite(LED[i], HIGH);
    } else {
      digitalWrite(LED[i], LOW);
    }
  }
  softPWMtic++;
}
