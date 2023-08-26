/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : LCD_interface.h                           			 */
/* Date          : Aug 22, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/
#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

//----------------------------------------------
// Section: Includes
//----------------------------------------------
#include "../../MCAL/GPIO/GPIO_interface.h"

//----------------------------------------------
// Section: User type definitions
//----------------------------------------------
typedef enum{
	LCD_4BIT = 4,
	LCD_8BIT = 8
}LCD_MODE_t;

typedef struct{
	LCD_MODE_t 	mode;
	uint8		Display_Mode; 	// @ref LCD_COMMANDS_define
	uint8		Entry_Mode;		// @ref LCD_COMMANDS_define
	pinCfg_t	RS_PIN;
	pinCfg_t	RW_PIN;
	pinCfg_t	EN_PIN;
	pinCfg_t	D_PINS[8];
}LCD_t;

//----------------------------------------------
// Section: Macros Configuration References
//----------------------------------------------

// @ref LCD_COMMANDS_define

#define LCD_CLEAR_DISPLAY              				(0x01)
#define LCD_RETURN_HOME                				(0x02)
#define LCD_ENTRY_MODE_DEC_SHIFT_OFF   				(0x04)
#define LCD_ENTRY_MODE_DEC_SHIFT_ON    				(0x05)
#define LCD_ENTRY_MODE_INC_SHIFT_OFF   				(0x06)
#define LCD_ENTRY_MODE_INC_SHIFT_ON    				(0x07)
#define LCD_CURSOR_MOVE_SHIFT_LEFT     				(0x10)
#define LCD_CURSOR_MOVE_SHIFT_RIGHT    				(0x14)
#define LCD_DISPLAY_SHIFT_LEFT         				(0x18)
#define LCD_DISPLAY_SHIFT_RIGHT        				(0x1C)
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF    	(0x0C)
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON     	(0x0D)
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF     	(0x0E)
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON      	(0x0F)
#define LCD_DISPLAY_OFF_CURSOR_OFF                 	(0x08)
#define LCD_8BIT_MODE_2_LINE           				(0x38)
#define LCD_4BIT_MODE_2_LINE           				(0x28)
#define LCD_COMMAND_SHIFT_RIGHT						(0x1C)
#define LCD_COMMAND_SHIFT_LEFT						(0x18)
#define LCD_CGRAM_START								(0x40)

// @ref LCD_ROWS_POS_define

#define LCD_FIRST_ROW								(0x80)
#define LCD_SECOND_ROW								(0xC0)
#define LCD_THIRD_ROW								(0x94)
#define LCD_FOURTH_ROW								(0xD4)

// @ref LCD_SHIFT_DIRECTION_define

#define LCD_SHIFT_RIGHT		0
#define LCD_SHIFT_LEFT		1

/*
 * =============================================
 * APIs Supported by "LCD"
 * =============================================
 */

/**=============================================
  * @Fn				- LCD_Init
  * @brief 			- Initialized LCD based on user defined configurations
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- User must set configurations @ref LCD_CONFIG_define
  */
Std_Returntype LCD_Init(LCD_t* LCD_cfg);

/**=============================================
  * @Fn				- LCD_Send_Command
  * @brief 			- Sends a command to the LCD to be executed
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- command: command to be executed @ref LCD_COMMANDS_define
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_Command(LCD_t* LCD_cfg, uint8 command);

/**=============================================
  * @Fn				- LCD_Send_Char
  * @brief 			- Sends a char to the LCD to be displayed
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- Char: ASCII character to be displayed on screen
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_Char(LCD_t* LCD_cfg, uint8 Char);

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
Std_Returntype LCD_Send_Char_Pos(LCD_t* LCD_cfg, uint8 Char, uint8 row, uint8 column);

/**=============================================
  * @Fn				- LCD_Send_String
  * @brief 			- Sends a string to the LCD to be displayed
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- string: pointer to a string of characters to be displayed on LCD
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_String(LCD_t* LCD_cfg, uint8 *string);

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
Std_Returntype LCD_Send_string_Pos(LCD_t* LCD_cfg, uint8 *string, uint8 row, uint8 column);

/**=============================================
  * @Fn				- LCD_Send_Number
  * @brief 			- Sends a number to the LCD to be displayed
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- number: signed integer to be displayed
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_Number(LCD_t* LCD_cfg, sint32 number);

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
Std_Returntype LCD_Send_Number_Pos(LCD_t* LCD_cfg, sint32 number, uint8 row, uint8 column);

/**=============================================
  * @Fn				- LCD_Shift_Display
  * @brief 			- Shifts the LCD display to the left or right for a number of iterations
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- direction: direction to be shifted @ref LCD_SHIFT_DIRECTION_define
  * @param [in] 	- iterations: Number of times the display will be shifted
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Shift_Display(LCD_t* LCD_cfg, uint8 direction, uint8 iterations);

/**=============================================
  * @Fn				- LCD_Save_Special_Character
  * @brief 			- Saves new special character in the LCD
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- location: location in CGRAM for the new special character
  * @param [in] 	- character: Pointer to the array of characters representing the special character
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Save_Special_Character(LCD_t* LCD_cfg, uint8 location, uint8 *character);

/**=============================================
  * @Fn				- LCD_Send_Enable_Signal
  * @brief 			- Sends enable signal to the LCD
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Send_Enable_Signal(LCD_t* LCD_cfg);

/**=============================================
  * @Fn				- LCD_Set_Cursor
  * @brief 			- Sets the location of the cursor
  * @param [in] 	- LCD_cfg: Pointer to the structure containing LCD configuration
  * @param [in] 	- row: Selects the row number of the displayed character @ref LCD_ROWS_POS_define
  * @param [in] 	- column: Selects the column number of the displayed character (1...16)
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype LCD_Set_Cursor(LCD_t* LCD_cfg, uint8 row, uint8 column);



#endif /* HAL_LCD_LCD_INTERFACE_H_ */
