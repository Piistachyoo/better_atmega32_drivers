/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project       : ITI_AVR_Drivers                                    	 */
/* File          : STD_LIB.h                           					 */
/* Date          : Aug 19, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/
#ifndef SERVICES_STD_LIB_H_
#define SERVICES_STD_LIB_H_

typedef unsigned char 		uint8;
typedef unsigned short 		uint16;
typedef unsigned long 		uint32;
typedef unsigned long long 	uint64;


typedef signed char			sint8;
typedef signed short 		sint16;
typedef signed long 		sint32;
typedef signed long long 	sint64;

typedef enum{
	RET_OK = 0,
	RET_NOT_OK = 1
}Std_Returntype;

#ifndef NULL
#define NULL	0
#endif

typedef enum{
	pollingEnable,
	pollingDisable
}polling_t;

#endif /* SERVICES_STD_LIB_H_ */
