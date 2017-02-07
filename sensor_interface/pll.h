#include<lpc214x.h>

void pll_init(void)
{
	PLL0CFG = 0X24;
	PLL0CON= 0X01;
	PLL0FEED = 0XAA;
	PLL0FEED = 0X55;
	while(!(PLL0STAT & (1<<10)));
	PLL0CON = 0X03;
	PLL0FEED = 0XAA;
	PLL0FEED = 0X55;
}

void vpb(void)
{
	VPBDIV = 0X01;
}


	