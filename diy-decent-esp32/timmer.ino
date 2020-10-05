void timmer() {
  long now = millis();
  
  if(digitalRead(BUTTON_B)) { // button pressed
    lastMillis = now;
  }

  pressedTime = now - lastMillis;
}
