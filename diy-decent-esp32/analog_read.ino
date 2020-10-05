/*
   ESP32 ADC multi readings

   All time ADC pins:
   ADC1_CH0,ADC1_CH03,ADC1_CH04
   ADC1_CH05,ADC1_CH06,ADC1_CH07

   Use only without WiFi:
   ADC2_CH0,ADC2_CH01,ADC2_CH02,ADC2_CH03
   ADC2_CH04,ADC2_CH05,ADC2_CH06
   ADC2_CH07,ADC2_CH08,ADC2_CH09

   Arduino espressif doc: https://goo.gl/NpUo3Z
   Espressif doc: https://goo.gl/hcUy5U
   GPIO: https://goo.gl/k8FGGD
*/

#include <esp_adc_cal.h>

// Command to see the REF_VOLTAGE: espefuse.py --port /dev/ttyUSB0 adc_info
// or dc2_vref_to_gpio(25)
#define REF_VOLTAGE 1128

byte pins[6] = {36, 39, 34, 35, 32, 33};

esp_adc_cal_characteristics_t *adc_chars = new esp_adc_cal_characteristics_t;


// ========= analogRead_cal =========
int analogRead_cal(uint8_t channel, adc_atten_t attenuation, uint8_t cycles) {
  adc1_channel_t channelNum;

  /*
     Set number of cycles per sample
     Default is 8 and seems to do well
     Range is 1 - 255
   * */
   analogSetCycles( cycles);

  /*
     Set number of samples in the range.
     Default is 1
     Range is 1 - 255
     This setting splits the range into
     "samples" pieces, which could look
     like the sensitivity has been multiplied
     that many times
   * */
  //analogSetSamples(uint8_t samples);

  switch (channel) {
    case (36):
      channelNum = ADC1_CHANNEL_0;
      break;

    case (39):
      channelNum = ADC1_CHANNEL_3;
      break;

    case (34):
      channelNum = ADC1_CHANNEL_6;
      break;

    case (35):
      channelNum = ADC1_CHANNEL_7;
      break;

    case (32):
      channelNum = ADC1_CHANNEL_4;
      break;

    case (33):
      channelNum = ADC1_CHANNEL_5;
      break;
  }

  adc1_config_channel_atten(channelNum, attenuation);
  return esp_adc_cal_raw_to_voltage(analogRead(channel), adc_chars);
}


// ========= SETUP =========
void setupAnalogRead() {
  // -- Fixed for the all adc1 ---
  // 4095 for 12-bits -> VDD_A / 4095 = 805uV  too jittery
  // 2048 for 11-bits -> 3.9 / 2048 = 1.9mV looks fine
  /*
     Set the resolution of analogRead return values. Default is 12 bits (range from 0 to 4096).
     If between 9 and 12, it will equal the set hardware resolution, else value will be shifted.
     Range is 1 - 16
  */
  analogReadResolution(11); // https://goo.gl/qwUx2d

  // Calibration function
  esp_adc_cal_value_t val_type =
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_11, REF_VOLTAGE, adc_chars);
}
