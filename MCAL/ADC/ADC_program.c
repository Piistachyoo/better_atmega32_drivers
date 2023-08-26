/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : ADC_program.c                           				 */
/* Date          : Aug 26, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "ADC_interface.h"

static void (*ADC_Callback)(void);

static ADC_cfg g_ADC_CFG;

/**=============================================
 * @Fn			- ADC_Init
 * @brief 		- This function configures and enable the ADC
 * @param [in] 	- cfg: pointer to the ADC configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype ADC_Init(ADC_cfg *cfg){
	Std_Returntype ret = RET_OK;
	uint8 temp_reg;
	if(NULL == cfg)
		ret |= RET_NOT_OK;
	else{
		/* Save configuration in global variable */
		g_ADC_CFG = *cfg;

		/* Disable ADC */
		ADC->ADCSRA.ADEN = 0;

		/* ADMUX Register configuration */
		temp_reg = cfg->reference_voltage | cfg->data_adjust;
		ADC->ADMUX.ADMUX_REG = temp_reg;

		/* ADCSRA Register configuration */
		temp_reg = cfg->interrupt_status | cfg->prescaler;
		ADC->ADCSRA.ADCSRA_REG = temp_reg;

		/* Set callback function and enable global interrupt if interrupt is enabled */
		if(cfg->interrupt_status){
			ADC_Callback = cfg->pf_callback;
			GLOBAL_INTERRUPT_ENABLE();
		}

		/* Enable ADC */
		ADC->ADCSRA.ADEN = 1;
	}
	return ret;
}

/**=============================================
 * @Fn			- ADC_Start_Conversion
 * @brief 		- This function starts conversion on specific ADC pin
 * @param [in] 	- PIN: specifies ADC pin @ref ADC_PIN_define
 * @param [in] 	- buffer: Pointer to the buffer that will return the conversion data if polling is enabled
 * @param [in] 	- poll_status: specifies if polling is used or not
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype ADC_Start_Conversion(uint8 PIN, uint16 *buffer, polling_t poll_status){
	Std_Returntype ret = RET_OK;
	/* Select the ADC pin */
	if(ADC_PIN_MAX > PIN)
		ADC->ADMUX.MUX = PIN;
	else
		ret |= RET_NOT_OK;

	/* Validate that user sent the correct pin number */
	if(RET_OK == ret){
		/* Start conversion */
		ADC->ADCSRA.ADSC = 1;

		/* Poll if polling is enabled */
		if(pollingEnable == poll_status){
			while(0 == ADC->ADCSRA.ADIF); // while flag is not set
			ADC->ADCSRA.ADIF = 1; // Clear flag
			if(ADC_ADJUST_LEFT == g_ADC_CFG.data_adjust)
				*buffer = ((ADC->ADCLH.ADCL + (ADC->ADCLH.ADCH << 8)) >> 6);
			else
				*buffer = (ADC->ADCLH.ADCL | (ADC->ADCLH.ADCH << 8));
		}
		else{ /* Do Nothing */ }
	}
	else
		ret |= RET_NOT_OK;

	return ret;
}

/**=============================================
 * @Fn			- ADC_SetCallBack
 * @brief 		- Sets the callback function
 * @param [in] 	- pf_callback: pointer to the function to be set as callback
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype ADC_SetCallBack(void (*pf_callback)(void)){
	Std_Returntype ret = RET_OK;
	if(NULL == pf_callback)
		ret |= RET_NOT_OK;
	else{
		ADC_Callback = pf_callback;
	}
	return ret;
}

/* ADC_ISR */
void __vector_16(void) __attribute__((signal));
void __vector_16(void){
	if(ADC_Callback)
		ADC_Callback();
}
