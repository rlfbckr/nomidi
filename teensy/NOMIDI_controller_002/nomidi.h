int segmentMax = 10;
volatile int lastSegmentPos = 0;

volatile int segmentPos = 0;
volatile int segmentTic = 0;
volatile char segmentData[] = "1bcdefghij";
const int SEG_K[] = {19, 20, 21, 22, 23, 24, 25, 26, 27, 38};
const int SEG[] = {39, 40, 41, 30, 31, 28, 29, 34};


const int LED[] = {0, 1, 35, 11, 12, 13, 32, 33, 36, 37};
volatile int ledIntesity[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile int softPWMtic = 0;
volatile int softPWMres = 100;

const float value_smoothing = 0.01;
const int ADDR_A = 2;
const int ADDR_B = 3;
const int ADDR_C = 4;
const int ADDR_D = 5;

const int POT1_X = A3;
const int POT1_INH = 9;
volatile float POT1_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};

const int POT0_X = A2;
const int POT0_INH = 8;
volatile float POT0_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};

const int FADER_X = A0;
const int FADER_INH = 6;
volatile float FADER_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};

const int SWITCH_X = 15;
const int SWITCH_INH = 7;
volatile int SWITCH_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};


const int SWITCH2_X = A4;
const int SWITCH2_INH = 10;
volatile int SWITCH2_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};
