#define _VERSION_ 0.05

volatile char segmentData[] = "- NOMIDI -";
const byte segCathodePins[] = {19, 20, 21, 22, 23, 24, 25, 26, 27, 38};
const byte segAnodePins[] = {39, 40, 41, 30, 31, 28, 29, 34};


const int ledPins[] = {0, 1, 35, 11, 12, 13, 32, 33, 36, 37};
volatile int ledIntesity[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile int softPWMtic = 0;
volatile int softPWMres = 100;

const float inputValueSmoothing = 0.2; // the smaller the smoother
const float inputValueGain = 1.003;
const int inputValueLowCut = 5;
const int inputValueHighCut = 4090;
const int inputHysteresisMax = 15;
const int inputHysteresisMin = 1;

const int ADDR_A = 2;
const int ADDR_B = 3;
const int ADDR_C = 4;
const int ADDR_D = 5;

const int POT1_X = A3;
const int POT1_INH = 9;
volatile int POT1_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};
volatile int POT1_VALUES_LAST[] = { -111 , -111, -111, -111, -111, -111, -111, -111, -111, -111};
volatile int POT1_HYS[] = { inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax };
volatile long POT1_HYS_LAST_CHANGE[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const int POT0_X = A2;
const int POT0_INH = 8;
volatile int POT0_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};
volatile int POT0_VALUES_LAST[] = { -111 , -111, -111, -111, 111, 111 , -111, -111, -111, -111};
volatile int POT0_HYS[] = { inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax };
volatile long POT0_HYS_LAST_CHANGE[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const int FADER_X = A0;
const int FADER_INH = 6;
volatile int FADER_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};
volatile int FADER_VALUES_LAST[] = { -111 , -111, -111, -111, -111, -111 , -111, -111, -111, -111};
volatile int FADER_HYS[] = { inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax };
volatile long FADER_HYS_LAST_CHANGE[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const int BUTTON0_X = 15;
const int BUTTON0_INH = 7;
volatile int BUTTON0_VALUES_LAST[] = { -1 , -1, -1, -1, -1, -1 , -1, -1, -1, -1};
volatile int BUTTON0_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};

const int BUTTON1_X = A4;
const int BUTTON1_INH = 10;
volatile int BUTTON1_VALUES_LAST[] = { -1 , -1, -1, -1, -1, -1 , -1, -1, -1, -1};
volatile int BUTTON1_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};
