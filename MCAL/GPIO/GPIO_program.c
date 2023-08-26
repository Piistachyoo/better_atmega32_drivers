/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : GPIO_program.c                           			 */
/* Date          : Aug 19, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "GPIO_Interface.h"

/**=============================================
 * @Fn			- GPIO_PIN_Init
 * @brief 		- Initializes a pin's direction and initial state
 * @param [in] 	- _pin: Pointer to the pin configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PIN_Init(const pinCfg_t* _pin){
	Std_Returntype ret = RET_OK;
	if(NULL == _pin)
		ret = RET_NOT_OK;
	else{
		ret |= GPIO_PIN_Direction(_pin, _pin->direction);
		ret |= GPIO_PIN_Write(_pin, _pin->default_state);
	}
	return ret;
}

/**=============================================
 * @Fn			- GPIO_PIN_Direction
 * @brief 		- Sets a pin's direction to output or input
 * @param [in] 	- _pin: Pointer to the pin configuration
 * @param [in] 	- _direction: defines if the pin is output or input @ref GPIO_DIRECTION_define
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PIN_Direction(const pinCfg_t* _pin, uint8 _direction){
	Std_Returntype ret = RET_OK;
	if(NULL == _pin)
		ret = RET_NOT_OK;
	else{
		if(GPIO_OUTPUT == _direction)
			_pin->GPIOx->DDR |= (1U << _pin->pin);
		else if(GPIO_INPUT == _direction)
			_pin->GPIOx->DDR &= ~(1U << _pin->pin);
		else
			ret = RET_NOT_OK;
	}
	return ret;
}

/**=============================================
 * @Fn			- GPIO_PIN_Write
 * @brief 		- Sets a pin's state to high or low
 * @param [in] 	- _pin: Pointer to the pin configuration
 * @param [in] 	- _state: defines if the pin is high or low @ref GPIO_STATE_define
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PIN_Write(const pinCfg_t* _pin, uint8 _state){
	Std_Returntype ret = RET_OK;
	if(NULL == _pin)
		ret = RET_NOT_OK;
	else{
		if(GPIO_STATE_HIGH == _state)
			_pin->GPIOx->PORT |= (1U << _pin->pin);
		else if(GPIO_STATE_LOW == _state)
			_pin->GPIOx->PORT &= ~(1U << _pin->pin);
		else
			ret = RET_NOT_OK;
	}
	return ret;
}

/**=============================================
 * @Fn			- GPIO_PIN_Read
 * @brief 		- Returns the value of the pin if high or low
 * @param [in] 	- _pin: Pointer to the pin configuration
 * @param [in] 	- _state: pointer to a variable that will return the pin's state
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PIN_Read(const pinCfg_t* _pin, uint8* _state){
	Std_Returntype ret = RET_OK;
	if((NULL == _pin) || (NULL == _state))
		ret = RET_NOT_OK;
	else
		*_state = ((_pin->GPIOx->PIN >> _pin->pin) & 0x01);
	return ret;
}

/**=============================================
 * @Fn			- GPIO_PIN_Toggle
 * @brief 		- Toggles a pin's state
 * @param [in] 	- _pin: Pointer to the pin configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PIN_Toggle(const pinCfg_t* _pin){
	Std_Returntype ret = RET_OK;
	if(NULL == _pin)
		ret = RET_NOT_OK;
	else
		_pin->GPIOx->PORT ^= (1U<<_pin->pin);
	return ret;
}

/**=============================================
 * @Fn			- GPIO_PORT_Init
 * @brief 		- Initializes a port's state and direction
 * @param [in] 	- GPIOx: The choosen port to be initialized (GPIOA/GPIOB/GPIOC/GPIOD)
 * @param [in] 	- _direction: defines the direction of the port
 * @param [in] 	- _state: defines the output value of the port
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PORT_Init(GPIO_Typedef* GPIOx, uint8 _direction, uint8 _state){
	Std_Returntype ret = RET_OK;
	if(NULL == GPIOx)
		ret = RET_NOT_OK;
	else{
		ret |= GPIO_PORT_Direction(GPIOx, _direction);
		ret |= GPIO_PORT_Write(GPIOx, _state);
	}
	return ret;
}

/**=============================================
 * @Fn			- GPIO_PORT_Direction
 * @brief 		- Sets a port's direction
 * @param [in] 	- GPIOx: The choosen port to be initialized (GPIOA/GPIOB/GPIOC/GPIOD)
 * @param [in] 	- _direction: defines the direction of the port
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PORT_Direction(GPIO_Typedef* GPIOx, uint8 _direction){
	Std_Returntype ret = RET_OK;
	if(NULL == GPIOx)
		ret = RET_NOT_OK;
	else
		GPIOx->DDR = _direction;
	return ret;
}

/**=============================================
 * @Fn			- GPIO_PORT_Write
 * @brief 		- Set's a port's state
 * @param [in] 	- GPIOx: The choosen port to be initialized (GPIOA/GPIOB/GPIOC/GPIOD)
 * @param [in] 	- _state: defines the output value of the port
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PORT_Write(GPIO_Typedef* GPIOx, uint8 _state){
	Std_Returntype ret = RET_OK;
	if(NULL == GPIOx)
		ret = RET_NOT_OK;
	else
		GPIOx->PORT = _state;
	return ret;
}

/**=============================================
 * @Fn			- GPIO_PORT_Write
 * @brief 		- Reads a port's state
 * @param [in] 	- GPIOx: The choosen port to be initialized (GPIOA/GPIOB/GPIOC/GPIOD)
 * @param [in] 	- _state: pointer to the variable that will return the port state
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PORT_Read(GPIO_Typedef* GPIOx, uint8 *_state){
	Std_Returntype ret = RET_OK;
	if((NULL == GPIOx) || (NULL == _state))
		ret = RET_NOT_OK;
	else
		*_state = GPIOx->PIN;
	return ret;
}

/**=============================================
 * @Fn			- GPIO_PORT_Toggle
 * @brief 		- Toggle's a port state
 * @param [in] 	- GPIOx: The choosen port to be initialized (GPIOA/GPIOB/GPIOC/GPIOD)
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype GPIO_PORT_Toggle(GPIO_Typedef* GPIOx){
	Std_Returntype ret = RET_OK;
	if(NULL == GPIOx)
		ret = RET_NOT_OK;
	else
		GPIOx->PORT ^= GPIOx->PORT;
	return ret;
}
