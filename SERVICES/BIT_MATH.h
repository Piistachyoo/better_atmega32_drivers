/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : BIT_MATH.h                           				 */
/* Date          : Aug 19, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/
#ifndef SERVICES_BIT_MATH_H_
#define SERVICES_BIT_MATH_H_

#define SET_BIT(REG, PIN)		(REG |= (1U<<PIN))
#define CLR_BIT(REG, PIN)		(REG &= ~(1U<<PIN))
#define TOG_BIT(REG, PIN)		(REG ^= (1U<<PIN))
#define GET_BIT(REG, PIN)		((REG>>PIN) & 0x01)


#endif /* SERVICES_BIT_MATH_H_ */
