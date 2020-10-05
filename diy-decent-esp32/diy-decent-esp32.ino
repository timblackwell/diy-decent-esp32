#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "BluetoothSerial.h"

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

// OLED FeatherWing buttons map to different pins depending on board:
#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14


long lastMillis = 0;
long pressedTime = 0;
bool wasPressing;

int pressurePin = A2;
int pressureVoltage = 0;
float pressureBars = 0.0;

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);

  if(!SerialBT.begin("ESPresso")){
    Serial.println("An error occurred initializing Bluetooth");
  }
  Serial.println("The device started, now you can pair it with bluetooth!");

  delay(100);

  setupAnalogRead();
  setupDisplay();

}

void loop() {
  pressureVoltage = (pressureVoltage + analogRead_cal(34, ADC_ATTEN_DB_11, 22)) /2;
  pressureBars = barsFromMilliVolts(pressureVoltage);
  timmer();
  refreshDisplay();

  SerialBT.print("Pressure: ");
  SerialBT.println(pressureBars);

  delay(100);
  yield();
}
