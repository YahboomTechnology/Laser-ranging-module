#include "LEDdisp.h"
///////////////////////////////////////////
//					4 BIT FND					
///////////////////////////////////////////
void LEDdisp::port(unsigned char _SCL,unsigned char _SDA)
{
	LED_SCL=_SCL;
	LED_SDA=_SDA;
	pinMode(LED_SCL,OUTPUT);
	pinMode(LED_SDA,OUTPUT);
}
void LEDdisp::TM1650_start(void)
{
  digitalWrite(LED_SDA,HIGH);
  digitalWrite(LED_SCL,HIGH);
  digitalWrite(LED_SDA,LOW);
}
void LEDdisp::TM1650_stop(void)
{
  digitalWrite(LED_SDA,LOW);
  digitalWrite(LED_SCL,HIGH);
  digitalWrite(LED_SDA,HIGH);
}
unsigned char LEDdisp::TM1650_ACK(void)
{
  unsigned char _ACK;
  pinMode(LED_SDA,INPUT);
  _ACK=digitalRead(LED_SDA);
  pinMode(LED_SDA,OUTPUT);
  digitalWrite(LED_SCL,HIGH);
  digitalWrite(LED_SCL,LOW);
  return _ACK;
}
void LEDdisp::TM1650_write_byte(unsigned char _DATA)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
    digitalWrite(LED_SCL,LOW);
    digitalWrite(LED_SDA,(_DATA & 0x80)>>7);
    _DATA<<=1;
    digitalWrite(LED_SCL,HIGH);
    digitalWrite(LED_SCL,LOW);
  }
  TM1650_ACK();
}
void LEDdisp::bright(unsigned char _grade)
{
  unsigned char disp_en=0;
  if(_grade)
    disp_en=1;
  if(_grade>7)
    _grade=0;
  TM1650_start();
  TM1650_write_byte(0x48);
  TM1650_write_byte((_grade<<4) + 0x04 + disp_en);
  TM1650_stop();
}
void LEDdisp::TM1638_write_data(unsigned char _ADDR,unsigned char _DATA)
{
  TM1650_start();
  TM1650_write_byte(_ADDR);
  TM1650_write_byte(_DATA);
  TM1650_stop();
}
void LEDdisp::sgl(unsigned _NO,unsigned char _DATA)
{
  if(_DATA<10)
    TM1638_write_data((_NO*2)+102,number[_DATA]);
  /*else if(47<_DATA<=58)
    TM1638_write_data((_NO*2)+102,number[_DATA-48]);
  else if(64<_DATA<71)
    TM1638_write_data((_NO*2)+102,number[_DATA-48]);*/
  else
    TM1638_write_data((_NO*2)+102,number[17]);
}
void LEDdisp::all(unsigned int _DATA)
{
	unsigned int number_temp;
	unsigned char bits=0,number_sgl[4];
	number_temp=_DATA;
	do{
		number_temp/=10;
		bits++;
	}while(number_temp);
	number_sgl[0]=_DATA/1000;
	number_sgl[1]=_DATA%1000/100;
	number_sgl[2]=_DATA%100/10;
	number_sgl[3]=_DATA%10;
	for(unsigned char i=0;i<bits;i++)
	{
		sgl(4-i,number_sgl[4-i-1]);
	}
	for(unsigned char i=0;i<(4-bits);i++)
	{
		sgl(4-i-bits,20);
	}
}
void LEDdisp::outputData(unsigned char _SCL,unsigned char _SDA,unsigned int _DATA)
{
	unsigned int number_temp;
	unsigned char bits=0,number_sgl[4];
	if((LED_SCL!=_SCL) || (LED_SDA!=_SDA))
	{
		LED_SCL=_SCL;
		LED_SDA=_SDA;
		pinMode(LED_SCL,OUTPUT);
		pinMode(LED_SDA,OUTPUT);
	}
	number_temp=_DATA;
	do{
		number_temp/=10;
		bits++;
	}while(number_temp);
	number_sgl[0]=_DATA/1000;
	number_sgl[1]=_DATA%1000/100;
	number_sgl[2]=_DATA%100/10;
	number_sgl[3]=_DATA%10;
	for(unsigned char i=0;i<bits;i++)
	{
		sgl(4-i,number_sgl[4-i-1]);
	}
	for(unsigned char i=0;i<(4-bits);i++)
	{
		sgl(4-i-bits,20);
	}
	
}