/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : LED_interface.h                           			 */
/* Date          : Aug 19, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/
#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_

//----------------------------------------------
// Section: Includes
//----------------------------------------------
#include "../../MCAL/GPIO/GPIO_interface.h"

//----------------------------------------------
// Section: User type definitions
//----------------------------------------------
typedef struct{
	pinCfg_t led_pin;
	uint8 	 led_mode; // @ref LED_MODE_define
}LED_t;

//----------------------------------------------
// Section: Macros Configuration References
//----------------------------------------------

// @ref LED_MODE_define
#define LED_MODE_ActiveLow	0
#define LED_MODE_ActiveHigh	1

/*
 * =============================================
 * APIs Supported by "LED"
 * =============================================
 */

/**=============================================
 * @Fn			- LED_Init
 * @brief 		- Initializes GPIO pin for LED
 * @param [in] 	- _LED: pointer to the LED configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype LED_Init(const LED_t* _LED);

/**=============================================
 * @Fn			- LED_TurnOn
 * @brief 		- Turns the LED on
 * @param [in] 	- _LED: pointer to the LED configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype LED_TurnOn(const LED_t* _LED);

/**=============================================
 * @Fn			- LED_TurnOff
 * @brief 		- Turns the LED off
 * @param [in] 	- _LED: pointer to the LED configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype LED_TurnOff(const LED_t* _LED);

/**=============================================
 * @Fn			- LED_Toggle
 * @brief 		- Toggles the LED state
 * @param [in] 	- _LED: pointer to the LED configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype LED_Toggle(const LED_t* _LED);


#endif /* HAL_LED_LED_INTERFACE_H_ */
