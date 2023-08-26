/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : main.c                           					 */
/* Date          : Aug 19, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "../HAL/LCD/LCD_interface.h"
#include "util/delay.h"
#include "../MCAL/ADC/ADC_interface.h"

uint16 *ptr = &(ADC->ADCLH.ADCLH_REG);
uint8 *ptrL = &(ADC->ADCLH.ADCL);
uint8 *ptrH = &(ADC->ADCLH.ADCH);
uint8 *ptrMUX = &(ADC->ADMUX.ADMUX_REG);
uint8 *ptrCSRA = &(ADC->ADCSRA.ADCSRA_REG);

LCD_t LCD2;
uint16 data;
void ADC_ISR(void){
	data = ADC->ADCLH.ADCLH_REG;
			LCD_Send_Number_Pos(&LCD2, data, LCD_FIRST_ROW, 1);

}

int main(void){

	LCD2.mode = LCD_4BIT;
	LCD2.Display_Mode = LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF;
	LCD2.Entry_Mode = LCD_ENTRY_MODE_INC_SHIFT_OFF;
	LCD2.RS_PIN.GPIOx = GPIOD;
	LCD2.RS_PIN.direction = GPIO_OUTPUT;
	LCD2.RS_PIN.pin = GPIO_PIN_3;
	LCD2.RS_PIN.default_state = GPIO_STATE_LOW;
	LCD2.RW_PIN.GPIOx = GPIOD;
	LCD2.RW_PIN.direction = GPIO_OUTPUT;
	LCD2.RW_PIN.pin = GPIO_PIN_4;
	LCD2.RW_PIN.default_state = GPIO_STATE_LOW;
	LCD2.EN_PIN.GPIOx = GPIOD;
	LCD2.EN_PIN.direction = GPIO_OUTPUT;
	LCD2.EN_PIN.pin = GPIO_PIN_5;
	LCD2.EN_PIN.default_state = GPIO_STATE_LOW;
	LCD2.D_PINS[0].GPIOx = GPIOD;
	LCD2.D_PINS[0].direction = GPIO_OUTPUT;
	LCD2.D_PINS[0].pin = GPIO_PIN_6;
	LCD2.D_PINS[0].default_state = GPIO_STATE_LOW;
	LCD2.D_PINS[1].GPIOx = GPIOD;
	LCD2.D_PINS[1].direction = GPIO_OUTPUT;
	LCD2.D_PINS[1].pin = GPIO_PIN_7;
	LCD2.D_PINS[1].default_state = GPIO_STATE_LOW;
	LCD2.D_PINS[2].GPIOx = GPIOB;
	LCD2.D_PINS[2].direction = GPIO_OUTPUT;
	LCD2.D_PINS[2].pin = GPIO_PIN_7;
	LCD2.D_PINS[2].default_state = GPIO_STATE_LOW;
	LCD2.D_PINS[3].GPIOx = GPIOB;
	LCD2.D_PINS[3].direction = GPIO_OUTPUT;
	LCD2.D_PINS[3].pin = GPIO_PIN_6;
	LCD2.D_PINS[3].default_state = GPIO_STATE_LOW;
	LCD_Init(&LCD2);
//	LCD_Send_String(&LCD2, (uint8*)"Direction: ");

	ADC_cfg myADC = {.reference_voltage = ADC_REFERENCE_AREF, .prescaler = ADC_PRESCALE_64, .data_adjust = ADC_ADJUST_RIGHT,
			.interrupt_status = ADC_INTERRUPT_ENABLE, .pf_callback = ADC_ISR};
	ADC_Init(&myADC);

	while(1){
		ADC_Start_Conversion(ADC_PIN_0, &data, pollingDisable);
		_delay_ms(750);
					LCD_Send_Command(&LCD2, LCD_CLEAR_DISPLAY);
	}
	return 0;
}

