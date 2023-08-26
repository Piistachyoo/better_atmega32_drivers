/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : keypad_interface.h                           		 */
/* Date          : Aug 22, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/
#ifndef HAL_KEYPAD_KEYPAD_INTERFACE_H_
#define HAL_KEYPAD_KEYPAD_INTERFACE_H_

//----------------------------------------------
// Section: Includes
//----------------------------------------------
#include "../../MCAL/GPIO/GPIO_interface.h"


//----------------------------------------------
// Section: Macros Configuration References
//----------------------------------------------
#define KEYPAD_ROWS		4
#define KEYPAD_COLS		4

// @ref Module_Ref_Name_define

//----------------------------------------------
// Section: User type definitions
//----------------------------------------------
typedef struct{
	pinCfg_t	row[KEYPAD_ROWS];
	pinCfg_t	col[KEYPAD_COLS];
}KPD_t;


/*
 * =============================================
 * APIs Supported by "Keypad"
 * =============================================
 */

/**=============================================
  * @Fn				- keypad_init
  * @brief 			- Initializes the keypad
  * @param [in] 	- KPD_cfg: pointer to the keypad configuration
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- Rows must be initialized by user as pull-up input and columns as output high
  */
Std_Returntype keypad_init(const KPD_t* KPD_cfg);

/**=============================================
  * @Fn				- keypad_Get_Pressed_Key
  * @brief 			- Checks for any pressed key and returns the value of it
  * @param [in] 	- KPD_cfg: pointer to the keypad configuration
  * @param [out] 	- pressed_key: Value of the pressed key, or F if no key is pressed
  * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
  * Note			- None
  */
Std_Returntype keypad_Get_Pressed_Key(const KPD_t* KPD_cfg, uint8 *pressed_key);

#endif /* HAL_KEYPAD_KEYPAD_INTERFACE_H_ */
