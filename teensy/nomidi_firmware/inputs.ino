
void readInputs() {
  for (int i = 0; i < 10 ; i++) {
    POT0_VALUES[i] = constrain(inputValueOffset + ((POT0_VALUES[i] * (1 - inputValueSmoothing)) + (mux_pot0.read(9 - i) * inputValueSmoothing) * inputValueGain), 0, 4096);
    if (POT0_VALUES[i] < 0.999) POT0_VALUES[i]  = 0;
    delayMicroseconds(intputReadDelay);

    POT1_VALUES[i] = constrain(inputValueOffset + ((POT1_VALUES[i] * (1 - inputValueSmoothing)) + (mux_pot1.read(9 - i) * inputValueSmoothing) * inputValueGain), 0, 4096);
    if (POT1_VALUES[i] < 0.999) POT1_VALUES[i]  = 0;
    delayMicroseconds(intputReadDelay);

    FADER_VALUES[i] = constrain(inputValueOffset + ((FADER_VALUES[i] * (1 - inputValueSmoothing)) + (mux_fader.read(9 - i) * inputValueSmoothing) * inputValueGain), 0, 4096);
    if (FADER_VALUES[i] < 0.999) FADER_VALUES[i]  = 0;
    delayMicroseconds(intputReadDelay);

    if (mux_button0.read(9 - i) > 10) {
      BUTTON0_VALUES[i] = 1;
    } else {
      BUTTON0_VALUES[i] = 0;
    }
    delayMicroseconds(intputReadDelay);

    if (mux_button1.read(9 - i) > 10) {
      BUTTON1_VALUES[i] = 1;
    } else {
      BUTTON1_VALUES[i] = 0;
    }
    delayMicroseconds(intputReadDelay);

  }
}
