/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : PB_interface.h                                        */
/* Date          : Aug 19, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/
#ifndef HAL_PB_PB_INTERFACE_H_
#define HAL_PB_PB_INTERFACE_H_

//----------------------------------------------
// Section: Includes
//----------------------------------------------
#include "../../MCAL/GPIO/GPIO_interface.h"

//----------------------------------------------
// Section: User type definitions
//----------------------------------------------
typedef struct{
	pinCfg_t	pin;
	uint8 		mode; // @ref PB_MODE_define
}PB_t;

//----------------------------------------------
// Section: Macros Configuration References
//----------------------------------------------

// @ref PB_MODE_define
#define PB_MODE_PULLUP		0
#define PB_MODE_PULLDOWN	1

// @ref PB_STATE_define
#define PB_PRESSED			1
#define PB_RELEASED			0

/*
 * =============================================
 * APIs Supported by "Push Button"
 * =============================================
 */

/**=============================================
 * @Fn			- PB_Init
 * @brief 		- Initializes GPIO pin
 * @param [in] 	- _PB: pointer to the PB configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype PB_Init(const PB_t* _PB);

/**=============================================
 * @Fn			- PB_Read
 * @brief 		- Reads the value of the push button
 * @param [in] 	- _PB: pointer to the PB configuration
 * @param [in] 	- _state: pointer to return value for the PB state @ref PB_STATE_define
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype PB_Read(const PB_t* _PB, uint8 *_state);


#endif /* HAL_PB_PB_INTERFACE_H_ */
