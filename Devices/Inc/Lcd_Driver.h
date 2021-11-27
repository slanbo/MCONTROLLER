
#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
	 
#define LCD_X_SIZE	        130
#define LCD_Y_SIZE	        130

#define USE_HORIZONTAL  		1
#if USE_HORIZONTAL
#define X_MAX_PIXEL	        LCD_Y_SIZE
#define Y_MAX_PIXEL	        LCD_X_SIZE
#else
#define X_MAX_PIXEL	        LCD_X_SIZE
#define Y_MAX_PIXEL	        LCD_Y_SIZE
#endif
	//////////////////////////////////////////////////////////////////////////////////
	 

	#define RED  		0xf800    
	#define GREEN		0x07e0   
	#define BLUE 		0x001f   
	#define SBLUE 		0x251F    
	#define WHITE		0xffff    
	#define BLACK		0x0000    
	#define YELLOW		0xFFE0   
	#define GRAY0		0xEF7D   	
	#define GRAY1		0x8410    
	#define GRAY2		0x4208    


	/*#define LCD_CTRL   	  	GPIOA		
	#define LCD_LED        	GPIO_Pin_9  
	#define LCD_RS         	GPIO_Pin_10	
	#define LCD_CS        	LCD_CS_Pin 
	#define LCD_RST     	LCD_RESET_Pin*/	

	#define	LCD_CS_SET  	HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_SET)    
	#define	LCD_RS_SET  	HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_SET)      
	#define	LCD_RST_SET  	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port,LCD_RESET_Pin,GPIO_PIN_SET)    
	//#define	LCD_LED_SET  	LCD_CTRL->BSRR=LCD_LED   

	#define	LCD_CS_CLR  	HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_RESET)    
	#define	LCD_RS_CLR  	HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)      
	#define	LCD_RST_CLR  	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port,LCD_RESET_Pin,GPIO_PIN_RESET)    
	//#define	LCD_LED_CLR  	LCD_CTRL->BRR=LCD_LED 

	//#define LCD_DATAOUT(x) LCD_DATA->ODR=x; 
	//#define LCD_DATAIN     LCD_DATA->IDR;   
	 
	 

	#define LCD_WR_DATA(data){\
	LCD_RS_SET;\
	LCD_CS_CLR;\
	LCD_DATAOUT(data);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	LCD_CS_SET;\
	} 

	void Lcd_WriteIndex(uint8_t Index);
	void Lcd_WriteData(uint8_t Data);
	void Lcd_WriteReg(uint8_t Index, uint8_t Data);
	uint16_t Lcd_ReadReg(uint8_t LCD_Reg);
	void Lcd_Reset(void);
	void Lcd_Init(void);
	void Lcd_Clear(uint16_t Color);
	void Lcd_SetXY(uint16_t x, uint16_t y);
	void Gui_DrawPoint(uint16_t x, uint16_t y, uint16_t Data);
	unsigned int Lcd_ReadPoint(uint16_t x, uint16_t y);
	void Lcd_SetRegion(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end);
	void Lcd_SetRegion_(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);
void Lcd_WriteData_16Bit(uint16_t Data);

#ifdef __cplusplus
}
#endif

#endif
