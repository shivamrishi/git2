#include <lpc214x.h>
#include <vector>

void initClocks(void);
void initUART0(void);
unsigned char uart_recieve(void);
unsigned char dats;

int main(void)
{int i=0;
	unsigned char arr[] = "welcome shivam";
	initClocks(); // Set CCLK=60Mhz and PCLK=60Mhz 
	initUART0();
	
	PINSEL1 = 0x000000;  //Configure the P1 Pins for GPIO;
  IO1DIR = 0xffffffff;
	IO1SET = (1<<21);
	for(i=0;i<50000;i++);
	IO1CLR = (1<<21);
 
	while(1)	
	{		 
		  if((U0LSR&0x01) == 1)
     	{   dats = U0RBR;
	 
		  if(dats == 'b')//LED On
			{ if((IO1PIN | (0<<21)) ==0)
        {IO1SET = (1<<21);}
      }
		 
			if(dats =='1') //led off
			{  
         IO1CLR = (1<<21);
      }
     for(i=0;i<5000;i++);
		  }
  }
}
void initUART0(void)
{   PINSEL0 = 0;
	 PINSEL0 = PINSEL0|(1<<0)|(1<<2);
	U0LCR=0x83;
	U0DLM=1;
	U0DLL=134;
	U0LCR=0x03;
}

void initClocks(void)
{
	PLL0CON = 0x01;   //Enable PLL
	PLL0CFG = 0x24;   //Multiplier and divider setup	
	PLL0FEED = 0xAA;  //Feed sequence
	PLL0FEED = 0x55;
	
	while(!(PLL0STAT & 0x00000400)); //is locked?
		
	PLL0CON = 0x03;   //Connect PLL after PLL is locked
	PLL0FEED = 0xAA;  //Feed sequence
	PLL0FEED = 0x55;
	VPBDIV = 0x01;    // PCLK is same as CCLK i.e.60 MHz
}



 
 