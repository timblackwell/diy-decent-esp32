float barsFromMilliVolts(int milliVolts) {
  if (milliVolts < 340) {
    return 0;
  }
  
  return (float)(milliVolts-340)/199.4371;
}
