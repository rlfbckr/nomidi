void readInputs() {
  for (int i = 0; i < 10 ; i++) {
    POT1_VALUES[i] = (POT1_VALUES[i] * (1 - value_smoothing)) + (mux_pot1.read(9 - i) * value_smoothing);
    POT0_VALUES[i] = (POT0_VALUES[i] * (1 - value_smoothing)) + (mux_pot0.read(9 - i) * value_smoothing);
    FADER_VALUES_LAST[i] = FADER_VALUES[i];
    FADER_VALUES[i] = (FADER_VALUES[i] * (1 - value_smoothing)) + (mux_fader.read(9 - i) * value_smoothing);
    if (FADER_VALUES_LAST[i] != FADER_VALUES[i]) {
      OSCMessage msg("/nm/fader");
      msg.add((int) i);

      msg.add((float) FADER_VALUES[i]);
      Udp.beginPacket(serverIP, serverPort);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
    }

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
