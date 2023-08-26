/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : LED_program.c                           				 */
/* Date          : Aug 19, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "LED_interface.h"

/**=============================================
 * @Fn			- LED_Init
 * @brief 		- Initializes GPIO pin for LED
 * @param [in] 	- _LED: pointer to the LED configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype LED_Init(const LED_t* _LED){
	Std_Returntype ret = RET_OK;
	if(NULL == _LED)
		ret = RET_NOT_OK;
	else
		ret = GPIO_PIN_Init(&(_LED->led_pin));
	return ret;
}

/**=============================================
 * @Fn			- LED_TurnOn
 * @brief 		- Turns the LED on
 * @param [in] 	- _LED: pointer to the LED configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype LED_TurnOn(const LED_t* _LED){
	Std_Returntype ret = RET_OK;
	uint8 LED_HIGH_VALUE;
	if(NULL == _LED)
		ret = RET_NOT_OK;
	else{
		LED_HIGH_VALUE = ((LED_MODE_ActiveHigh == _LED->led_mode) ? GPIO_STATE_HIGH : GPIO_STATE_LOW);
		ret = GPIO_PIN_Write(&(_LED->led_pin), LED_HIGH_VALUE);
	}
	return ret;
}

/**=============================================
 * @Fn			- LED_TurnOff
 * @brief 		- Turns the LED off
 * @param [in] 	- _LED: pointer to the LED configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype LED_TurnOff(const LED_t* _LED){
	Std_Returntype ret = RET_OK;
	uint8 LED_OFF_VALUE;
	if(NULL == _LED)
		ret = RET_NOT_OK;
	else{
		LED_OFF_VALUE = ((LED_MODE_ActiveHigh == _LED->led_mode) ? GPIO_STATE_LOW : GPIO_STATE_HIGH);
		ret = GPIO_PIN_Write(&(_LED->led_pin), LED_OFF_VALUE);
	}
	return ret;
}

/**=============================================
 * @Fn			- LED_Toggle
 * @brief 		- Toggles the LED state
 * @param [in] 	- _LED: pointer to the LED configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype LED_Toggle(const LED_t* _LED){
	Std_Returntype ret = RET_OK;
	if(NULL == _LED)
		ret = RET_NOT_OK;
	else
		ret = GPIO_PIN_Toggle(&(_LED->led_pin));
	return ret;
}
