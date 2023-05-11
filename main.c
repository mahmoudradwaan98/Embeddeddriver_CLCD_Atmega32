/*
 * main.c
 *
 *  Created on: Feb 28, 2023
 *      Author: User
 */
#include"STD_TYPES.h"


#include"DIO_interface.h"
#include"clcd_interface.h"


void main(){


	/* LCD pin init */

	DIO_u8SetPortDirection(DIO_U8PORTA,DIO_U8PORT_OUTPUT);

	DIO_u8SetPinDirection(DIO_U8PORTC,DIO_U8PIN0,DIO_U8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_U8PORTC,DIO_U8PIN1,DIO_U8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_U8PORTC,DIO_U8PIN2,DIO_U8PIN_OUTPUT);

	/* LCD datasheet init */

	CLCD_VoidINIT();

	CLCD_voidSendData('R');
	CLCD_voidSendData('A');
	CLCD_voidSendData('D');
	CLCD_voidSendData('W');
	CLCD_voidSendData('A');
	CLCD_voidSendData('N');




	while(1){


	}



}
