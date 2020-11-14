#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>
#include <OSCBundle.h>
#include <Chrono.h>

#include "Type4067Mux.h"
#include "nomidi.h"

boolean DEBUG_OSC_MSG = false;

IntervalTimer readInputsTimer;
IntervalTimer updateDisplayTimer;
IntervalTimer softPWMTimer;
Chrono sendOSC;

Type4067Mux mux_pot1(POT1_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, POT1_INH);
Type4067Mux mux_pot0(POT0_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, POT0_INH);
Type4067Mux mux_fader(FADER_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, FADER_INH);
Type4067Mux mux_button0(BUTTON0_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, BUTTON0_INH);
Type4067Mux mux_button1(BUTTON1_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, BUTTON1_INH);

EthernetUDP Udp;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFC, 0x88};
IPAddress myIP(10, 0, 0, 123); // contoller
IPAddress serverIP(10, 0, 0, 3); // e.g maxmsp
static int serverPort = 9013;
static int incommingPort = 10013;


void setup() {
  Serial.begin(115200);
  Serial.print("NOMIDI v");
  Serial.println(  _VERSION_);
  analogReadResolution(12);
  for (int i = 0; i < 10; i++) {
    pinMode(segCathodePins[i], OUTPUT);
    digitalWrite(segCathodePins[i], 0);
    pinMode(ledPins[i] , OUTPUT);
    digitalWrite(ledPins[i], 0);

  }
  for (int i = 0; i < 8; i++) {
    pinMode(segAnodePins[i], OUTPUT);
    digitalWrite(segAnodePins, 0);
  }
  analogReadAveraging(100);
  initEthernet();
  //readInputsTimer.begin(readInputs, 100);
  updateDisplayTimer.begin(updateSegments, 20);
  softPWMTimer.begin(updateSoftPWM, 80);
}

void loop() {
  readInputs();
  if (sendOSC.hasPassed(20) ) {
    sendOSC.restart();
    sendInputsOSC();
  }

  OSCMessage msgIn;
  int msg_size;
  if ((msg_size = Udp.parsePacket()) > 0) {
    while (msg_size--)
      msgIn.fill(Udp.read());
    if (!msgIn.hasError()) {
      msgIn.route("/nm/set7seg", OSCset7Seg);
      msgIn.route("/nm/set7segall", OSCset7SegAll);
      msgIn.route("/nm/setled", OSCsetLED);
    }
  }
}
