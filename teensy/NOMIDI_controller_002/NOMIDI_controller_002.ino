#include "Type4067Mux.h"
#include "nomidi.h"
IntervalTimer readInputsTimer;
IntervalTimer updateDisplayTimer;
IntervalTimer softPWMTimer;

int t  = 0;
Type4067Mux mux_pot1(POT1_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, POT1_INH);
Type4067Mux mux_pot0(POT0_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, POT0_INH);
Type4067Mux mux_fader(FADER_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, FADER_INH);
Type4067Mux mux_switch(SWITCH_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, SWITCH_INH);
Type4067Mux mux_switch2(SWITCH2_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, SWITCH2_INH);

void setup() {
  Serial.begin(115200);
  Serial.println("hi");
  analogReadResolution(12);
  for (int i = 0; i < 10; i++) {
    pinMode(SEG_K[i], OUTPUT);
    digitalWrite(SEG_K[i], 0);
    pinMode(LED[i] , OUTPUT);
    digitalWrite(LED[i], 1);

  }
  for (int i = 0; i < 8; i++) {
    pinMode(SEG[i], OUTPUT);
    digitalWrite(SEG[i], 0);
  }

  // readInputsTimer.begin(readInputs, 1000);
  updateDisplayTimer.begin(updateSegments, 60);
  softPWMTimer.begin(updateSoftPWM, 60);
}
void readInputs() {
  for (int i = 0; i < 10 ; i++) {
    POT1_VALUES[i] = (POT1_VALUES[i] * (1 - value_smoothing)) + (mux_pot1.read(9 - i) * value_smoothing);
    POT0_VALUES[i] = (POT0_VALUES[i] * (1 - value_smoothing)) + (mux_pot0.read(9 - i) * value_smoothing);
    FADER_VALUES[i] = (FADER_VALUES[i] * (1 - value_smoothing)) + (mux_fader.read(9 - i) * value_smoothing);
    ledIntesity[i] = map(FADER_VALUES[i], 0, 4095, 0, softPWMres);

    if (mux_switch.read(9 - i) > 10) {
      SWITCH_VALUES[i] = 1;
    } else {
      SWITCH_VALUES[i] = 0;
    }
    if (mux_switch2.read(9 - i) > 10) {
      SWITCH2_VALUES[i] = 1;
    } else {
      SWITCH2_VALUES[i] = 0;
    }
  }
}

void loop() {
  readInputs();
  if (t % 1000 == 0) {
    Serial.print("POT1 ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( POT1_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();

    Serial.print("POT0 ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( POT0_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("FADER ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( FADER_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("SWITCH ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( SWITCH_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("SWITCH2 ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( SWITCH2_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();
  }
  t++;
  // delay(1);
}
