/*
 * The MIT License (MIT)
 * Copyright (c) 2015 amb93
 * Arduino library for the Vishay VEML3328 and VEML3328sl sensors
 * funtions:
 * bool RGBCIR.begin(void); look for the sensor in the I2C bus, return 0 if sensor not found
 * void RGBCIR.Enable(void); Turn on the sensor'channels (off by default)
 * void setConfiguration(uint16_t);
 * void Disable(void); Turn off the sensor
 * uint16_t getRed(void); get the red channel's reading from 0-65535
 * uint16_t getGreen(void); get the green channel's reading from 0-65535
 * uint16_t getBlue(void); get the blue channel's reading from 0-65535
 * uint16_t getClear(void); get the clear channel's reading from 0-65535
 * uint16_t getIR(void); get the IR channel's reading from 0-65535
 * void setSensitivity(bool); toggle between two sensitivity modes; 0 for low sensitivity and 1 for high
 * void setGain(float); set the gain of the sensor, choose between 0.5, 1, 2, 4 (1 default)
 * void setDG(uint8_t); set the digital gain of the sensor, choose between 1, 2, 4 (1 default)
 * void setIntegrationTime(uint16_t); set the integration time of the sensor, choose between 50, 100, 200, 400 (in milliseconds)
 * uint16_t getCommandReg(void); Read the value of the command register
 * 
 * refer to the datasheet: https://www.vishay.com/docs/80012/veml3328sl.pdf
 * 
 * By: Ahmed Albagdady
 */

#include "Wire.h"
#include "VEML3328.h"

VEML3328 RGBCIR;

void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  if(!RGBCIR.begin()) {
    Serial.println("ERROR: couldn't detect the sensor");
    while(1){}
  }
  Serial.println("Vishay VEML3328 RGBCIR color sensor");
  RGBCIR.Enable(); 
  RGBCIR.setGain(0.5);
  RGBCIR.setSensitivity(high_sens);
  RGBCIR.setDG(4);
  RGBCIR.setIntegrationTime(IT_400MS);

  delay(1000);
}

void loop() {
  // Use the arduino's serial plotter
  Serial.print(RGBCIR.getBlue()); 
  Serial.print(','); 
  Serial.print(RGBCIR.getRed()); 
  Serial.print(',');  
  Serial.print(RGBCIR.getGreen()); 
  Serial.print(',');  
  Serial.print(RGBCIR.getClear());
  Serial.print(',');  
  Serial.println(RGBCIR.getIR()); 
  delay(100);
}
