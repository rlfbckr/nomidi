
void readInputs() {
  for (int i = 0; i < 10 ; i++) {
    POT0_VALUES[i] =  (POT0_VALUES[i] * 0.8) + (mux_pot0.read(9 - i) * 0.2);
    if (POT0_VALUES[i] < 0.99) {
      POT0_VALUES[i] = 0;
    }
    
    POT1_VALUES[i] =  (POT1_VALUES[i] * 0.8) + (mux_pot1.read(9 - i) * 0.2);
    if (POT1_VALUES[i] < 0.99) {
      POT1_VALUES[i] = 0;
    }

    FADER_VALUES[i] =  (FADER_VALUES[i] * 0.8) + (mux_fader.read(9 - i) * 0.2);
    if (FADER_VALUES[i] < 0.99) {
      FADER_VALUES[i] = 0;
    }

    if (mux_button0.read(9 - i) > 10) {
      BUTTON0_VALUES[i] = 1;
    } else {
      BUTTON0_VALUES[i] = 0;
    }
    if (mux_button1.read(9 - i) > 10) {
      BUTTON1_VALUES[i] = 1;
    } else {
      BUTTON1_VALUES[i] = 0;
    }
  }
}
