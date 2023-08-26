/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : LCD_program.c                           				 */
/* Date          : Aug 22, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include <stdlib.h>
#include "LCD_interface.h"
#include <util/delay.h>

static Std_Returntype LCD_GPIO_Init(LCD_t* LCD_cfg){
	Std_Returntype ret = RET_OK;
	uint8 iterator;
	ret |= GPIO_PIN_Init(&(LCD_cfg->RS_PIN));
	ret |= GPIO_PIN_Init(&(LCD_cfg->RW_PIN));
	ret |= GPIO_PIN_Init(&(LCD_cfg->EN_PIN));
	for(iterator = 0; iterator < LCD_cfg->mode; iterator++)
		ret |= GPIO_PIN_Init(&(LCD_cfg->D_PINS[iterator]));
	return ret;
}

/**=============================================
  * @Fn				- LCD_Init
  * @brief 			- Initialized LCD based on user defined configurations
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- User must set configurations @ref LCD_CONFIG_define
  */
Std_Returntype LCD_Init(LCD_t* LCD_cfg){
	Std_Returntype ret = RET_OK;
	uint8 iterator;
	if(NULL == LCD_cfg)
		ret = RET_NOT_OK;
	else{
		ret |= LCD_GPIO_Init(LCD_cfg);
		_delay_ms(30);
		/* Send Function Set */
		if(LCD_8BIT == LCD_cfg->mode){
			ret |= LCD_Send_Command(LCD_cfg, LCD_8BIT_MODE_2_LINE);
		}
		else if(LCD_4BIT == LCD_cfg->mode){
			for(iterator = 0; iterator < LCD_cfg->mode; iterator++)
				ret |= GPIO_PIN_Write(&(LCD_cfg->D_PINS[iterator]), ((LCD_4BIT_MODE_2_LINE >> (iterator + 4)) & 0x01));
			_delay_us(80);
			ret |= LCD_Send_Enable_Signal(LCD_cfg);
			_delay_us(300);
			ret |= LCD_Send_Command(LCD_cfg, LCD_4BIT_MODE_2_LINE);
		}
		else{ /* Do Nothing */ }
		_delay_us(50);
		/* Send Display On/Off control */
		ret |= LCD_Send_Command(LCD_cfg, LCD_cfg->Display_Mode);
		_delay_us(50);
		/* Display Clear */
		ret |= LCD_Send_Command(LCD_cfg, LCD_CLEAR_DISPLAY);
		_delay_ms(2);
		ret |= LCD_Send_Command(LCD_cfg, LCD_cfg->Entry_Mode);
	}
	return ret;
}

/**=============================================
  * @Fn				- LCD_Send_Command
  * @brief 			- Sends a command to the LCD to be executed
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- command: command to be executed @ref LCD_COMMANDS_define
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_Command(LCD_t* LCD_cfg, uint8 command){
	Std_Returntype ret = RET_OK;
	uint8 iterator;
	if(NULL == LCD_cfg)
		ret = RET_NOT_OK;
	else{
		ret |= GPIO_PIN_Write(&(LCD_cfg->RW_PIN), GPIO_STATE_LOW);
		ret |= GPIO_PIN_Write(&(LCD_cfg->RS_PIN), GPIO_STATE_LOW);
		_delay_us(40);
		if(LCD_8BIT == LCD_cfg->mode){
			for(iterator = 0; iterator < LCD_cfg->mode; iterator++)
				ret |= GPIO_PIN_Write(&(LCD_cfg->D_PINS[iterator]), ((command >> iterator) & 0x01));
		}
		else if(LCD_4BIT == LCD_cfg->mode){
			for(iterator = 0; iterator < LCD_cfg->mode; iterator++)
				ret |= GPIO_PIN_Write(&(LCD_cfg->D_PINS[iterator]), ((command >> (iterator + 4)) & 0x01));

			LCD_Send_Enable_Signal(LCD_cfg);

			for(iterator = 0; iterator < LCD_cfg->mode; iterator++)
				ret |= GPIO_PIN_Write(&(LCD_cfg->D_PINS[iterator]), ((command >> iterator) & 0x01));
		}
		else{ /* Do Nothing */ }
		ret |= LCD_Send_Enable_Signal(LCD_cfg);
	}
	return ret;
}

/**=============================================
  * @Fn				- LCD_Send_Char
  * @brief 			- Sends a char to the LCD to be displayed
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- Char: ASCII character to be displayed on screen
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_Char(LCD_t* LCD_cfg, uint8 Char){
	Std_Returntype ret = RET_OK;
	uint8 iterator;
	if(NULL == LCD_cfg)
		ret = RET_NOT_OK;
	else{
		ret |= GPIO_PIN_Write(&(LCD_cfg->RW_PIN), GPIO_STATE_LOW);
		ret |= GPIO_PIN_Write(&(LCD_cfg->RS_PIN), GPIO_STATE_HIGH);
		_delay_us(40);
		if(LCD_8BIT == LCD_cfg->mode){
			for(iterator = 0; iterator < LCD_cfg->mode; iterator++)
				ret |= GPIO_PIN_Write(&(LCD_cfg->D_PINS[iterator]), ((Char >> iterator) & 0x01));
		}
		else if(LCD_4BIT == LCD_cfg->mode){
			for(iterator = 0; iterator < LCD_cfg->mode; iterator++)
				ret |= GPIO_PIN_Write(&(LCD_cfg->D_PINS[iterator]), ((Char >> (iterator + 4)) & 0x01));

			LCD_Send_Enable_Signal(LCD_cfg);

			for(iterator = 0; iterator < LCD_cfg->mode; iterator++)
				ret |= GPIO_PIN_Write(&(LCD_cfg->D_PINS[iterator]), ((Char >> iterator) & 0x01));
		}
		else{ /* Do Nothing */ }
		ret |= LCD_Send_Enable_Signal(LCD_cfg);
	}
	return ret;
}

/**=============================================
  * @Fn				- LCD_Send_Char_Pos
  * @brief 			- Sends a char to the LCD to be displayed at a specific location
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- Char: ASCII character to be displayed on screen
  * @param [in] 	- row: Selects the row number of the displayed character @ref LCD_ROWS_POS_define
  * @param [in] 	- column: Selects the column number of the displayed character (1...16)
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_Char_Pos(LCD_t* LCD_cfg, uint8 Char, uint8 row, uint8 column){
	Std_Returntype ret = RET_OK;
	if(NULL == LCD_cfg)
		ret = RET_NOT_OK;
	else{
		ret |= LCD_Set_Cursor(LCD_cfg, row, column);
		ret |= LCD_Send_Char(LCD_cfg, Char);
	}
	return ret;
}

/**=============================================
  * @Fn				- LCD_Send_String
  * @brief 			- Sends a string to the LCD to be displayed
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- string: pointer to a string of characters to be displayed on LCD
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_String(LCD_t* LCD_cfg, uint8 *string){
	Std_Returntype ret = RET_OK;
	if((NULL == LCD_cfg) || (NULL == string))
		ret = RET_NOT_OK;
	else{
		while(*string)
			ret |= LCD_Send_Char(LCD_cfg, *string++);
	}
	return ret;
}

/**=============================================
  * @Fn				- LCD_Send_string_Pos
  * @brief 			- Sends a string to the LCD to be displayed at a specific location
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- string: pointer to a string of characters to be displayed on LCD
  * @param [in] 	- row: Selects the row number of the displayed character @ref LCD_ROWS_POS_define
  * @param [in] 	- column: Selects the column number of the displayed character (1...16)
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_string_Pos(LCD_t* LCD_cfg, uint8 *string, uint8 row, uint8 column){
	Std_Returntype ret = RET_OK;
	if(NULL == LCD_cfg)
		ret = RET_NOT_OK;
	else{
		ret |= LCD_Set_Cursor(LCD_cfg, row, column);
		ret |= LCD_Send_String(LCD_cfg, string);
	}
	return ret;
}

/**=============================================
  * @Fn				- LCD_Send_Number
  * @brief 			- Sends a number to the LCD to be displayed
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- number: signed integer to be displayed
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_Number(LCD_t* LCD_cfg, sint32 number){
	uint8 buffer[50];
	Std_Returntype ret = RET_OK;
	if(NULL == LCD_cfg)
		ret = RET_NOT_OK;
	else{
		itoa(number, (char*)buffer, 10);
		ret |= LCD_Send_String(LCD_cfg, buffer);
	}
	return ret;
}

/**=============================================
  * @Fn				- LCD_Send_Number_Pos
  * @brief 			- Sends a number to the LCD to be displayed at specific row and column
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- number: signed integer to be displayed
  * @param [in] 	- row: Selects the row number of the displayed character @ref LCD_ROWS_POS_define
  * @param [in] 	- column: Selects the column number of the displayed character (1...16)
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_Number_Pos(LCD_t* LCD_cfg, sint32 number, uint8 row, uint8 column){
	Std_Returntype ret = RET_OK;
	if(NULL == LCD_cfg)
		ret = RET_NOT_OK;
	else{
		ret |= LCD_Set_Cursor(LCD_cfg, row, column);
		ret |= LCD_Send_Number(LCD_cfg, number);
	}
	return ret;
}

/**=============================================
  * @Fn				- LCD_Shift_Display
  * @brief 			- Shifts the LCD display to the left or right for a number of iterations
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- direction: direction to be shifted @ref LCD_SHIFT_DIRECTION_define
  * @param [in] 	- iterations: Number of times the display will be shifted
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Shift_Display(LCD_t* LCD_cfg, uint8 direction, uint8 iterations){
	Std_Returntype ret = RET_OK;
	uint8 shift_cmd = ((LCD_SHIFT_RIGHT == direction) ? LCD_COMMAND_SHIFT_RIGHT : LCD_COMMAND_SHIFT_LEFT);
	uint8 iterator;
	if(NULL == LCD_cfg)
		ret = RET_NOT_OK;
	else{
		for(iterator = 0; iterator < iterations; iterator++)
			ret |= LCD_Send_Command(LCD_cfg, shift_cmd);
	}
	return ret;
}

/**=============================================
  * @Fn				- LCD_Save_Special_Character
  * @brief 			- Saves new special character in the LCD
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- location: location in CGRAM for the new special character
  * @param [in] 	- character: Pointer to the array of characters representing the special character
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Save_Special_Character(LCD_t* LCD_cfg, uint8 location, uint8 *character){
	Std_Returntype ret = RET_OK;
	uint8 iterator;
	if(NULL == LCD_cfg)
		ret = RET_NOT_OK;
	else{
		ret |= LCD_Send_Command(LCD_cfg, (LCD_CGRAM_START | (location * 8)));
		for(iterator = 0; iterator < 8; iterator++)
			ret |= LCD_Send_Char(LCD_cfg, character[iterator]);
		LCD_Set_Cursor(LCD_cfg, LCD_FIRST_ROW, 1);
	}
	return ret;
}

/**=============================================
  * @Fn				- LCD_Send_Enable_Signal
  * @brief 			- Sends enable signal to the LCD
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_Enable_Signal(LCD_t* LCD_cfg){
	Std_Returntype ret = RET_OK;
	if(NULL == LCD_cfg)
		ret = RET_NOT_OK;
	else{
		ret |= GPIO_PIN_Write(&(LCD_cfg->EN_PIN), GPIO_STATE_HIGH);
		_delay_us(150);
		ret |= GPIO_PIN_Write(&(LCD_cfg->EN_PIN), GPIO_STATE_LOW);
		_delay_us(300);
	}
	return ret;
}

/**=============================================
  * @Fn				- LCD_Set_Cursor
  * @brief 			- Sets the location of the cursor
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- row: Selects the row number of the displayed character @ref LCD_ROWS_POS_define
  * @param [in] 	- column: Selects the column number of the displayed character (1...16)
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Set_Cursor(LCD_t* LCD_cfg, uint8 row, uint8 column){
	Std_Returntype ret = RET_OK;
	if(NULL == LCD_cfg)
		ret = RET_NOT_OK;
	else
		ret |= LCD_Send_Command(LCD_cfg, (row + (column - 1)));
	return ret;
}
