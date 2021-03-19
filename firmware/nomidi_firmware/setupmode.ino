
int setup_pos = 1;
int setup_pos_max = 8;
int setup_brighness = 90;
void setupMode() {
  if (setup_pos == 0) {
    strncpy(segmentData, "-setup-", 10);

  } else if (setup_pos == 1) {
    sprintf(segmentData, "bri %i", setup_brighness);

  }
}
