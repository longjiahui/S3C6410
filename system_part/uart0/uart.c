#include "S3C6410.h"

static void delay(unsigned long long tmp){while(tmp--);}

//judge if the data in Rx
unsigned char uart0_ifDataInRx()
{
	if(UFSTAT0&(0x7F)==0)return 0;
	else return 1;
}

//初始化函数
void init_uart0()//115200bps 8N1 FIFO-Mode
{
	GPACON &=~0xFF;
	GPACON |= 0x22;

	ULCON0=0x03;
	UCON0=0x05;
	UFCON0=0x01;//0000 0001 enable fifo-mode 0B for tx 1Bfor rx
	UMCON0=0;
	UDIVSLOT0=1;
	UBRDIV0=35;
}

unsigned char uart0_getChar()
{
	while((UFSTAT0&(0x7F))==0);
	return URXH0;	
	delay(0x100);
}

void uart0_putChar(unsigned char c)
{
	while(UTRSTAT0&(1<<1)==0);//full
	UTXH0=c;
	delay(0x100);
}

void uart0_putString(unsigned char* s)
{
	unsigned long counter=0;
	char tmp;
	while( (tmp=s[counter]) !='\0')
	{
		uart0_putChar(tmp);
		counter+=1;
	}
}
