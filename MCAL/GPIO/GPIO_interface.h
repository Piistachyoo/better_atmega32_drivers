/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : GPIO_interface.h                                      */
/* Date          : Aug 19, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/
#ifndef MCAL_GPIO_GPIO_INTERFACE_H_
#define MCAL_GPIO_GPIO_INTERFACE_H_

//----------------------------------------------
// Section: Includes
//----------------------------------------------
#include "../ATMEGA32.h"

//----------------------------------------------
// Section: User type definitions
//----------------------------------------------
typedef struct{
	GPIO_Typedef* 	GPIOx;
	uint8			direction;		// @ref GPIO_DIRECTION_define
	uint8			pin;			// @ref GPIO_PIN_define
	uint8			default_state; 	// @ref GPIO_STATE_define
}pinCfg_t;



//----------------------------------------------
// Section: Macros Configuration References
//----------------------------------------------

// @ref GPIO_PIN_define
#define GPIO_PIN_0		0
#define GPIO_PIN_1		1
#define GPIO_PIN_2		2
#define GPIO_PIN_3		3
#define GPIO_PIN_4		4
#define GPIO_PIN_5		5
#define GPIO_PIN_6		6
#define GPIO_PIN_7		7

// @ref GPIO_STATE_define
#define GPIO_STATE_LOW	0U
#define GPIO_STATE_HIGH	1U

// @ref GPIO_DIRECTION_define
#define GPIO_INPUT		0U
#define GPIO_OUTPUT		1U

/*
 * =============================================
 * APIs Supported by "GPIO"
 * =============================================
 */

/**=============================================
 * @Fn			- GPIO_PIN_Init
 * @brief 		- Initializes a pin's direction and initial state
 * @param [in] 	- _pin: Pointer to the pin configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PIN_Init(const pinCfg_t* _pin);

/**=============================================
 * @Fn			- GPIO_PIN_Direction
 * @brief 		- Sets a pin's direction to output or input
 * @param [in] 	- _pin: Pointer to the pin configuration
 * @param [in] 	- _direction: defines if the pin is output or input @ref GPIO_DIRECTION_define
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PIN_Direction(const pinCfg_t* _pin, uint8 _direction);

/**=============================================
 * @Fn			- GPIO_PIN_Write
 * @brief 		- Sets a pin's state to high or low
 * @param [in] 	- _pin: Pointer to the pin configuration
 * @param [in] 	- _state: defines if the pin is high or low @ref GPIO_STATE_define
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PIN_Write(const pinCfg_t* _pin, uint8 _state);

/**=============================================
 * @Fn			- GPIO_PIN_Read
 * @brief 		- Returns the value of the pin if high or low
 * @param [in] 	- _pin: Pointer to the pin configuration
 * @param [in] 	- _state: pointer to a variable that will return the pin's state
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PIN_Read(const pinCfg_t* _pin, uint8* _state);

/**=============================================
 * @Fn			- GPIO_PIN_Toggle
 * @brief 		- Toggles a pin's state
 * @param [in] 	- _pin: Pointer to the pin configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PIN_Toggle(const pinCfg_t* _pin);

/**=============================================
 * @Fn			- GPIO_PORT_Init
 * @brief 		- Initializes a port's state and direction
 * @param [in] 	- GPIOx: The choosen port to be initialized (GPIOA/GPIOB/GPIOC/GPIOD)
 * @param [in] 	- _direction: defines the direction of the port
 * @param [in] 	- _state: defines the output value of the port
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PORT_Init(GPIO_Typedef* GPIOx, uint8 _direction, uint8 _state);

/**=============================================
 * @Fn			- GPIO_PORT_Direction
 * @brief 		- Sets a port's direction
 * @param [in] 	- GPIOx: The choosen port to be initialized (GPIOA/GPIOB/GPIOC/GPIOD)
 * @param [in] 	- _direction: defines the direction of the port
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PORT_Direction(GPIO_Typedef* GPIOx, uint8 _direction);

/**=============================================
 * @Fn			- GPIO_PORT_Write
 * @brief 		- Set's a port's state
 * @param [in] 	- GPIOx: The choosen port to be initialized (GPIOA/GPIOB/GPIOC/GPIOD)
 * @param [in] 	- _state: defines the output value of the port
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PORT_Write(GPIO_Typedef* GPIOx, uint8 _state);

/**=============================================
 * @Fn			- GPIO_PORT_Write
 * @brief 		- Reads a port's state
 * @param [in] 	- GPIOx: The choosen port to be initialized (GPIOA/GPIOB/GPIOC/GPIOD)
 * @param [in] 	- _state: pointer to the variable that will return the port state
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PORT_Read(GPIO_Typedef* GPIOx, uint8 *_state);

/**=============================================
 * @Fn			- GPIO_PORT_Toggle
 * @brief 		- Toggle's a port state
 * @param [in] 	- GPIOx: The choosen port to be initialized (GPIOA/GPIOB/GPIOC/GPIOD)
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PORT_Toggle(GPIO_Typedef* GPIOx);


#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */
