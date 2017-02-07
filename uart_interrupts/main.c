unsigned char a;
int s;
#include<lpc214x.h>
  void clocks_init(void);
void initUART0(void);
__irq void uart_isr(void);
void timer_int(void);
__irq void  timer_isr(void);


int  main()
{ 
	s = 0;
clocks_init();
initUART0();
timer_int();
PINSEL1 = 0x000000;  //Configure the P1 Pins for GPIO;
IO1DIR = 0xffffffff;
	IO0DIR |=  (1<<3);
	T0TCR = 0x01;//enable timer
while(1){
 ;                
}

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
	   T0MR0 = 500;
	   T0MR1 = 1000;
	T0MR2 = 1500;
	T0MR3 = 2000;
	    T0MCR = (1<<0) |(1<<3)| (1<<6) |(1<<9)|(1<<10);//generate an interrupt and reset when MR0 matches timer counter
	    
	//CONFIGURE INTERRUPT
	
	VICVectAddr4 = (unsigned )timer_isr; //Pointer Interrupt Function (ISR)

	VICVectCntl4 = 0x20 | 4; 
	VICIntEnable = 0x10; //Enable timer0 int
	
  
	T0TCR = 0x02;
	
	
}

void initUART0(void)
{  PINSEL0 = 0X5;
	
  
	
	U0LCR=0x83;
	U0DLM=1;
	U0DLL=134;

	
	
	U0FCR = 0x6; // reset Rx and Tx FIFO
	U0FCR = 0x1; // enable FIFO
	U0LCR = 0x03; // now make DLAB=0 
	
	U0IER = 0x1; // to keep things simple just enable "Receive Data Available(RDA)" interrupt
VICVectAddr1 = (unsigned)uart_isr; //Pointer Interrupt Function (ISR)

VICVectCntl1 = 0x20 | 6; 

VICIntEnable |= (1<<6); //Enable Uart0 interrupt , 6th bit=1

}

__irq void uart_isr()
{
long int regVal1;
	regVal1 = U0IIR; // Reading U0IIR 
	
	//Recieve Data Available Interrupt has occured
	a = U0RBR;
	
	if(a == 'a')//LED ON
	{  if((IO0PIN | (0<<3))==0) 
IO0SET =  (1<<3);
 }
  
 if(a == 'b') //LED OFF
 {
    IO0CLR = (1<<3);
	}
	
	if(a == 'c')
	{  if(s ==0)
		 s=1;
		else
			s=0;

  }

	VICVectAddr = 0x0; // Acknowledge that ISR has finished execution
}
__irq void  timer_isr(void)
{
	long int redval;
	redval = T0IR;
{	if(s==0)
	{
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
	
	
	

	
 }
 
 
 else
 {
   	
	if(T0IR & (1<<0))
  {  
		IO1PIN ^= (1<<20);
}
  else if(T0IR & (1<<1))
	{ IO1PIN ^= (1<<20);
		IO1PIN ^=(1<<21);
	}
	
	else if(T0IR & (1<<2))
	{
		IO1PIN ^= (1<<21);
		IO1PIN ^= (1<<22);
	}
	
	else if( T0IR & (1<<3))
	 {  IO1PIN ^=(1<<22);
	 }
	
 }  
 }
T0IR= redval;
	VICVectAddr = 0x0;
}




