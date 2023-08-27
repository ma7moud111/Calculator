/**********************************************************************/
/**********************************************************************/
/**************	   Author: Mahmoud Sayed	***************************/
/**************	   Layer: HAL 				***************************/
/**************	   Component: CLCD   	    ***************************/
/**************	   Version: 1.00			***************************/
/**********************************************************************/
/**********************************************************************/

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include <util/delay.h>

u8 CUR_POS = 0;

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/* 1- set RS pin to low for command */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);

	/* 2- set RW pin to low for write */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

	/* 3- set command to data pins */
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);

	/* 4- set pulse on the enable pin */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	/* 1- set RS pin to high for data */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_HIGH);

	/* 2- set RW pin to low for write */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

	/* 3- set data to data pins */
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);

	/* 4- set pulse on the enable pin */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
}

/* 8 bit initialization*/
void CLCD_voidInit(void)
{
	/*wait for more than 30 ms*/
	_delay_ms(40);

	/*function set command: 2 lines & 5*8 font size*/
	CLCD_voidSendCommand(0b00111000);

	/*display on off command: display enable, cursor disable, no blink cursor*/
	CLCD_voidSendCommand(0b00001100);

	/*clear display*/
	CLCD_voidSendCommand(0b00000001);
}

void CLCD_voidGoToXY(u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Local_u8Address;
	if(Copy_u8XPos == 0)
	{
		Local_u8Address = Copy_u8YPos;
	}
	else if(Copy_u8XPos == 1)
	{
		Local_u8Address = Copy_u8YPos + 0x40;
	}
	/*set DDRAM Address*/
	CLCD_voidSendCommand(Local_u8Address + 128);
}

void CLCD_voidSendString(const char* Copy_pcString)
{
	u8 Local_u8Counter = 0;
	while(Copy_pcString[Local_u8Counter] != '\0')
	{
		if(CUR_POS == 16){
			CLCD_voidGoToXY(1,0);
		}

		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
		CUR_POS++;
	}
}


void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8PatternNumber, u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAddress, Local_u8Iterator;

	/*calculate the GCRAM Address whose each block is 8 bytes*/
	Local_u8CGRAMAddress = Copy_u8PatternNumber * 8;

	/*send the physical address command of the CGRAM to LCD, setting bit 6 and clearing bit 7 */
	CLCD_voidSendCommand(Local_u8CGRAMAddress + 64);

	/*write the pattern into the CGRAM*/
	for(Local_u8Iterator = 0; Local_u8Iterator < 8; Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}

	/*returning to the DDRAM with a specific position on the LCD display*/
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);

	/*display the pattern written in the CGRAM on the LCD (dealing with the location of the data as the data itself)*/
	CLCD_voidSendData(Copy_u8PatternNumber);
	/**
	 * 	***** IMPORTANT NOTE ********
	 *
	 * - if the sendData function took an ascii value then it will access the CGROM to get this
	 *   ascii value and display it
	 *
	 * - if it took an number from 0 to 7 then it will access the CGRAM and display the pattern which
	 * 	 exists at this location or block form block 0 to block 7
	 */

}

void CLCD_voidWriteNumber(u32 Copy_u32Number)
{
	if(Copy_u32Number == 0)
	{
		return;
	}
	CLCD_voidWriteNumber(Copy_u32Number / 10);
	CLCD_voidSendData((Copy_u32Number % 10) + '0');
}


