#include<lpc214x.h>


void clocks_init(void);
void timer_int(void);
 __irq void timer_isr(void);



int  main()
{
  clocks_init();
  timer_int();
	
  PINSEL1 = 0x000000;  //Configure the P1 Pins for GPIO;
    IO1DIR = 0xffffffff;
	
	//Configure the P1 pins as OUTPUT;
	T0TCR = 0x01;//enable timer
	
while(1);
}

void clocks_init(void)
{
   PLL0CFG= 0X24;
   PLL0CON= 0X01;
   PLL0FEED = 0XAA;
   PLL0FEED = 0X55;
   while((PLL0STAT& (1<<10) == 0));
   PLL0CON = 0X03;
   PLL0FEED = 0XAA;
	PLL0FEED = 0X55;
	VPBDIV = 0X01;
	
}

void timer_int(void)

{
//CONFIGURE TIMER
			T0CTCR = 0X0;
	    T0PR = 59999;//1ms delay
	   T0MR0 = 1000;
	   T0MR1 = 2000;
	T0MR2 = 3000;
	T0MR3 = 4000;
	    T0MCR = (1<<0) |(1<<3)| (1<<6) |(1<<9)|(1<<10);//generate an interrupt and reset when MR0 matches timer counter
	    
	//CONFIGURE INTERRUPT
	
	VICVectAddr4 = (unsigned )timer_isr; //Pointer Interrupt Function (ISR)

	VICVectCntl4 = 0x20 | 4; 
	VICIntEnable = 0x10; //Enable timer0 int
	
  
	T0TCR = 0x02;
	
	
}


__irq void  timer_isr(void)
{
	
	long int redval;
	redval = T0IR;
	if(T0IR & (1<<0))
  {  
		IO1PIN ^= (1<<21);
}
  else if(T0IR & (1<<1))
	{ IO1PIN ^= (1<<21);
		IO1PIN ^=(1<<22);
	}
	
	else if(T0IR & (1<<2))
	{
		IO1PIN ^= (1<<22);
		IO1PIN ^= (1<<23);
	}
	
	else if( T0IR & (1<<3))
	 {  IO1PIN ^=(1<<23);
	 }
	
	
	

	T0IR= redval;
	VICVectAddr = 0x0;
}
