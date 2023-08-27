/**********************************************************************/
/**********************************************************************/
/**************		Author: Mahmoud Sayed	***************************/
/**************		Layer: MCAL 			***************************/
/**************		SWC/Driver : DIO 		***************************/
/**************		Version: 1.00			***************************/
/**********************************************************************/
/**********************************************************************/

// assuming files in the same project folder not in a separate folders
#include "STD_TYPES.h"			
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"
#include "DIO_register.h"

/*
u8 DIO_u8SetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
	u8 Local_u8ErrorState = 0;
	if(Copy_u8Pin <= DIO_u8PIN7)
	{
		switch(Copy_u8Port)
		{
		case DIO_u8PORTA:
			if(Copy_u8Direction == DIO_u8PIN_OUTPUT)
				SET_BIT(DDRA,Copy_u8Pin);
			else if(Copy_u8Direction == DIO_u8PIN_INPUT)
				CLR_BIT(DDRA,Copy_u8Pin);
			else
				Local_u8ErrorState = 1;
			break;

		case DIO_u8PORTB:
			if(Copy_u8Direction == DIO_u8PIN_OUTPUT)
				SET_BIT(DDRB,Copy_u8Pin);
			else if(Copy_u8Direction == DIO_u8PIN_INPUT)
				CLR_BIT(DDRB,Copy_u8Pin);
			else
				Local_u8ErrorState = 1;
			break;

		case DIO_u8PORTC:
			if(Copy_u8Direction == DIO_u8PIN_OUTPUT)
				SET_BIT(DDRC,Copy_u8Pin);
			else if(Copy_u8Direction == DIO_u8PIN_INPUT)
				CLR_BIT(DDRC,Copy_u8Pin);
			else
				Local_u8ErrorState = 1;
			break;

		case DIO_u8PORTD:
			if(Copy_u8Direction == DIO_u8PIN_OUTPUT)
				SET_BIT(DDRD,Copy_u8Pin);
			else if(Copy_u8Direction == DIO_u8PIN_INPUT)
				CLR_BIT(DDRD,Copy_u8Pin);
			else
				Local_u8ErrorState = 1;
			break;

		default:
			Local_u8ErrorState = 1;
			break;
		}
	}
	else
	{
		Local_u8ErrorState = 1;
	}
	return Local_u8ErrorState;
	
}
*/

/****************************************************************************/
/*
u8 DIO_u8SetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction)		// direction means the value passed by user to set 
port with it
{
	u8 Local_u8ErrorState;
	switch(Copy_u8Port)
	{
	case DIO_u8PORTA:
		DDRA = Copy_u8Direction;
		Local_u8ErrorState = 0;
		break;

	case DIO_u8PORTB:
		DDRB = Copy_u8Direction;
		Local_u8ErrorState = 0;
		break;

	case DIO_u8PORTC:
		DDRC = Copy_u8Direction;
		Local_u8ErrorState = 0;
		break;

	case DIO_u8PORTD:
		DDRD = Copy_u8Direction;
		Local_u8ErrorState = 0;
		break;

	default:
		Local_u8ErrorState = 1;
		break;
	}
	return Local_u8ErrorState;
}
*/

/*************************************************************************************/

u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	u8 Local_u8ErrorState = 0;
	switch(Copy_u8Port)
	{
	case DIO_u8PORTA:
		if(Copy_u8Value == DIO_u8PIN_HIGH)
			SET_BIT(PORTA,Copy_u8Pin);
		else if(Copy_u8Value == DIO_u8PIN_LOW)
			CLR_BIT(PORTA,Copy_u8Pin);
		else
			Local_u8ErrorState = 1;
		break;

	case DIO_u8PORTB:
		if(Copy_u8Value == DIO_u8PIN_HIGH)
			SET_BIT(PORTB,Copy_u8Pin);
		else if(Copy_u8Value == DIO_u8PIN_LOW)
			CLR_BIT(PORTB,Copy_u8Pin);
		else
			Local_u8ErrorState = 1;
		break;

	case DIO_u8PORTC:
		if(Copy_u8Value == DIO_u8PIN_HIGH)
			SET_BIT(PORTC,Copy_u8Pin);
		else if(Copy_u8Value == DIO_u8PIN_LOW)
			CLR_BIT(PORTC,Copy_u8Pin);
		else
			Local_u8ErrorState = 1;
		break;

	case DIO_u8PORTD:
		if(Copy_u8Value == DIO_u8PIN_HIGH)
			SET_BIT(PORTD,Copy_u8Pin);
		else if(Copy_u8Value == DIO_u8PIN_LOW)
			CLR_BIT(PORTD,Copy_u8Pin);
		else
			Local_u8ErrorState = 1;
		break;

	default:
		Local_u8ErrorState = 1;
		break;
	}
	return Local_u8ErrorState;
}

/*************************************************************/

u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	u8 Local_u8ErrorState;
	switch(Copy_u8Port)
	{
	case DIO_u8PORTA:
		PORTA = Copy_u8Value;
		Local_u8ErrorState = 0;
		break;

	case DIO_u8PORTB:
		PORTB = Copy_u8Value;
		Local_u8ErrorState = 0;
		break;

	case DIO_u8PORTC:
		PORTC = Copy_u8Value;
		Local_u8ErrorState = 0;
		break;

	case DIO_u8PORTD:
		PORTD = Copy_u8Value;
		Local_u8ErrorState = 0;
		break;

	default:
		Local_u8ErrorState = 1;
		break;
	}
	return Local_u8ErrorState;
}

/*************************************************************/
u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* Copy_pu8Value)
{
	u8 Local_u8ErrorState;

	if(Copy_pu8Value == NULL || Copy_u8Pin > DIO_u8PIN7)
	{
		Local_u8ErrorState = 1;
	}
	else
	{
		switch(Copy_u8Port)
		{
		case DIO_u8PORTA:
			*Copy_pu8Value = GET_BIT(PINA, Copy_u8Pin);
			Local_u8ErrorState = 0;
			break;

		case DIO_u8PORTB:
			*Copy_pu8Value = GET_BIT(PINB, Copy_u8Pin);
			Local_u8ErrorState = 0;
			break;

		case DIO_u8PORTC:
			*Copy_pu8Value = GET_BIT(PINC, Copy_u8Pin);
			Local_u8ErrorState = 0;
			break;

		case DIO_u8PORTD:
			*Copy_pu8Value = GET_BIT(PIND, Copy_u8Pin);
			Local_u8ErrorState = 0;
			break;

		default:
			Local_u8ErrorState = 1;
			break;
		}
	}
	return Local_u8ErrorState;
}

/****************************************************************/

u8 DIO_u8TogglePinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	u8 Local_u8ErrorState;
	switch(Copy_u8Port)
	{
	case DIO_u8PORTA:
		TOGGLE_BIT(PORTA, Copy_u8Pin);
		Local_u8ErrorState = 0;
		break;

	case DIO_u8PORTB:
		TOGGLE_BIT(PORTB, Copy_u8Pin);
		Local_u8ErrorState = 0;
		break;

	case DIO_u8PORTC:
		TOGGLE_BIT(PORTC, Copy_u8Pin);;
		Local_u8ErrorState = 0;
		break;

	case DIO_u8PORTD:
		TOGGLE_BIT(PORTD, Copy_u8Pin);
		Local_u8ErrorState = 0;
		break;

	default:
		Local_u8ErrorState = 1;
		break;
	}
	return Local_u8ErrorState;	
}


