/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : keypad_program.c                           			 */
/* Date          : Aug 22, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "keypad_interface.h"

/* Keypad buttons definition */
static uint8 Keypad_Buttons [KEYPAD_ROWS][KEYPAD_COLS] = {
		{ '7' ,  '8' ,  '9' , '/'},
		{ '4' ,  '5' ,  '6' , 'x'},
		{ '1' ,  '2' ,  '3' , '-'},
		{ 'C' ,  '0' ,  '=' , '+'}
};

/**=============================================
  * @Fn				- keypad_init
  * @brief 			- Initializes the keypad
  * @param [in] 	- KPD_cfg: pointer to the keypad configuration
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- Rows must be initialized by user as pull-up input and columns as output high
  */
Std_Returntype keypad_init(const KPD_t* KPD_cfg){
	Std_Returntype ret = RET_OK;
	uint8 iterator;
	if(NULL == KPD_cfg)
		ret = RET_NOT_OK;
	else{
		for(iterator = 0; iterator < KEYPAD_ROWS; iterator++)
			ret |= GPIO_PIN_Init(&(KPD_cfg->row[iterator]));

		for(iterator = 0; iterator < KEYPAD_COLS; iterator++)
			ret |= GPIO_PIN_Init(&(KPD_cfg->col[iterator]));
	}
	return ret;
}

/**=============================================
  * @Fn				- keypad_Get_Pressed_Key
  * @brief 			- Checks for any pressed key and returns the value of it
  * @param [in] 	- KPD_cfg: pointer to the keypad configuration
  * @param [out] 	- pressed_key: Value of the pressed key, or F if no key is pressed
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype keypad_Get_Pressed_Key(const KPD_t* KPD_cfg, uint8 *pressed_key){
	Std_Returntype ret = RET_OK;
	uint8 row_iterator, col_iterator, pin_state;
	uint8 found_flag = 0;
	*pressed_key = 'F'; // Default
	if(NULL == KPD_cfg)
		ret = RET_NOT_OK;
	else{
		for(col_iterator = 0; col_iterator < KEYPAD_COLS; col_iterator++){
			ret |= GPIO_PIN_Write(&(KPD_cfg->col[col_iterator]), GPIO_STATE_LOW);

			for(row_iterator = 0; row_iterator < KEYPAD_ROWS; row_iterator++){
				GPIO_PIN_Read(&(KPD_cfg->row[row_iterator]), &pin_state);
				if(GPIO_STATE_LOW == pin_state){
					while(GPIO_STATE_LOW == pin_state)
						GPIO_PIN_Read(&(KPD_cfg->row[row_iterator]), &pin_state);
					*pressed_key = Keypad_Buttons[row_iterator][col_iterator];
					found_flag = 1;
					break;
				}
			}
			ret |= GPIO_PIN_Write(&(KPD_cfg->col[col_iterator]), GPIO_STATE_HIGH);
			if(found_flag)
				break;
		}
	}
	return ret;
}
