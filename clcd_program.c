/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Mahmoud Radwan       ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : LCD                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/
#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "clcd_config.h"
#include "clcd_interface.h"
#include "clcd_private.h"
#include "CLCD_ExtraCahr.h"
/***************************************************************************************/
/* Description : Interface to send the configuration commands to the LCD Driver         */
/* Input       : Command number                                                         */
/* Output      : Nothing                                                                */
/***************************************************************************************/

 void CLCD_voidSendCommand(u8 copy_u8command){


	  /* set RS pin to low to send command */
	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_RS_PIN, DIO_U8PIN_LOW );

	  /* set R/W pin to low to write command */
	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_RW_PIN,  DIO_U8PIN_LOW);

	  /* send command through data port */
	  DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8command);


	  /* set Enable PIN for period of time */
	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_E_PIN,DIO_U8PIN_HIGH);
	  _delay_ms(2);
	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_E_PIN,DIO_U8PIN_LOW);

  }

  void CLCD_voidSendData(u8 copy_u8data){

	  /* set RS pin to high to send data */
	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_RS_PIN, DIO_U8PIN_HIGH );

	  /* set R/W pin to low to write data */
	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_RW_PIN,  DIO_U8PIN_LOW);

	  /* send data to data port */
	  DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8data);


	  /* set Enable PIN for period of time  */
	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_E_PIN,DIO_U8PIN_HIGH);
	  _delay_ms(2);
	  DIO_u8SetPinValue( CLCD_CONTRL_PORT,CLCD_E_PIN,DIO_U8PIN_LOW);

  }


  /***************************************************************************************/
  /* Description : Apply initialization sequence for LCD module                           */
  /* Input       : Nothing                                                                */
  /* Output      : Nothing                                                                */
  /***************************************************************************************/

  void CLCD_VoidINIT(void)
  {
  	/* Delay 30ms to ensure the initialization of the LCD driver */
  	_delay_ms(30);

  	/* Return Home  */
  	CLCD_voidSendCommand(lcd_Home);
  	_delay_ms(15);

  	/* Function Set  */
  	/* function send command : n 2 lines (1) , font size 5*8 (0) from data sheet */
  	CLCD_voidSendCommand(lcd_FunctionSet8bit);
  	_delay_ms(1);

  	/* Display ON OFF Control */
  	  /* function send command : display on/off control 00001DCB
  	   * D : display screen enable 1
  	   * C : cursor enable 1
  	   * B : cursor blink enable 1
  	   *  */
  	CLCD_voidSendCommand(lcd_DisplayOn);
  	_delay_ms(1);

  	/* Clear Display */
  	CLCD_voidSendCommand(lcd_Clear);
  	_delay_ms(15);

  	/* Entry Mode Set  */
  	CLCD_voidSendCommand(lcd_EntryMode);
  	_delay_ms(2);

  }

  /***************************************************************************************/
  /* Description! Interface to write character on LCD screen                             */
  /* Input      ! Data to send                                                           */
  /* Output     ! Nothing                                                                */
  /***************************************************************************************/
  void CLCD_vidWriteChar(u8 u8DataCpy)
  {
  	/* Set RS to HIG */
	  DIO_u8SetPinValue(CLCD_CONTRL_PORT, CLCD_RS_PIN, DIO_U8PIN_HIGH);

  	/* Set R/W to LOW */
	  DIO_u8SetPinValue(CLCD_CONTRL_PORT, CLCD_RW_PIN, DIO_U8PIN_LOW);

  	/* Set E to HIGH */
	  DIO_u8SetPinValue(CLCD_CONTRL_PORT, CLCD_E_PIN, DIO_U8PIN_HIGH);

  	/* Load Command on Data bus */
	  DIO_u8SetPortValue(CLCD_DATA_PORT, u8DataCpy);

  	/* Set E to LOW */
	  DIO_u8SetPinValue(CLCD_CONTRL_PORT, CLCD_E_PIN, DIO_U8PIN_LOW);

  	/* Wait for E to settle */
  	_delay_ms(5);

  	/* Set E to HIGH */
  	DIO_u8SetPinValue(CLCD_CONTRL_PORT, CLCD_E_PIN, DIO_U8PIN_HIGH);

  	/* Delay to let the LCD Display the character */
  	_delay_ms(10);

  }

  /***************************************************************************************/
  /* Description : Interface to write string on LCD screen                                */
  /* Input       : Pointer to the string                                                  */
  /* Output      : Nothing                                                                */
  /***************************************************************************************/
  void LCD_vidWriteString (u8* pu8StringCpy, u8 u8Index)
  {

      /* Local loop index */
	  //    u8 u8Index = 0;
  	u8 iteration=0;
  	//	while (pu8StringCpy[u8Index] != '\0')
  	for (iteration=0; iteration<u8Index ; iteration++)
  	{

  		/* Write Character on LCD */
  		CLCD_vidWriteChar(pu8StringCpy[iteration]);

  		/* Increment local loop index */
  		//  		u8Index++;

  		/* Delay to let the LCD show the character */
  		_delay_ms(2);
  	}

  }

  /***************************************************************************************/
  /* Description : Interface to start the writing process at certain digit in the LCD     */
  /* Input       : Y = Row position , X = Column position                                 */
  /* Output      : Nothing                                                                */
  /***************************************************************************************/
  void Gotoxy (u8 Y,u8 X)
  {
  	if (X>0 && X<=16)
  	{
  	    switch(Y)
  	    {
  		    case 1:
  		    	CLCD_voidSendCommand(X+127);
  		    break;
  		    case 2:
  		    	CLCD_voidSendCommand(X+191);
  		    break;
  		    default:
  		    break;
  	    }
  	}
  }

  /***************************************************************************************/
  /* Description : Interface to write extra characters saved in the CGRAM                 */
  /* Input       : Y = Row position , X = Column position                                 */
  /* Output      : Nothing                                                                */
  /***************************************************************************************/
  void LCD_vidWriteExtraChar (u8 Y,u8 X)
  {
      u8 iteration1,iteration2;

      /*DDRAM-->CGRAM*/

      CLCD_voidSendCommand(64);

  	for(iteration1=0 ; iteration1<64 ; iteration1++)
  	{
  		CLCD_vidWriteChar(ExtraChar[iteration1]);
  	}

  	/* CGRAM --> DDRAM */

  	CLCD_voidSendCommand(128);

  	Gotoxy(Y,X);

  	/* First eight character which saved at CGRAM */

  	for (iteration2=0; iteration2<=7 ; iteration2++)
  	{
  		/* Write bytes of DDRAM */
  		CLCD_vidWriteChar(iteration2);

  		_delay_ms(5);
  	}
  }
