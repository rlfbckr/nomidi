
void readInputs() {
  for (int i = 0; i < 10 ; i++) {
    // int i = readinputtick % 10;
    // POT 0
    int tmp_pot0 = map(constrain((mux_pot0.read(9 - i) * inputValueGain), inputValueLowCut , inputValueHighCut), inputValueLowCut , inputValueHighCut, 0 , 4095);
    if (abs(tmp_pot0 - POT0_VALUES[i]) >= POT0_HYS[i]) {
      POT0_VALUES[i] = tmp_pot0;
      if (POT0_HYS[i] > inputHysteresisMin) {
        POT0_HYS[i]--;
        POT0_HYS_LAST_CHANGE[i] = millis();
      }
    }
    if ((millis() - POT0_HYS_LAST_CHANGE[i]) > 100) {
      if (POT0_HYS[i] < inputHysteresisMax) {
        POT0_HYS[i]++;
      }
    }
  }

  delayMicroseconds(20);
  for (int i = 0; i < 10 ; i++) {
    // POT 1
    int tmp_pot1 = map(constrain((mux_pot1.read(9 - i) * inputValueGain), inputValueLowCut , inputValueHighCut), inputValueLowCut , inputValueHighCut, 0 , 4095);
    if (abs(tmp_pot1 - POT0_VALUES[i]) >= POT1_HYS[i]) {
      POT1_VALUES[i] = tmp_pot1;
      if (POT0_HYS[i] > inputHysteresisMin) {
        POT1_HYS[i]--;
        POT1_HYS_LAST_CHANGE[i] = millis();
      }
    }
    if ((millis() - POT1_HYS_LAST_CHANGE[i]) > 100) {
      if (POT1_HYS[i] < inputHysteresisMax) {
        POT1_HYS[i]++;
      }
    }
  }
  delayMicroseconds(20);
  for (int i = 0; i <10 ; i++) {
    // FADER
    int tmp_fader = map(constrain((mux_fader.read(9 - i) * inputValueGain), inputValueLowCut , inputValueHighCut), inputValueLowCut , inputValueHighCut, 0 , 4095);
   


    if (abs(tmp_fader - FADER_VALUES[i]) >= FADER_HYS[i]) {
      FADER_VALUES[i] = tmp_fader;
      if (FADER_HYS[i] > inputHysteresisMin) {
        FADER_HYS[i]--;
        FADER_HYS_LAST_CHANGE[i] = millis();
      }
    }
    if ((millis() - FADER_HYS_LAST_CHANGE[i]) > 100) {
      if (FADER_HYS[i] < inputHysteresisMax) {
        FADER_HYS[i]++;
      }
    }
    
  }
   // Serial.println();
  delayMicroseconds(10);
  for (int i = 0; i < 10 ; i++) {
    if (mux_button0.read(9 - i) > 10) {
      BUTTON0_VALUES[i] = 1;
    } else {
      BUTTON0_VALUES[i] = 0;
    }
    /*
      if (i == 0) {
      Serial.print(i);
      Serial.print(" ");
      Serial.print(mux_button0.read(9 - i));
      Serial.print(" ");
      Serial.println(mux_button1.read(9 - i));
      }
    */
    if (mux_button1.read(9 - i) > 10) {
      BUTTON1_VALUES[i] = 1;
    } else {
      BUTTON1_VALUES[i] = 0;
    }
  }

  delayMicroseconds(10);


  //readinputtick++;
}
