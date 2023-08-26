/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : SS_interface.h                           			 */
/* Date          : Aug 19, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/
#ifndef HAL_SEVEN_SEGMENT_SS_INTERFACE_H_
#define HAL_SEVEN_SEGMENT_SS_INTERFACE_H_

//----------------------------------------------
// Section: Includes
//----------------------------------------------
#include "../../MCAL/GPIO/GPIO_interface.h"

//----------------------------------------------
// Section: User type definitions
//----------------------------------------------
typedef struct{
	uint8 		mode;		// @ref SS_MODE_define
	uint8		ON_State;	// @ref GPIO_STATE_define
	uint8		OFF_State;	// @ref GPIO_STATE_define
	pinCfg_t 	PIN[7];
}SS_t;

//----------------------------------------------
// Section: Macros Configuration References
//----------------------------------------------

// @ref SS_MODE_define
#define SS_MODE_CommonAnode		0
#define SS_MODE_CommonCathode	1

/*
 * =============================================
 * APIs Supported by "Seven Segment"
 * =============================================
 */

/**=============================================
 * @Fn			- SS_Init
 * @brief 		- Initializes GPIO pins for the seven segment
 * @param [in] 	- _SS: Pointer to the seven segment configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype SS_Init(SS_t *_SS);

/**=============================================
 * @Fn			- SS_Display
 * @brief 		- Displays a number on the seven segments
 * @param [in] 	- _SS: Pointer to the seven segment configuration
 * @param [in] 	- _number: Number to be displayed (0 -> 9)
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- SS_Init MUST be called first
 */
Std_Returntype SS_Display(const SS_t* _SS, uint8 _number);


#endif /* HAL_SEVEN_SEGMENT_SS_INTERFACE_H_ */
