/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : EXTI_program.c                          				 */
/* Date          : Aug 26, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "EXTI_interface.h"

static void (*EXTI_Callback_Functions[3])(void);

/**=============================================
 * @Fn			- EXTI_Init
 * @brief 		- Initializes EXTI (INT0-INT2) and enables global interrupt
 * @param [in] 	- cfg: pointer to the struct containing the EXTI configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype EXTI_Init(const EXTI_cfg* cfg){
	Std_Returntype ret = RET_OK;
	if(NULL == cfg)
		ret |= RET_NOT_OK;
	else{
		switch(cfg->number){
		case EXTI_INT0:
			/* Disable INT0 */
			EXTI->GICR.INT0 = 0;

			/* Set the corresponding trigger */
			EXTI->MCUCR.ISC0 = cfg->mode;

			/* Set the callback function */
			if(cfg->pf_CallBack)
				EXTI_Callback_Functions[0] = cfg->pf_CallBack;

			/* Enable INT0 */
			EXTI->GICR.INT0 = 1;

			/* Enable global interrupts */
			GLOBAL_INTERRUPT_ENABLE();
			break;
		case EXTI_INT1:
			/* Disable INT1 */
			EXTI->GICR.INT1 = 0;

			/* Set the corresponding trigger */
			EXTI->MCUCR.ISC1 = cfg->mode;

			/* Set the callback function */
			if(cfg->pf_CallBack)
				EXTI_Callback_Functions[1] = cfg->pf_CallBack;

			/* Enable INT1 */
			EXTI->GICR.INT1 = 1;

			/* Enable global interrupts */
			GLOBAL_INTERRUPT_ENABLE();
			break;
		case EXTI_INT2:
			/* Disable INT2 */
			EXTI->GICR.INT2 = 0;

			/* Set the corresponding trigger */
			if(EXTI_TRIGGER_FALLING_EDGE == cfg->mode)
				EXTI->MCUCSR.ISC2 = 0;
			else if(EXTI_TRIGGER_RISING_EDGE == cfg->mode)
				EXTI->MCUCSR.ISC2 = 1;
			else
				ret |= RET_NOT_OK;

			/* Set the callback function */
			if(cfg->pf_CallBack)
				EXTI_Callback_Functions[2] = cfg->pf_CallBack;

			/* Enable INT0 */
			EXTI->GICR.INT2 = 1;

			/* Enable global interrupts */
			GLOBAL_INTERRUPT_ENABLE();
			break;
		default: ret |= RET_NOT_OK; break;
		}
	}
	return ret;
}

/**=============================================
 * @Fn			- EXTI_DeInit
 * @brief 		- Stops the EXTI (INT0-INT2)
 * @param [in] 	- number: number of INT pin to be disabled (INT0-INT2) @ref EXTI_define
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype EXTI_DeInit(uint8 number){
	Std_Returntype ret = RET_OK;
	if(EXTI_INT0 == number)
		EXTI->GICR.INT0;
	else if(EXTI_INT1 == number)
		EXTI->GICR.INT1;
	else if(EXTI_INT2 == number)
		EXTI->GICR.INT2;
	else
		ret |= RET_NOT_OK;
	return ret;
}

/**=============================================
 * @Fn			- EXTI_SetCallBack
 * @brief 		- Sets the callback function of a specific EXTI
 * @param [in] 	- number: number of INT pin to be disabled (INT0-INT2) @ref EXTI_define
 * @param [in] 	- pf_callback: pointer to the function to be set as callback
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype EXTI_SetCallBack(uint8 number, void (*pf_callback)(void)){
	Std_Returntype ret = RET_OK;
	if(NULL == pf_callback)
		ret |= RET_NOT_OK;
	else{
		if(EXTI_INT0 == number)
			EXTI_Callback_Functions[0] = pf_callback;
		else if(EXTI_INT1 == number)
			EXTI_Callback_Functions[1] = pf_callback;
		else if(EXTI_INT2 == number)
			EXTI_Callback_Functions[2] = pf_callback;
		else
			ret |= RET_NOT_OK;
	}
	return ret;
}

/* INT0_ISR */
void __vector_1(void) __attribute__((signal));
void __vector_1(void){
	if(EXTI_Callback_Functions[0])
		EXTI_Callback_Functions[0]();
}

/* INT1_ISR */
void __vector_2(void) __attribute__((signal));
void __vector_2(void){
	if(EXTI_Callback_Functions[1])
		EXTI_Callback_Functions[1]();
}

/* INT2_ISR */
void __vector_3(void) __attribute__((signal));
void __vector_3(void){
	if(EXTI_Callback_Functions[2])
		EXTI_Callback_Functions[2]();
}
