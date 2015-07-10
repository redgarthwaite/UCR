#include <avr/io.h>
#include <avr/interrupt.h>

//#define SET_BIT(p,i) ((p) |= (1 << (i)))
//#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
//#define GET_BIT(p,i) ((p) & (1 << (i)))

const unsigned int ONE_MS = 4;

const unsigned int RT_Period = 1000;
unsigned int RT_Clk = 0;
unsigned int RT_Counter = 0;


enum RT_States { INIT, S0, S1 } RT_State;

//Interrupt service routine
//We enter this function ~4 times per millisecond,
//we can set a flag that signals a period has passed every period*4 times the function is entered.
//If our period is 1000 ms, then we would enter the function 1000*4 = 4000 times before transitioning to next state.

ISR(TIMER0_OVF_vect) 
{ //Timer0 overflow interrupt service routine
   //Put code in me!
   //Count up to period and set flag
   RT_Counter++;

	if(RT_Counter >= (RT_Period * ONE_MS))
	{
		RT_Counter = 0;
		RT_Clk = 1;
		PORTA++;

	}
   
}

void RT_ClkTick() 
{
   //Put code in me!
   //wait until ISR sets flag
   while(!RT_Clk)
    { }
   	RT_Clk = 0;
}

void RT_Tick()
 {
  switch(RT_State) 
  { //actions
      case INIT:
	  		PORTA = 0;
	  	break;
	  case S0:
	  		PORTA = 1;
	  	break;
	  case S1:
	  		PORTA = 0;
	  	break;    
   }
   switch(RT_State)
    { //transitions
      case INIT:
	  	 RT_State =  S0;
		break;
      case S0:
	  		if(1){
			 RT_State =  S1;
			}
	  	break;
	  case S1:
	  		if(1){
			RT_State =  S0;
			}
	  	break;
   }
 
}

//Configure ATMega32 Timer0 control registers.  Correct values can be found in ATMega32 datasheet.
void InitTimer() 
{
   // Set prescaler to 8.  Since the ATMega32 runs at 8Mhz, our timer clock will run at 8MHz/8 = 1MHz.
   TCCR0 |= 0x02;

   //Enable Overflow Interrupt Enable on Timer0.  
   TIMSK |= 0x01;

   //Initialize starting value of timer
   TCNT0=0x00;
}

/*
char conv_table[] = 
	{
   1,   2,   3, 100,
   4,   5,   6, 101,
   7,   8,   9, 102,
   0, 105, 104, 103 
 };


int CheckKey( ) 
{
	int i,j;
	
	    for(i=0; i<4; i++) 
		{ // Set one column at a time to 0 
			PORTC = 0xF0; //The 
			CLR_BIT(PORTC,(i+4));
			for(j = 0; j< 4; j++)//reads one row at a time
				{
					if(GET_BIT(PINC,j) == 0)//check for pressed button
					{
					  return conv_table[(i+(j*4))];
					}
			
				}
	
	   	}
		return 0xff;
    
}
int GetKey()
{
	int key;
	key = CheckKey();
	while(key == 0xFF)
	{
		key = CheckKey();
	}
	return key;
}
*/
int main()
{
   DDRA = 0xFF;

   //Enable Global Interrupts
   SREG |= (1<<7);

   InitTimer();

   //init state
   RT_State = INIT;

    while(1) 
	{
		
       RT_Tick();
       RT_ClkTick();
    }
}
