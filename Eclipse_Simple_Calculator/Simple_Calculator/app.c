/*********************************************
 * File name: app.c
 * Description: source file for the Simple Calculator
 * Author: amr mohsen
 ********************************************/
#include "keypad.h"
#include "lcd.h"
#include <util/delay.h>

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
uint8 key;
uint8 num1_flag=0;
uint8 num2_flag=0;
uint16 num1=0;
uint16 num2=0;
uint16 result=0;
uint8 first_operand=0;

void SimpleCalculator_printResult();

/*******************************************************************************
 *                              Functions Definitions                           *
 *******************************************************************************/

/*
 * Description:
 * 1. get the first input number
 * 2. get the first input operand
 */
void SimpleCalculator_getFirst_Number()
{
	while(num1_flag==0)
	{
		key=KEYPAD_getPressedKey();

		switch(key)
		{
		/* clear Button */
		case 13:
			LCD_sendCommand(LCD_CLEAR_COMMAND);
			num1=0;
			num2=0;
			num1_flag=0;
			num2_flag=0;
			break;
		/*  '=' sign after first number */
		case 4:
			LCD_moveCursor(1,0);
			LCD_displayCharacter('/');
			num1_flag=1;
			break;
		/* end of first number and first operand */
		case '+':
			LCD_displayCharacter('+');
			first_operand='+';
			num1_flag=1;
			break;
		case '-':
			LCD_displayCharacter('-');
			first_operand='-';
			num1_flag=1;
			break;
		case '*':
			LCD_displayCharacter('*');
			first_operand='*';
			num1_flag=1;
			break;
		case '/':
			LCD_displayCharacter('/');
			first_operand='/';
			num1_flag=1;
			break;
		/* the num1 is still inserted */
		default:
			LCD_integerToString(key);
			num1=num1*10+ key;
			break;
		}
		_delay_ms(500);
	}
	num1_flag=0;
}

void SimpleCalculator_getSecond_Number()
{
	while(num2_flag==0)
	{
		key=KEYPAD_getPressedKey();

		switch(key)
		{
		/* clear Button */
		case 13:
			LCD_sendCommand(LCD_CLEAR_COMMAND);
			num1=0;
			num2=0;
			num1_flag=0;
			num2_flag=0;
			break;
		/* '=' means num2 is inserted and go to printResult on the second line */
		case '=':
			LCD_moveCursor(1,0);
			LCD_displayCharacter('=');
			num2_flag=1;
			SimpleCalculator_printResult();
			break;
		case '+':
			LCD_displayCharacter('+');
			break;
		case '-':
			LCD_displayCharacter('-');
			break;
		case '*':
			LCD_displayCharacter('*');
			break;
		case '/':
			LCD_displayCharacter('/');
			break;
		/* the num2 is still inserted */
		default:
			LCD_integerToString(key);
			num2=num2*10+ key;
			break;
		}
		_delay_ms(400);
	}
	num2_flag=0;

}

void SimpleCalculator_printResult()
{

	switch(first_operand)
	{
	case '+':
		result=num1+num2;
		LCD_integerToString(result);
		break;
	case '-':
		result=num1-num2;
		LCD_integerToString(result);
		break;
	case '*':
		result=num1*num2;
		LCD_integerToString(result);
		break;
	case '/':
		if(num2==0)
			LCD_displayString("Undefined");
		else
		{
			result=(uint16)((uint32)num1/num2);
			LCD_integerToString(result);
		}
		break;
	}
}



int main(void)
{
	/* LCD Initialization */
	LCD_init();

	while(1)
	{
		SimpleCalculator_getFirst_Number();

		SimpleCalculator_getSecond_Number();


	}
}


