#ifndef APP_ALL_LCD_H
#define APP_ALL_LCD_H

#ifndef APP_ALL_LCD_C
#define APP_ALL_LCD_EXT extern
#else
#define APP_ALL_LCD_EXT
#endif





#define Turn_Light_On()          do{if(JUDGE_POWER_OFF EQ 0) LCD_BACK_LIGHT_1;}while(0)   //掉电下不开背光
#define Turn_Light_Off()         LCD_BACK_LIGHT_0




void	HTLCDWriteACommand(INT32U command);
void	HTLCD_WRITE_MODE(INT8U LCD_RAM_ADDR);
void	HTLCD_SEND_DATA(INT8U LCD_RAM_ADDR, INT8U *DATA_ADDR,INT32U DATA_LENGTH);
void    Init_LCD_Mode(INT32U Mode,INT8U Status);
void	LCDWriteMultiData(INT8U LCD_RAM_ADDR,INT8U *DATA_ADDR,INT32U	DATA_LENGTH);
void    InitHTLCDIOPort(void);
void    Init_LCD_Loop(void);
void    FillAllScreen(void);
void    ClearAllScreen(void);
void Test_Lcd_Proc(void);
#endif
