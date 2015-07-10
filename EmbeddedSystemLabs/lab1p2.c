#include <avr/io.h>

//These are macros used to set, clear, or get a single bit from an 8-bit port
//for example SET_BIT(PORTA,3); sets PORTA = 0x08.
#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))

int main(void){

	DDRA = 0xFF; //set all pins of port A to output
	DDRC = 0x00; //set all pins of port C to input

	while(1)
	{
		int one = 1;
		int count = 0;
		int i = 0;
		while(i < 8)
		{
			int temp = GET_BIT(PINC,i);
			if(temp != 0)
			{
				count++;
			}
			++i;
		}
		if ((count % 2) != 0)
		{
			CLR_BIT(PORTA, 1);
			one = SET_BIT(PORTA, 0);
		}
		else 
		{
				CLR_BIT(PORTA, 0);
			one = SET_BIT(PORTA, 1);
		}
		count = 0;
	}

return 0;
	
}
