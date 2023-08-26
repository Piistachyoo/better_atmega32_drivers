/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : ADC_interface.h                           			 */
/* Date          : Aug 26, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/
#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

//----------------------------------------------
// Section: Includes
//----------------------------------------------
#include "../ATMEGA32.h"

//----------------------------------------------
// Section: User type definitions
//----------------------------------------------
typedef struct{
	uint8 reference_voltage;	// @ref ADC_REFERENCE_define
	uint8 data_adjust;			// @ref ADC_ADJUST_define
	uint8 prescaler;			// @ref ADC_PRESCALE_define
	uint8 interrupt_status;		// @ref ADC_INTERRUPT_define
	void (*pf_callback)(void);
}ADC_cfg;

//----------------------------------------------
// Section: Macros Configuration References
//----------------------------------------------

#define ADC_VREF_VOLTAGE_MV		5000UL
#define ADC_RESOLUTION			1024UL

// @ref ADC_REFERENCE_define
#define ADC_REFERENCE_AREF		(0)
#define ADC_REFERENCE_AVCC		(0x40)
#define ADC_REFERENCE_INTERNAL	(0xC0U)

// @ref ADC_ADJUST_define
#define ADC_ADJUST_RIGHT		(0)
#define ADC_ADJUST_LEFT			(0x20)

// @ref ADC_INTERRUPT_define
#define ADC_INTERRUPT_ENABLE	(0x08)
#define ADC_INTERRUPT_DISABLE	(0)

// @ref ADC_PRESCALE_define
#define ADC_PRESCALE_2			1
#define ADC_PRESCALE_4			2
#define ADC_PRESCALE_8			3
#define ADC_PRESCALE_16			4
#define ADC_PRESCALE_32			5
#define ADC_PRESCALE_64			6
#define ADC_PRESCALE_128		7

// @ref ADC_PIN_define
#define ADC_PIN_0				0
#define ADC_PIN_1				1
#define ADC_PIN_2				2
#define ADC_PIN_3				3
#define ADC_PIN_4				4
#define ADC_PIN_5				5
#define ADC_PIN_6				6
#define ADC_PIN_7				7
#define ADC_PIN_MAX				8

/*
 * =============================================
 * APIs Supported by "ADC"
 * =============================================
 */

/**=============================================
 * @Fn			- ADC_Init
 * @brief 		- This function configures and enable the ADC
 * @param [in] 	- cfg: pointer to the ADC configuration
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype ADC_Init(ADC_cfg *cfg);

/**=============================================
 * @Fn			- ADC_Start_Conversion
 * @brief 		- This function starts conversion on specific ADC pin
 * @param [in] 	- PIN: specifies ADC pin @ref ADC_PIN_define
 * @param [in] 	- buffer: Pointer to the buffer that will return the conversion data if polling is enabled
 * @param [in] 	- poll_status: specifies if polling is used or not
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype ADC_Start_Conversion(uint8 PIN, uint16 *buffer, polling_t poll_status);

/**=============================================
 * @Fn			- ADC_SetCallBack
 * @brief 		- Sets the callback function
 * @param [in] 	- pf_callback: pointer to the function to be set as callback
 * @retval 		- return RET_OK if operation was successful, and returns RET_NOT_OK if an error happened
 * Note			- None
 */
Std_Returntype ADC_SetCallBack(void (*pf_callback)(void));


#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
