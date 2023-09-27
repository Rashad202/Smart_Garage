/*
 * main.c
 *
 *  Created on: 26 Sep 2023
 *      Author: Rashad
 */


#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/TIMERS/TIMER1/TIMER1_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/SERVO_MOTOR/SERVO_Interface.h"
#include "avr/delay.h"


void StartProgram			 (void);

void main ()
{

	DIO_voidSetPortDirection(DIO_PORTA,DIO_OUTPUT);

	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN3,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN6,DIO_INPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN7,DIO_INPUT);

	TIMER1_voidInit ();
	LCD_voidInit();
	StartProgram();
	_delay_ms(500);
	LCD_voidClearDisplay();
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("There are 0 cars");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("garage has space");

	u8 flag1=0,flag2=0,IR1,IR2,counter=0;

	while (1)
	{
		IR1=DIO_u8GetPinValue(DIO_PORTD,DIO_PIN6);
		if(IR1==1 && flag1==0 && counter<4)
		{
			DIO_voidSetPinValue(DIO_PORTA,counter,DIO_HIGH);
			counter++;
			LCD_voidGoTo_XY(0,10);
			LCD_voidWriteChar(counter+'0');
			flag1=1;
			if(counter==4)
			{
				LCD_voidClearDisplay();
				LCD_voidWriteString("there are 4 cars");
				LCD_voidGoTo_XY(1,0);
				LCD_voidWriteString("garage  is full");
			}
			SERVO_voidRotateSpecificAngle_OC1A(90);

			_delay_ms(500);
			SERVO_voidRotateSpecificAngle_OC1A(0);
		}
		else if(IR1==0)
		{
			flag1=0;
		}
		/*-----------------------------------------*/
		IR2=DIO_u8GetPinValue(DIO_PORTD,DIO_PIN7);
		if(IR2==1 && flag2==0 && counter>0)
		{
			counter--;
			DIO_voidSetPinValue(DIO_PORTA,counter,DIO_LOW);
			LCD_voidGoTo_XY(0,10);
			LCD_voidWriteChar(counter+'0');
			flag2=1;
			LCD_voidGoTo_XY(1,0);
			LCD_voidWriteString("garage has space");
			SERVO_voidRotateSpecificAngle_OC1B(90);
			_delay_ms(500);
			SERVO_voidRotateSpecificAngle_OC1B(0);
		}
		else if(IR2==0)
		{
			flag2=0;
		}
	}








}
/*                      Welcome Massage                       */
void StartProgram (void)
{
	LCD_voidClearDisplay();
	LCD_voidGoTo_XY (0,1);
	LCD_voidWriteString (" Welcome To MY");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("  Smart Garage  ");
}

