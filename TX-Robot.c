#include<pic.h>
#include"pic_lcd8.h"
__CONFIG(HS & WDTDIS & PWRTDIS & BORDIS & LVPDIS & WRTEN & DEBUGDIS & DUNPROT & UNPROTECT);
unsigned int a,b,c,d0,d1,d2,d3,d4,d5;
unsigned char ser;
unsigned int del,j,i,m,n;
unsigned char z;
#define sw RD7
//unsigned char a;
bit x;
void forward();
void uart_init();
void forward();

void left();
void right();
void stop();


void send(unsigned char const *);

void enter();
void TX(unsigned char );
void delay(unsigned int z)
{
while(z--);
}
void interrupt rcx(void)   
{
	if(RCIF==1)
	{
		x=1;
		ser=RCREG;
		RCIF=0;   

	}
}
void main()
{
m=0;
n=0;
	TRISA=0xFF;

	TRISD=0xF0;
    TRISB=0x40;


	//TRISE=0x00;
	TRISC=0x8F;
	ADCON1=0x82;
TRISC2=1;
TRISC3=1;
TRISB6=1;
RB6=1;
	//Lcd8_Init();
	ADCON0=0xC5;
uart_init();// Uart init
     	
 TXEN=1;
CREN=1;
	
	while(1)
	{
		ADGO=1;
		while(ADGO==1);
		a=ADRESL;
		b=ADRESH;
		b=b*256;
		c=b+a;
		

if((RC2==1)&&(RC3==1))
{
forward();
}
else if((RC2==0)&&(RC3==1))
{
right();
delay(65000);
forward();
delay(5000);


}
else if((RC2==1)&&(RC3==0))
{
left();
delay(65000);
forward();
delay(5000);

}
 
else
{
stop();
}


if(c>300)
{
m=m+1;
TX('B');
//send("stop");
RB0=0;
RB1=0;
RB2=0;
RB3=0;
RB4=0;
RB5=0;
stop();

}
while(m==1);
if(sw==0)
{
n=n+1;
TX('A');
//send("start");

stop();
//RB6=1;
}
while(n==1);
 }
}   
		
void forward()
{
RB0=1;
RB1=1;
RB2=1;
RB3=0;
RB4=1;
RB5=0;

}

void right()
{
RB0=1;
RB1=1;
RB2=1;
RB3=0;
RB4=0;
RB5=0;
}
void left()
{
RB0=1;
RB1=1;
RB2=0;
RB3=0;
RB4=1;
RB5=0;
}
void stop()
{
RB0=0;
RB1=0;
RB2=0;
RB3=0;
RB4=0;
RB5=0;

}
void uart_init()
{
RCSTA=0X90;
TXSTA=0X26;
BRGH=1;
SPBRG=129;
}
void send(unsigned char const *hh)
{
while(*hh){
		TX(*hh);		
		hh++;	}
}


/* Press enter command */	
void enter()
{
   TX(0x0d);//hex value for Carrage return--------------Refer ASCII table
   TX(0x0a);//hex value for new line or Enter--------------Refer ASCII table
	call_delay();
	call_delay();
}
void TX(unsigned char z)
{
	TXREG=z;// Transmit buffer 8bit register
	while(TRMT!=1);// Tramsmit empty bit in TXSTA--used for checking whether TXREG is full or empty, if TRMT=1(empty) means TXIF will set as one
	TXIF=0;// Tx interrupt flag clear 
}				