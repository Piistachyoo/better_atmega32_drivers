/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : PB_program.c                                          */
/* Date          : Aug 19, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "PB_interface.h"

/**=============================================
 * @Fn			- PB_Init
 * @brief 		- Initializes GPIO pin
 * @param [in] 	- _PB: pointer to the PB configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype PB_Init(const PB_t* _PB){
	Std_Returntype ret = RET_OK;
	if(NULL == _PB)
		ret = RET_NOT_OK;
	else{
		ret |= GPIO_PIN_Direction(&(_PB->pin), GPIO_INPUT);
		if(PB_MODE_PULLUP == _PB->mode)
			ret |= GPIO_PIN_Write(&(_PB->pin), GPIO_STATE_HIGH);
	}
	return ret;
}

/**=============================================
 * @Fn			- PB_Read
 * @brief 		- Reads the value of the push button
 * @param [in] 	- _PB: pointer to the PB configuration
 * @param [in] 	- _state: pointer to return value for the PB state @ref PB_STATE_define
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype PB_Read(const PB_t* _PB, uint8 *_state){
	Std_Returntype ret = RET_OK;
	if((NULL == _PB) || (NULL == _state))
		ret = RET_NOT_OK;
	else{
		ret |= GPIO_PIN_Read(&(_PB->pin), _state);
		if(PB_MODE_PULLUP == _PB->mode){
			*_state = (*_state == PB_PRESSED) ? PB_RELEASED : PB_PRESSED;
		}
		else{ /* Do Nothing */ }
	}
	return ret;
}
