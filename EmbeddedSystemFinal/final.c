#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#include <stdlib.h>
#include <stdio.h>
#include "speaker.h"

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))


const unsigned int RT_Period = 1;
volatile unsigned int RT_Clk = 0;
unsigned int RT_Counter = 0;
const unsigned int ONE_MS = 4;
const int length = 25;
const int look_up[4] = {1,2,4,8};


ISR(TIMER0_OVF_vect) 
{ //Timer0 overflow interrupt service routine
   //Put code in me!
   //Count up to period and set flag
   RT_Counter++;
	if(RT_Counter == (RT_Period * ONE_MS))
	{
		RT_Counter = 0;
		RT_Clk = 1;
	}   
}



int Pin_Receive()
{
	int i;
	for(i=0;i<4;i++)
	{
		if(GET_BIT(PIND,i)!= 0)
		{
			PORTD = GET_BIT(PIND,i) << 4;
			return GET_BIT(PIND,i);
		}
	}
	return 0;
}

void RT_ClkTick() 
{
   //Put code in me!
   //wait until ISR sets flag
   
   while(!RT_Clk)
    { }
	
   	RT_Clk = 0;
}

enum Game_States {Wait, Show, Check_Value, Win, Lose};
enum Input_States {Check_Pressed, Check_Release};
unsigned char mem_array[25] = {0};
//unsigned char mem_array[25] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int value = 0;
int total_count = 1;
int shock_flag = 0;
int Input_Tick(int state)
{
	switch(state)
	{
		case -1:
			break;
		case Check_Pressed:
			total_count+=6;
			break;
		case Check_Release:

			total_count*=total_count;
			break;

	}
	switch(state)
	{
		case -1:
			state = Check_Pressed;
			break;
		case Check_Pressed:
			total_count++;

		
			if(Pin_Receive() != 0)
			{
				value = Pin_Receive();
				state = Check_Release;
				LCD_DisplayString(1,"Received.");	
			}
			else if(shock_flag == 1)
			{
				PORTC = 0x00;
				PORTD = 0x00;
				state = Check_Release;
			}

			else
			{
				state = Check_Pressed;
			}
			break;
		case Check_Release:
			total_count++;
	
		
			if(Pin_Receive() != 0)
			{

				state = Check_Release;
			}

			else if(shock_flag == 1)
			{
				PORTC = 0xFF;
				PORTD = 0xFF;
				state = Check_Pressed;
			}

			else
			{

				PORTD = 0;
				state = Check_Pressed;
			}
			break;

	}

	return state;
}


int Game_Tick(int state)
{
	static int restart;
	static int high = 0;
	static int lost;
	static int convert;
	static int ocount;
	static int icount;
	static int level;
	static char score[3];
//	static int wait_count;
	switch(state)//actions
	{
		case -1:
			break;

		case Wait:
			shock_flag = 0;
			PORTC = 0;
			lost = 0;
			restart = 0;
	
			total_count++;
			itoa(high,score,10);
			LCD_DisplayStrings(1,"Press Blue.HS:",score);//dont forget high score
			convert = (((total_count + RT_Counter) % 150) + 1  * 11) % 4;
			mem_array[0] = look_up[convert];
			ocount = 0;
			icount = 0;
			level = 1;
			break;

		case Show:
			PORTD = 0;
			PORTC = 0;
			total_count*=3;
		//	wait_count = 6;
			LCD_DisplayString(1,"Generating..");
			PORTD = (mem_array[ocount]) << 4;
			ocount++;
			icount = 0;
			break;

		case Check_Value:
			PORTD = 0;
			total_count+=total_count;
			LCD_DisplayString(1,"Your Turn!");
			if(value != 0)
			{
				if(value == mem_array[icount])
				{
					icount++;
					value = 0;
					
				}
				else
				{
					lost = 1;
				}
			}
		//	if(value == 0)
		//	{
		//		if(wait_count == 0)
		//		{
		//			lost = 1;
		//		}
		//		wait_count--;
		//	}
			break;

		case Win:
			total_count++;
			LCD_DisplayString(1,"Winner!");
			PORTD = 0xFF;
			restart = 1;
			if(level > high)
			{
				high = level;
			}
			break;

		case Lose:
			total_count/=7;
			LCD_DisplayString(1,"Owned");
			shock_flag = 1;
			restart = 1;
			if(level > high)
			{
				high = level;
			}
			break;
	
      	default:

         break;
	}
	switch(state)//transitions
	{
		case -1:
			state = Wait;
			break;

		case Wait:
			total_count++;
			if(value == 1)
			{
				state = Show;
				value = 0;
			}
			else
			{
				state = Wait;
			}
			break;

		case Show:
			total_count++;
			if(ocount != (level))
			{
				state = Show;
			}

			else
			{
			//	LCD_DisplayString(1,"DEBUG!");
				state = Check_Value;
			}
			break;
			
		case Check_Value:
			total_count++;
			if(lost == 1)
			{
				state = Lose;
			}
			else if(level == 24)
			{
				state = Win;
			}
			else if(icount != (level))
			{
				state = Check_Value;
			}
			else
			{
				LCD_DisplayString(1,"Correct!!");
				state = Show;
				convert = (((total_count + RT_Counter) % 150) + 1  * 11) % 4;
				mem_array[level] = look_up[convert];
				ocount = 0;
				level++;
			}
			break;

		case Win:
			total_count-=9;
			state = Wait;
			break;

		case Lose:
			total_count*=3;
			if(value != 0)
			{
				state = Wait;
				value = 0;
			}
			else
			{
				state = Lose;
			}

			break;


      	default:
			state = Wait;
         break;

	}

	return state;
}


//Configure ATMega32 Timer0 control registers.  Correct values can be found in ATMega32 datasheet.
void InitTimer() 
{
   // Set prescaler to 8.  Since the ATMega32 runs at 8Mhz, our timer clock will run at 8MHz/8 = 1MHz.
   TCCR0 |= 0x02;
   //TCCR2 |= 0x02;

   //Enable Overflow Interrupt Enable on Timer0.  
   TIMSK |= 0x01;

   //Initialize starting value of timer
   TCNT0=0x00;
   //TCNT2=0x00;
}

typedef struct task {
   //tasks should have members that include period, state, a function pointer, and a measurement of elapsed time.
	int state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int (*TickFct) (int);
} task;

//implement scheduler code from PES Chapter 7
int main()
{

   DDRA = 0xFF; 
   DDRB = 0xFF;
   DDRC = 0x0F;
   DDRD = 0xFF;
//	InitSpeaker();
   
   LCD_init();
   LCD_ClearScreen();
   //Enable Global Interrupts
   SREG |= (1<<7);
   InitTimer(); 

	const unsigned long int P_Period = 200;
	const unsigned long int C_Period = 1000;
	unsigned long int i;

	task task1, task2;

	task *tasks[2] = {&task1, &task2};

	task1.state = -1;
	task1.period = P_Period;
	task1.elapsedTime = 0;
	task1.TickFct = &Input_Tick;

	task2.state = -1;
	task2.period = C_Period;
	task2.elapsedTime = 0;
	task2.TickFct = &Game_Tick;

   while(1) {
      //scheduler code
	  for(i = 0; i < 2; i++)
	  {
		if(tasks[i]->elapsedTime >= tasks[i]->period)
		{
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += RT_Period;

	  }
	  RT_ClkTick();

	}
   
   return 0;
}
