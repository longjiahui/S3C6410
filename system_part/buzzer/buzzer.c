#include "S3C6410.h"

void init_buzzer()
{
	GPFCON &=(~(3<<28));
	GPFCON |=(~(2<<28));
	GPFDAT &=(~(1<<14));
}

void buzzerOn()
{
	GPFDAT |=(1<<14);
}

void buzzerOff()
{
	GPFDAT &=(~(1<<14));
}
