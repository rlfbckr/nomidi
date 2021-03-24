
/*

  LED      *    *    *    *    *    *    *    *    *    *

  Pot0     o    o    o    o    o    o    o    o    o    o

  Pot1     o    o    o    o    o    o    o    o    o    o

  Button1  x    x    x    x    x    x    x    x    x    x

  Slider   -    -    -    -    -    -    -    -    -    -
           |    |    |    |    |    |    |    |    |    |
           |    |    |    |    |    |    |    |    |    |
           |    |    |    |    |    |    |    |    |    |
           |    |    |    |    |    |    |    |    |    |
           |    |    |    |    |    |    |    |    |    |
           |    |    |    |    |    |    |    |    |    |
           |    |    |    |    |    |    |    |    |    |
           -    -    -    -    -    -    -    -    -    -
  Button0  x    x    x    x    x    x    x    x    x    x

          [m]  Swi  Pre  Nxt  Sel                      [m]

           0    1    2    3    4    5    6    7    8    9

*/

void setupMode() {
  if (BUTTON_SWI) {
    setup_pos = (setup_pos + 1) % setup_pos_max;
  }
  switch (setup_pos) {
    case 0: sprintf(segmentData, "0 setup      %i ", 0);
      break;
    case 1: sprintf(segmentData, "1 bri %i    ", setup_brighness);
      if (BUTTON_PRE) setup_brighness = constrain(setup_brighness - 5, 1, 100);
      if (BUTTON_NXT) setup_brighness = constrain(setup_brighness + 5, 1, 100);
      sevseg.setBrightness(setup_brighness);
      break;
    case 2: sprintf(segmentData, "2 --- %i    ", setup_brighness);
      break;
    default:
      // nothing
      break;

  }
  //strncpy(segmentData, "-setup-", 10);

  // reset buttons
  BUTTON_SWI = false;
  BUTTON_PRE = false;
  BUTTON_NXT = false;
  BUTTON_SEL = false;
}
