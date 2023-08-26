/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : EXTI_interface.h                          			 */
/* Date          : Aug 26, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/
#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

//----------------------------------------------
// Section: Includes
//----------------------------------------------
#include "../ATMEGA32.h"

//----------------------------------------------
// Section: User type definitions
//----------------------------------------------
typedef struct{
	uint8 number; 	// @ref EXTI_define
	uint8 mode;		// @ref EXTI_TRIGGER_define
	void (*pf_CallBack)(void);
}EXTI_cfg;

//----------------------------------------------
// Section: Macros Configuration References
//----------------------------------------------

// @ref EXTI_define
#define EXTI_INT0	6
#define EXTI_INT1	7
#define EXTI_INT2	5

// @ref EXTI_TRIGGER_define
#define EXTI_TRIGGER_LOW_LEVEL			0
#define EXTI_TRIGGER_ANY_CHANGE			1
#define EXTI_TRIGGER_FALLING_EDGE		2
#define EXTI_TRIGGER_RISING_EDGE		3

/*
 * =============================================
 * APIs Supported by "EXTI"
 * =============================================
 */

/**=============================================
 * @Fn			- EXTI_Init
 * @brief 		- Initializes EXTI (INT0-INT2) and enables global interrupt
 * @param [in] 	- cfg: pointer to the struct containing the EXTI configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype EXTI_Init(const EXTI_cfg* cfg);

/**=============================================
 * @Fn			- EXTI_DeInit
 * @brief 		- Stops the EXTI (INT0-INT2)
 * @param [in] 	- number: number of INT pin to be disabled (INT0-INT2) @ref EXTI_define
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype EXTI_DeInit(uint8 number);

/**=============================================
 * @Fn			- EXTI_SetCallBack
 * @brief 		- Sets the callback function of a specific EXTI
 * @param [in] 	- number: number of INT pin to be disabled (INT0-INT2) @ref EXTI_define
 * @param [in] 	- pf_callback: pointer to the function to be set as callback
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype EXTI_SetCallBack(uint8 number, void (*pf_callback)(void));


#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
