#include<lpc214x.h>

void uart_init()
{//BAUD RATE IS SET TO 9600,PINSELECTION SHOULD BE DONE IN MAIN
	U0LCR = 0X83;
	U0DLL = 110;
	U0DLM = 1;
	U0FDR = 0XF1;
	U0LCR = 0X0F;
}
	
void uart_send(int data)
{
	while (!(U0LSR & (1<<5))); // wait till the THR is empty
	// now we can write to the Tx FIFO
	U0THR = data;
}

