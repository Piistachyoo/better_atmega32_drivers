/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : SS_program.c                           				 */
/* Date          : Aug 19, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "SS_interface.h"

#define SS_PINS		7
uint8 SS_numbers_hexa[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
								0x6D, 0x7D, 0x07, 0x7F, 0x6f};


/**=============================================
 * @Fn			- SS_Init
 * @brief 		- Initializes GPIO pins for the seven segment
 * @param [in] 	- _SS: Pointer to the seven segment configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype SS_Init(SS_t *_SS){
	Std_Returntype ret = RET_OK;
	uint8 index;
	if(NULL == _SS)
		ret = RET_NOT_OK;
	else{
		if(SS_MODE_CommonAnode == _SS->mode){
			_SS->ON_State = GPIO_STATE_LOW;
			_SS->OFF_State = GPIO_STATE_HIGH;
		}
		else{
			_SS->ON_State = GPIO_STATE_HIGH;
			_SS->OFF_State = GPIO_STATE_LOW;
		}

		for(index = 0; index < SS_PINS; index++){
			/* Set initial state OFF for all segments */
			_SS->PIN[index].default_state = _SS->OFF_State;
			ret |= GPIO_PIN_Init(&(_SS->PIN[index]));
		}
	}
	return ret;
}

/**=============================================
 * @Fn			- SS_Display
 * @brief 		- Displays a number on the seven segments
 * @param [in] 	- _SS: Pointer to the seven segment configuration
 * @param [in] 	- _number: Number to be displayed on the seven segment @ref SS_NUMBERS_define
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- SS_Init MUST be called first
 */
Std_Returntype SS_Display(const SS_t* _SS, uint8 _number){
	Std_Returntype ret = RET_OK;
	uint8 index;
	if(NULL == _SS)
		ret = RET_NOT_OK;
	else{
		for(index = 0; index < SS_PINS; index++){
			if((SS_numbers_hexa[_number]>>index) & 0x01)
				ret |= GPIO_PIN_Write(&(_SS->PIN[index]), _SS->ON_State);
			else
				ret |= GPIO_PIN_Write(&(_SS->PIN[index]), _SS->OFF_State);
		}
	}
	return ret;
}
