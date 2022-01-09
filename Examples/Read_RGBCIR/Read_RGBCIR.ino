/*
 MIT License

Copyright (c) 2022 Developium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 * Arduino library for the Vishay VEML3328 and VEML3328sl sensors
 * funtions:
 * bool RGBCIR.begin(void); look for the sensor in the I2C bus, return 0 if sensor not found
 * void RGBCIR.Enable(void); Turn on the sensor'channels (off by default)
 * void Disable(void); Turn off the sensor
 * uint16_t getRed(void); get the red channel's reading from 0-65535
 * uint16_t getGreen(void); get the green channel's reading from 0-65535
 * uint16_t getBlue(void); get the blue channel's reading from 0-65535
 * uint16_t getClear(void); get the clear channel's reading from 0-65535
 * uint16_t getIR(void); get the IR channel's reading from 0-65535
 * void setSensitivity(bool); toggle between two sensitivity modes; 0 for low sensitivity and 1 for high
 * void setGain(float); set the gain of the sensor, choose between 0.5, 1, 2, 4 (1 default)
 * void setDG(uint8_t); set the digital gain of the sensor, choose between 1, 2, 4 (1 default)
 * void setIntegrationTime(uint16_t); set the integration time of the sensor, choose between IT_50MS, IT_100MS, IT_200MS, IT_400MS (in milliseconds)
 * uint16_t getCommandReg(void); Read the value of the command register
 * 
 * refer to the datasheet: https://www.vishay.com/docs/80012/veml3328sl.pdf
 * 
 * By: amb93
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
  Serial.print(RGBCIR.getBlue());   //read blue channel
  Serial.print(','); 
  Serial.print(RGBCIR.getRed());    //read red channel
  Serial.print(',');  
  Serial.print(RGBCIR.getGreen());  //read green channel
  Serial.print(',');  
  Serial.print(RGBCIR.getClear());  //read clear channel
  Serial.print(',');  
  Serial.println(RGBCIR.getIR());   //read IR channel
  delay(100);
}
