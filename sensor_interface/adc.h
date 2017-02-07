#include<lpc214x.h>
	int result;
void adc_init(void)
{
AD1CR = 0X00200E02;//initialise adc
	
}

int adc_conversion(void)
{
	AD1CR = AD1CR|(1<<24);//START CONVERSION NOW
	while((AD1STAT&(1<<1))==0);//check conversion status

	result = (AD1DR1>>6)&(0x3ff);//fetch result;
return result;
}	
	
	
	