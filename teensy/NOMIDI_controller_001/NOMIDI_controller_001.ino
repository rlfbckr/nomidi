#include "Type4067Mux.h"
#include "nomidi.h"

IntervalTimer updateDisplayTimer;
IntervalTimer softPWMTimer;

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

  updateDisplayTimer.begin(updateSegments, 50);
  softPWMTimer.begin(updateSoftPWM, 10);
}

void loop() {


  Serial.print("POT1 ");
  for (int i = 9; i >= 0 ; i--) {
    Serial.print( mux_pot1.read(i) );
    Serial.print(" ");
  }
  Serial.println();

  Serial.print("POT0 ");
  for (int i = 9; i >= 0 ; i--) {
    Serial.print( mux_pot0.read(i) );
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("FADER ");
  for (int i = 9; i >= 0 ; i--) {
    Serial.print( mux_fader.read(i) );
    ledIntesity[9-i] = map(mux_fader.read(i),0,4095,0,softPWMres);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("SWITCH ");
  for (int i = 9; i >= 0 ; i--) {
    Serial.print( mux_switch.read(i) );
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("SWITCH2 ");
  for (int i = 9; i >= 0 ; i--) {
    Serial.print( mux_switch2.read(i) );
    Serial.print(" ");
  }
  Serial.println();
  delay(1);
}
