# NOMIDI
**A [OSC](http://opensoundcontrol.org/) based performance controller**

![NOMIDI Assembled](https://github.com/rlfbckr/nomidi/blob/1136a831244162e96c44ef483a0d44b69978a3aa/assets/images/nomidi_assembled.jpg)

I build this controller out of frustration that [MIDI controllers](https://en.wikipedia.org/wiki/MIDI_controller) are still using only 7 bit resolution. **NOMIDI** is a OSC based controller with 10 channels each 10bit (12 or 14 bit should be possible as well) resolution for the sliders and knobs. The controller is based on a Teensy 4.1 microcontroller including a high speed ethernet port to broadcast and receive OSC to and from different nodes in the network.
 
**PLEAYSE NOTE:** NOMIDI is OSC based in cannot be used in an "MIDI Environment". I can send/reicive only signals form OSC enabled Software and Hardware. e.g. MaxMSP, Supercollider, PureData, Processing, OpenFrameworks, monome norns, Abelton Live and many more.
 

## Control elements
* inputs:
  - 10 x 2 knobs (potentiometer ALPS)
  - 10 x 2 pushbuttons
  - 10 x 1 slider (potentiometer 6mm ALPS)
* outputs: 
  - 10 x 1 seven-segment element (13,5mm)
  - 10 x 1 white led (3mm)

## Interface / Connection
- USB SlipSerial
**or**
- Ethernet

## PCB (Printed circuit board)
![NOMIDI PCB](https://github.com/rlfbckr/nomidi/blob/1136a831244162e96c44ef483a0d44b69978a3aa/assets/images/nomidi_pcb.jpg)

## Software
*For flashing the firmware on the Teensy board these software compnents are needed:*

- Arduino IDE (Version 1.8.13) [(download)](https://www.arduino.cc/en/software)
- Teensyduino (Version 1.53) [(download)](https://www.pjrc.com/teensy/td_download.html)

## Needed Arduino libraries
- OSCBundle  *[install via package manager]*
- Chrono  *[install via package manager]*
- MUX74HC4067 *[install via package manager]*
- SevSeg ( Seven Segment Multiplexing Library ) *[modefied version included in firmware sketch]*
- NativeEthernet ( Teensy 4.1 ) *[comes with teensyduino]*

## Bill of Materials
[BOM](https://docs.google.com/spreadsheets/d/1EoTag_wGxFKfiME3yydL2qvFMf1TQeLivOXvCBYUS_A/edit#gid=0)

## Firmware configuration

NOMIDI can communicate ether via *Ethernet* oder *Serial* (OSC over SLIPSerial). edit **firmware/nomidi_firmware/config.h**  

### Use Serial ( OSC over SLIP Serial) for communication:
```
#define USE_SLIP_SERIAL
```

### Use Ethernet ( OSC over UDP) for communication:
```
#define USE_ETHERNET

static byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFC, 0x88}; // hardware addres of your device
static IPAddress myIP(10, 0, 0, 123); // ip address of the controller
static IPAddress serverIP(10, 0, 0, 3); // ip addres of your laptop
static int serverPort = 9013;
static int incommingPort = 10013;

```
