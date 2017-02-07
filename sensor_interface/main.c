#include<lpc214x.h>
#include"pll.h"
#include"adc.h"

int main()
{ int i,j;
	
	pll_init();
	vpb();
	adc_init();
	PINSEL0 = 0;
	PINSEL0 = PINSEL0|(1<<17)|(1<<16);
	IO0DIR = ~(0x00000000 | (1<<7));
	PINSEL1 = 0X00000000;
	IO1DIR = 0XFFFFFFFF; 
	
	
	while(1)
	{
	 int	result_adconv = 0;
	for(i=0;i<200;i++);
		result_adconv = adc_conversion();
		if(result_adconv<300);
		 IO1SET = (1<<20);
		if(result_adconv>=300)
			IO1CLR = (1<<20);
		for( i=0;i<400;i++);
	}
return 0;
	
}	
		
	
	
	
	
	
	
