void setupDisplay() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();

  Serial.println("IO test");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
}

void refreshDisplay() {
    pressedTime = millis() - lastMillis;

    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Time: ");
    display.print(pressedTime);
    display.println("s");
    display.print("Bars: ");
    display.print(pressureBars);
    display.print("    ");
    display.print(pressureVoltage);
    display.println("mV");
    
    // 120 pixels for 12 bar. 10 pixels for 1 bar. 0.1 bar = 1 pixel
    int pixels = (pressureBars*10);
    display.fillRect(4, 20, pixels, 8, WHITE);
    display.drawFastVLine(4, 16, 16, WHITE);  // 0
    display.drawFastVLine(24, 16, 16, WHITE);  // 2
    display.drawFastVLine(44, 16, 16, WHITE); // 4
    display.drawFastVLine(64, 16, 16, WHITE); // 6
    display.drawFastVLine(84, 16, 16, WHITE); // 8
    display.drawFastVLine(104, 16, 16, WHITE); // 10
    display.drawFastVLine(124, 16, 16, WHITE); // 12
    display.display();
}


void printTime() {
    pressedTime = millis() - lastMillis;

    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Time: ");
    display.print(pressedTime);
    display.fillRect(0, 20, pressedTime/10, 8, WHITE);
    display.drawFastVLine(0, 16, 16, WHITE);
    display.drawFastVLine(32, 16, 16, WHITE);
    display.drawFastVLine(64, 16, 16, WHITE);
    display.drawFastVLine(96, 16, 16, WHITE);
    display.drawFastVLine(127, 16, 16, WHITE);
    display.display();
}
