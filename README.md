# NOMIDI
a [OSC](http://opensoundcontrol.org/) based performance controller

 I build this controller out of frustration that [MIDI controllers](https://en.wikipedia.org/wiki/MIDI_controller) are still using only 7 bit resolution. NOMIDI is a OSC based controller with 10 channels each 10bit (12 or 14 bit should be possible as well) resolution for the sliders and knobs. The controller is based on a Teensy 4.1 microcontroller including a high speed ethernet port to broadcast and receive OSC to and from different nodes in the network.

## control elements
* inputs:
  - 10 x 2 knobs (potentiometer ALPS)
  - 10 x 2 pushbuttons
  - 10 x 1 slider (potentiometer 6mm ALPS)
* outputs: 
  - 10 x 1 seven-segemnt element (13,5mm)
  - 10 x 1 white led (3mm)


## componets
[BOM](https://docs.google.com/spreadsheets/d/1EoTag_wGxFKfiME3yydL2qvFMf1TQeLivOXvCBYUS_A/edit#gid=0)

