/*****************************
 * Load Cell Test
 * Use with the HX711 Arduino Library by Bogdan Necula
 * 
 * 2022-11-07
 *****************************/

#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 6;
const int LOADCELL_SCK_PIN = 7;

const long calibZero = -88180; // Calibration factor

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    long reading = scale.read() - calibZero;
    reading = -reading/1000;

    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }

  delay(1000);
  
}