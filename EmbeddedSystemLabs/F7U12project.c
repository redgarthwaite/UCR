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
	if(RT_Counter >= (RT_Period * ONE_MS))
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

enum LCD_States {Display};
enum Game_States {Wait,Show,Check_Pressed,Check_Release,Check_Value};
unsigned char mem_array[25] = {0};

int Game_Tick(int state)
{
	int i;
	static int value = 0;
	static int ocount = 0;
	static int icount = 0;
	static int level = 1;
	switch(state)//actions
	{
		case -1:
			break;
		case Wait:
			LCD_DisplayString(1,"Press Blue.");
			break;
		case Show:
			LCD_DisplayString(1,"Generating..");
			PORTD = (mem_array[ocount]) << 4;
			ocount++;
			icount = 0;
			break;
		case Check_Pressed:
			break;
		case Check_Release:
			break;
		case Check_Value:
			 if(value == mem_array[icount])
			{
				icount++;
			}
			else
			{
				PORTC = 0x02;
			}
			ocount = 0;
			break;
	}
	switch(state)//transitions
	{
		case -1:
			state = Wait;
			break;
		case Wait:
			if(Pin_Receive() == 1)
			{
				state = Show;
				//generate array
				for(i=0;i<length;i++ )
				{
					int convert = i % 4;
					mem_array[i] = look_up[convert];	
				}
			}
			else
			{
				state = Wait;
			}
			break;
		case Show:
			if(ocount != level)
			{
				state = Show;
			}
			else
			{
				state = Check_Pressed;
			}
			break;

		case Check_Pressed:
			if(Pin_Receive() != 0)
			{
				value = Pin_Receive();
				state = Check_Release;
				
			}
			else
			{
				state = Check_Pressed;
			}
			break;
		case Check_Release:
			if(Pin_Receive() != 0)
			{
				state = Check_Release;
			}
			else
			{
				PORTD = 0;
				state = Check_Value;
			}
			break;

		case Check_Value:
			if(icount != level)
			{
				state = Check_Pressed;
			}
			else
			{
				state = Show;
				level++;
				PORTC = 0x01;
			}
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
  // SREG |= (1<<7);
   //InitTimer(); 
		int state = -1;

	while(1)
	{
	  state = Game_Tick(state);

	}
	
//	const unsigned long int P_Period = 50;
//	const unsigned long int C_Period = 1000;
//	unsigned long int i;
//
//	task task1, task2;
//	task *task[numTasks] = {&task1, &task2};
//
//	task1.state = -1;
//	task1.period = P_Period;
//	task1.elapsedTime = 0;
//	task1.TickFct = &Producer_SMTick;
//
//	task2.state = -1;
//	task2.period = C_Period;
//	task2.elapsedTime = 0;
//	task2.TickFct = &Consumer_SMTick;

  // while(1) {
      //scheduler code
//	task[0]->state = task[0]->TickFct(task[0]->state);

//		if(task[1]->elapsedTime == task[1]->period)
//		{
//			task[1]->state = task[1]->TickFct(task[1]->state);
//			task[1]->elapsedTime = 0;
//		}
//		task[1]->elapsedTime += RT_Period;
//


	//}
   
//   printString("Error: Program should not exit");
   return 0;
}
