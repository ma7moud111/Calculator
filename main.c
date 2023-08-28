/********************************************************************/
/******************	  Author: Mahmoud Sayed 			*************/
/******************	  Project title: Simple Calculator	*************/
/********************************************************************/

#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KEYPAD_interface.h"
#include <util/delay.h>


void main(void)
{

	u8 Local_u8Key, Local_u8Operation;
	u32 Local_u32Num1Int = 0, Local_u32Num2Int = 0, Local_u32Result ;

	PORT_voidInit();
	CLCD_voidInit();

	while(1)
	{
		/*getting the first number and the operation*/
		while(1)
		{
			do{
				Local_u8Key = KPD_u8GetPressedKey();
			}while(Local_u8Key == 0xff);

			if(Local_u8Key == '/' || Local_u8Key == 'x' || Local_u8Key == '-' || Local_u8Key == '+')
			{
				CLCD_voidSendData(Local_u8Key);
				Local_u8Operation = Local_u8Key;
				break;
			}
			else if(Local_u8Key == 'z')
			{
				CLCD_voidSendCommand(0x01);
				goto END_OF_PROGRAM;
			}
			CLCD_voidSendData(Local_u8Key + '0');
			Local_u32Num1Int = Local_u32Num1Int * 10 + (Local_u8Key);
		}

		/*getting the second number*/
		while(1)
		{
			do{
				Local_u8Key = KPD_u8GetPressedKey();
			}while(Local_u8Key == 0xff);

			if(Local_u8Key == '=')
			{
						CLCD_voidSendData(Local_u8Key);
						break;
			}
			else if(Local_u8Key == '/' || Local_u8Key == 'x' || Local_u8Key == '+')
			{
				CLCD_voidSendData(Local_u8Key);
				CLCD_voidGoToXY(1,1);
				CLCD_voidSendString("Error!");
				goto END_OF_PROGRAM;
			}
			else if(Local_u8Key == 'z')
			{
				CLCD_voidSendCommand(0x01);
				goto END_OF_PROGRAM;
			}
			CLCD_voidSendData(Local_u8Key + '0');
			Local_u32Num2Int = Local_u32Num2Int * 10 + (Local_u8Key);
		}


		/*perform the operation*/
		switch (Local_u8Operation)
		{
		case '+':
			Local_u32Result = (Local_u32Num1Int + Local_u32Num2Int);
			break;
		case '-':
			if(Local_u32Num1Int < Local_u32Num2Int)
			{
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendData('-');
				Local_u32Result = (Local_u32Num2Int - Local_u32Num1Int);
			}
			else
			{
				Local_u32Result = (Local_u32Num1Int - Local_u32Num2Int);
			}
			break;
		case 'x':
			Local_u32Result = (Local_u32Num1Int * Local_u32Num2Int);
			break;
		case '/':
			if(Local_u32Num2Int == 0)
			{
				CLCD_voidWriteNumber(Local_u8Key);
				CLCD_voidGoToXY(1,1);
				CLCD_voidSendString("Error!");
				goto END_OF_PROGRAM;
			}
			Local_u32Result = (Local_u32Num1Int / Local_u32Num2Int);
			break;
		default:
			CLCD_voidSendString("Error!");
			break;
		}

		/*write the answer in the second line of the LCD*/
		CLCD_voidGoToXY(1,1);

		/*Print the answer on the LCD*/
		CLCD_voidWriteNumber(Local_u32Result);

		do{
			Local_u8Key = KPD_u8GetPressedKey();
		}while(Local_u8Key == 0xff);

		END_OF_PROGRAM:
		if(Local_u8Key == 'z')
			CLCD_voidSendCommand(0x01);

		Local_u32Num1Int = 0;
		Local_u32Num2Int = 0;

	}
}
