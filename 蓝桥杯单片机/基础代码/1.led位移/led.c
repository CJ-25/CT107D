#include"STC15F2K60S2.h"
#include"intrins.h"

void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main()
{
   	 unsigned char i;
	  P2=((P2&0x1f)|0xa0);
		  P0=0x00;
		  P2&=0X1f;

	  while(1)
	  for(i=0;i<8;i++)
	  {
		  P2=((P2&0x1f)|0x80);
		  P0=0xfe>>i;
		  P2&=0X1f;
		  Delay100ms();
	  }
}
