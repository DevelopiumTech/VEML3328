
#ifndef VEML3328_H
#define VEML3328_H

// VEML3328 I2C ADDRESS

#define VEML3328_I2C_ADDRESS   0x10

// REGISTER CONF (00H) SETTINGS

#define VEML3328_SD1_ENABLE     0x00
#define VEML3328_SD1_DISABLE    0x8000 

#define VEML3328_DG_1		0x00
#define VEML3328_DG_2		0x1000
#define VEML3328_DG_4		0x2000
#define VEML3328_DG_Res		0x3000

#define VEML3328_Gain_12	0xC00
#define VEML3328_Gain_1		0x00
#define VEML3328_Gain_2		0x400
#define VEML3328_Gain_4		0x800

#define VEML3328_SENSITIVITY_0	0x00
#define VEML3328_SENSITIVITY_1	0x40			

#define VEML3328_IT_50MS       0x00
#define VEML3328_IT_100MS      0x10
#define VEML3328_IT_200MS      0x20
#define VEML3328_IT_400MS      0x30

#define IT_50MS			50
#define IT_100MS		100
#define IT_200MS		200
#define IT_400MS		400


#define high_sens			0
#define low_sens			1

#define VEML3328_TRIG_DISABLE  0x00
#define VEML3328_TRIG_ENABLE   0x04

#define VEML3328_AF_AUTO       0x00
#define VEML3328_AF_FORCE      0x08

#define VEML3328_SD0_ENABLE     0x00
#define VEML3328_SD0_DISABLE    0x01 




// COMMAND CODES

#define COMMAND_CODE_CONF		0x00
#define COMMAND_CODE_RED		0x05
#define COMMAND_CODE_GREEN		0x06
#define COMMAND_CODE_BLUE		0x07
#define COMMAND_CODE_CLEAR		0x04
#define COMMAND_CODE_IR			0x08



class VEML3328 {
	
  private: 
    uint16_t read(uint8_t);
    uint8_t lastConfiguration;
	void setConfiguration(uint16_t);
	
  public:
    VEML3328(void);
    bool begin(void);
	void Enable(void);
	void Disable(void);
    uint16_t getRed(void);
    uint16_t getGreen(void);
    uint16_t getBlue(void);
    uint16_t getClear(void);
	uint16_t getIR(void);
	void setSensitivity(bool);
	void setGain(float);
	void setDG(uint8_t);
	void setIntegrationTime(uint16_t);
	uint16_t getCommandReg(void);

};

#endif
