#include <avr/io.h>

//These are macros used to set, clear, or get a single bit from an 8-bit port
//for example SET_BIT(PORTA,3); sets PORTA = 0x08.
#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))

int main(void)
{

	DDRA = 0xFF; //set all pins of port A to output
	DDRC = 0x00; //set all pins of port C to input

	while(1)
	{

		CLR_BIT(PORTA,0);
		CLR_BIT(PORTA,1);
		CLR_BIT(PORTA,2);
		int DSO = GET_BIT(PINC,0);
		int PSO = GET_BIT(PINC,1);
		int DW = GET_BIT(PINC,2);
		int PW = GET_BIT(PINC,3);
		int BRW = GET_BIT(PINC,4);
		int BLW = GET_BIT(PINC,5);
		int KEY = GET_BIT(PINC,6);
		int LOCK = GET_BIT(PINC,7);

		if(((KEY && DW && !DSO) || (KEY && PW && !PSO)))
		{
			SET_BIT(PORTA,0);
		}
		if((PW && PSO))
		{
			SET_BIT(PORTA,1);
		}
		if((LOCK && (DW || PW || BRW || BLW)))
		{
			SET_BIT(PORTA,2);
		}

		
		
	}

return 0;
}
