/**********************************************************************/
/**********************************************************************/
/**************	   Author: Mahmoud Sayed	***************************/
/**************	   Layer: HAL 				***************************/
/**************	   SWC/Driver: Keypad		***************************/
/**************	   Version: 1.00			***************************/
/**********************************************************************/
/**********************************************************************/

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"

u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8PressedKey = KPD_NO_PRESSED_KEY, Local_u8ColIdx, Local_u8RowIdx, Local_u8PinState;
	static u8 Local_u8KPDArr[ROW_NUM][COLUMN_NUM] = KPD_ARR_VAL;
	static u8 Local_u8KPDColumnArr[COLUMN_NUM] = {KPD_COLUMN0_PIN, KPD_COLUMN1_PIN, KPD_COLUMN2_PIN, KPD_COLUMN3_PIN};
	static u8 Local_u8KPDRowArr[ROW_NUM] = {KPD_ROW0_PIN, KPD_ROW1_PIN, KPD_ROW2_PIN, KPD_ROW3_PIN};

	for(Local_u8ColIdx = 0; Local_u8ColIdx<COLUMN_NUM; Local_u8ColIdx++)
	{
		/*activate current column*/
		DIO_u8SetPinValue(KPD_PORT, Local_u8KPDColumnArr[Local_u8ColIdx], DIO_u8PIN_LOW);

		for(Local_u8RowIdx = 0; Local_u8RowIdx<ROW_NUM; Local_u8RowIdx++)
		{
			/*read the current row*/
			DIO_u8GetPinValue(KPD_PORT, Local_u8KPDRowArr[Local_u8RowIdx], &Local_u8PinState);

			/*check if the switch is pressed or not*/
			if(DIO_u8PIN_LOW == Local_u8PinState)
			{
				Local_u8PressedKey = Local_u8KPDArr[Local_u8RowIdx][Local_u8ColIdx];

				/*Polling (busy waiting) until the key is released*/
				while(DIO_u8PIN_LOW == Local_u8PinState)
				{
					DIO_u8GetPinValue(KPD_PORT, Local_u8KPDRowArr[Local_u8RowIdx], &Local_u8PinState);
				}
				return Local_u8PressedKey;	//for avoiding debouncing & avoiding 2 pressed buttons at the same time
			}
		}
		/*deactivate current column*/
		DIO_u8SetPinValue(KPD_PORT, Local_u8KPDColumnArr[Local_u8ColIdx], DIO_u8PIN_HIGH);
	}
	return Local_u8PressedKey;
}
