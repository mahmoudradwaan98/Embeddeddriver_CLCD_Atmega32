/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Mahmoud Radwan       ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : LCD                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

/*  preprocessor file guard */



#ifndef  clcd_interface_H_

  #define  clcd_interface_H_
  
  
  void CLCD_voidSendCommand(u8 copy_u8command);
  
  void CLCD_voidSendData(u8 copy_u8data);
  
  void CLCD_VoidINIT(void);
  
  void CLCD_vidWriteChar(u8 u8DataCpy);

  void LCD_vidWriteString (u8* pu8StringCpy, u8 u8Index);

  void Gotoxy (u8 Y,u8 X);

  void LCD_vidWriteExtraChar (u8 Y,u8 X);


#endif
