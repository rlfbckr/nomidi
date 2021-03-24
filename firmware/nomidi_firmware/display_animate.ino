

void drawAnimation() {
  if (animation) {
    if (millis() - animation_last_frame > animation_speed) {
      strncpy(segmentData, animation_data[animation_frame], 10);
      // animate_frame = (animate_frame + 1) % (sizeof(segmentAnimation) / sizeof(segmentAnimation[0])) ;
      animation_frame = (animation_frame + 1); 
      if (animation_frame >=  (sizeof(animation_data) / sizeof(animation_data[0])) ) {
        animation = false;
      }
      animation_last_frame = millis();
    }
  }
}
