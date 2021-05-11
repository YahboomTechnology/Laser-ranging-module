#ifndef LEDdisp_h
#define LEDdisp_h
#include <Arduino.h>
class LEDdisp
{
	private:
		unsigned char LED_SDA;
		unsigned char LED_SCL;
		void TM1650_start(void);
		void TM1650_stop(void);
		unsigned char TM1650_ACK(void);
		void TM1650_write_byte(unsigned char _DATA);
		void TM1638_write_data(unsigned char _ADDR,unsigned char _DATA);
		unsigned char number[18]={	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,
									0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0xff,0x00};
	public:
		void port(unsigned char _SCL,unsigned char _SDA);
		void bright(unsigned char _grade);
		void sgl(unsigned _NO,unsigned char _DATA);
		void all(unsigned int _DATA);
		void outputData(unsigned char _SCL,unsigned char _SDA,unsigned int _DATA);
};
#endif