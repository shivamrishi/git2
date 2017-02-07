#include<lpc21xx.h>

int arr[10] = {0x0000003f,0x00000006,0x0000005b,0x0000004f,0x00000066,0x0000006d,0x0000007d,0x00000007,0x0000007f,0x0000006f};
int arr1[10]= {0x00003f00,0x00000600,0x00005b00,0x00004f00,0x00006600,0x00006d00,0x00007d00,0x00000700,0x00007f00,0x00006f00};

int main()
{ int i,j,q,w;
	PINSEL0 = 0;
	IO0DIR=IO1DIR=  0xffffffff;
	
	while(1)
	{ 
	for(i=0;i<10;i++)	
{   IO0SET = IO0SET |arr[i];
		for(q=0;q<2000;q++);
      for(j=0;j<10;j++)
       { IO0SET = arr1[j];	
	       for(q=0;q<200000;q++);
         IO0CLR = arr1[j];   
	       for(w=0;w<200;w++);
     
       }
	
		IO0CLR =   IO0CLR | arr[i];	 
	for(w=0;w<200000;w++);
}
	}
	 
	return 0;
 }
