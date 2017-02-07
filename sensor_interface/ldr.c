#include<lpc214x.h>
#include"adc.h"
#include"pll.h"
#include"uart.h"

int main()
{  int i = 0;
	pll_init();
	vpb();
	PINSEL0 = 0;
	PINSEL0 = (1<<0)|(1<<2)|(1<<16)|(1<<17);
	
	uart_init();
	adc_init();
while(1)
{
	
	int conv_data = adc_conversion();
	uart_send(conv_data);
 
	
}
return  0;
}

	
	