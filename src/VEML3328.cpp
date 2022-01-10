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

*/

#include "Wire.h"
#ifndef __MATH_H
#include <math.h>
#endif
#include "VEML3328.h"


VEML3328::VEML3328(void) {
  
}

bool VEML3328::begin(void) {
  bool sensorExists;
  Wire.begin();
  Wire.beginTransmission(VEML3328_I2C_ADDRESS);
  if (Wire.endTransmission() == 0) {
    sensorExists = true;
  }
  return sensorExists;
}

void VEML3328::setConfiguration(uint16_t configuration) {
  char bytes[2];
  bytes[0]= (configuration >> 0) & 255;
  bytes[1]= (configuration >> 8) & 255;
  Wire.beginTransmission(VEML3328_I2C_ADDRESS);  
  Wire.write(COMMAND_CODE_CONF); 
  Wire.write(bytes,2);
  Wire.write(0);
  Wire.endTransmission(); 
  lastConfiguration = configuration;
}

uint16_t VEML3328::read(uint8_t commandCode) {
  uint16_t data = 0; 
  
  Wire.beginTransmission(VEML3328_I2C_ADDRESS);
  Wire.write(commandCode);
  Wire.endTransmission(false);
  Wire.requestFrom(VEML3328_I2C_ADDRESS,2);
  while(Wire.available()) 
  {
    data = Wire.read(); 
    data |= Wire.read() << 8;
  }
  
  return data; 
}

uint16_t VEML3328::getRed(void) {
  return(read(COMMAND_CODE_RED));
}

uint16_t VEML3328::getGreen(void) {
  return(read(COMMAND_CODE_GREEN));
}

uint16_t VEML3328::getBlue(void) {
  return(read(COMMAND_CODE_BLUE));
}

uint16_t VEML3328::getClear(void) {
  return(read(COMMAND_CODE_CLEAR));
}

uint16_t VEML3328::getIR(void) {
  return(read(COMMAND_CODE_IR));
}

uint16_t VEML3328::getCommandReg(void) {
  return(read(COMMAND_CODE_CONF));
}

void VEML3328::Enable(void) {
  uint16_t CommandReg;
  CommandReg = read(COMMAND_CODE_CONF);						//read the content of the command register to updated it
  CommandReg = CommandReg&(VEML3328_SD0_DISABLE^0xFFFF);			//reset SD0 and SD1 bit to 0
  CommandReg = CommandReg&(VEML3328_SD1_DISABLE^0xFFFF);			//reset SD0 and SD1 bit to 0
 
  setConfiguration(CommandReg);
}

void VEML3328::Disable(void) {
  uint16_t CommandReg;
  CommandReg = read(COMMAND_CODE_CONF);
  CommandReg = CommandReg&(VEML3328_SD0_DISABLE^0xFFFF);			//reset SD0 and SD1 bit to 0
  CommandReg = CommandReg&(VEML3328_SD1_DISABLE^0xFFFF);			//reset SD0 and SD1 bit to 0
  
  CommandReg = CommandReg^VEML3328_SD0_DISABLE;
  CommandReg = CommandReg^VEML3328_SD1_DISABLE;
  
  setConfiguration(CommandReg);
}

void VEML3328::setSensitivity(bool sens) {
  uint16_t CommandReg;
  CommandReg = read(COMMAND_CODE_CONF);
  CommandReg = CommandReg&(VEML3328_SENSITIVITY_1^0xFFFF); 			//reset sensitivity bit to 0
  
  if (sens == 1)
  {
	  CommandReg = CommandReg^VEML3328_SENSITIVITY_1;
  }
  else if (sens == 0)
  {
	  CommandReg = CommandReg^VEML3328_SENSITIVITY_0;
  }
  
  setConfiguration(CommandReg);
}

void VEML3328::setGain(float gain) {
  uint16_t CommandReg;
  CommandReg = read(COMMAND_CODE_CONF);
  CommandReg = CommandReg&(VEML3328_Gain_12^0xFFFF); 			//reset gain to 00
  if (gain == 0.5)
  {
	CommandReg = CommandReg^VEML3328_Gain_12;
  }

  else if (gain == 1)
  {
	CommandReg = CommandReg^VEML3328_Gain_1;
  }  
  
  else if (gain == 2)
  {
	CommandReg = CommandReg^VEML3328_Gain_2;
  }  
  
  else if (gain == 4)
  {
	CommandReg = CommandReg^VEML3328_Gain_4;
  }  
  

  setConfiguration(CommandReg);
}

void VEML3328::setDG(uint8_t gain) {
  uint16_t CommandReg;
  CommandReg = read(COMMAND_CODE_CONF);
  CommandReg = CommandReg&(VEML3328_DG_Res^0xFFFF);			//reset DG to 00
  
  if (gain == 1)
  {
	CommandReg = CommandReg^VEML3328_DG_1;
  }

  else if (gain == 2)
  {
	CommandReg = CommandReg^VEML3328_DG_2;
  }  
  
  else if (gain == 4)
  {
	CommandReg = CommandReg^VEML3328_DG_4;
  }  

  setConfiguration(CommandReg);
}

void VEML3328::setIntegrationTime(uint16_t IT) {
  uint16_t CommandReg;
  CommandReg = read(COMMAND_CODE_CONF);
  CommandReg = CommandReg&(VEML3328_IT_400MS^0xFFFF); 			//reset IT to 00
  if (IT == 50)
  {
	CommandReg = CommandReg^VEML3328_IT_50MS;
  }

  else if (IT == 100)
  {
	CommandReg = CommandReg^VEML3328_IT_100MS;
  }  
  
  else if (IT == 200)
  {
	CommandReg = CommandReg^VEML3328_IT_200MS;
  }  

  else if (IT == 400)
  {
	CommandReg = CommandReg^VEML3328_IT_400MS;
  }  

  setConfiguration(CommandReg);
}
