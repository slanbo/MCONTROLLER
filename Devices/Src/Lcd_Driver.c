//#include "stm32f10x.h"
#include "Lcd_Driver.h"
//#include "delay.h"
#include "spi.h"
#include "tim.h"
#include "Auxiliary.h"


void Lcd_WriteIndex(uint8_t Index)
{
   LCD_CS_CLR;
   LCD_RS_CLR; 
   HAL_SPI_Transmit(&hspi1, &Index, 1, 5000);
   LCD_CS_SET;
}


void Lcd_WriteData(uint8_t Data)
{
   LCD_CS_CLR;
   LCD_RS_SET; 
	HAL_SPI_Transmit(&hspi1, &Data, 1, 5000);
   LCD_CS_SET;
}


void LCD_WriteReg(uint8_t Index, uint16_t Data)
{
	Lcd_WriteIndex(Index);
	Lcd_WriteData_16Bit(Data);
}


void Lcd_WriteData_16Bit(uint16_t Data)
{	
	LCD_CS_CLR;
	LCD_RS_SET;
	uint8_t fByte = Data >> 8;
	uint8_t sByte = Data;
	HAL_SPI_Transmit(&hspi1, &fByte, 1, 5000);
	HAL_SPI_Transmit(&hspi1, &sByte, 1, 5000);
	//LCD_CS_SET;
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
    //US_DELAY(100);
}


void Write_WDR(uint8_t Index, uint16_t Data)
{
	Lcd_WriteIndex(Index);
	Lcd_WriteData_16Bit(Data);
	US_DELAY(1000);
}


void Lcd_Reset(void)
{
	LCD_RST_CLR;
	US_DELAY(100);
	LCD_RST_SET;
	US_DELAY(100);
	//LCD_RST_CLR;
	//US_DELAY(100);
}


void Lcd_Init(void)
{	
	Lcd_Reset(); //Reset before LCD Init.
	Write_WDR(0x10,0x2F8E); /* power control 1 */
	Write_WDR(0x11,0x000C); /* power control 2 */
	Write_WDR(0x07,0x0021); /* display control */
	Write_WDR(0x28,0x0006); /* vcom OTP */
	Write_WDR(0x28,0x0005);
	Write_WDR(0x27,0x057F); /* further bias current setting */
	Write_WDR(0x29,0x89A1); /* vcom OTP */
	Write_WDR(0x00,0x0001); /* OSC en */
	Write_WDR(0x29,0x80B0); /* vcom OTP */
	Write_WDR(0x29,0xFFFE); /* vcom OTP */
	Write_WDR(0x07,0x0023); /* display control */
	Write_WDR(0x07,0x0033); /* display control */
#if USE_HORIZONTAL
	Write_WDR(0x01,0x2283); /* driver output control, REV, TB=0, RL=1, RGB */
	Write_WDR(0x03,0x6838); /* entry mode, 65K, ram, ID3 */
#else
	Write_WDR(0x01,0x2183); /* driver output control, REV, TB, RGB */
	Write_WDR(0x03,0x6830); /* entry mode, 65K, ram, ID0 */
#endif
	Write_WDR(0x2F,0xFFFF); /* 2A ~ 2F, test */
	Write_WDR(0x2C,0x8000);
	Write_WDR(0x27,0x0570);
	Write_WDR(0x02,0x0300); /* driving wave form control */
	Write_WDR(0x0B,0x580C); /* frame cycle control */
	Write_WDR(0x12,0x0609); /* power control 3 */
	Write_WDR(0x13,0x3100); /* power control 4 */
}


void Lcd_SetXY(uint16_t Xpos, uint16_t Ypos)
{	
#if USE_HORIZONTAL
	Lcd_WriteIndex(0x21);
	Lcd_WriteData(Xpos);
	Lcd_WriteData(Ypos+2);	
#else
	Lcd_WriteIndex(0x21);
	Lcd_WriteData(Ypos+2);
	Lcd_WriteData(Xpos+2);	
#endif
	Lcd_WriteIndex(0x22);	

} 

void Lcd_SetRegion(uint8_t xStar, uint8_t yStar, uint8_t xEnd, uint8_t yEnd)
{
	
#if USE_HORIZONTAL
	Lcd_WriteIndex(0x45);
	Lcd_WriteData(xEnd);
	Lcd_WriteData(xStar);	
	
	Lcd_WriteIndex(0x44);
	Lcd_WriteData(yEnd+2);
	Lcd_WriteData(yStar+2);	
#else	
	Lcd_WriteIndex(0x44);
	Lcd_WriteData(xEnd+2);
	Lcd_WriteData(xStar+2);	
	
	Lcd_WriteIndex(0x45);
	Lcd_WriteData(yEnd+2);
	Lcd_WriteData(yStar+2);	
#endif
	Lcd_SetXY(xStar,yStar);
}

	

void Gui_DrawPoint(uint16_t x, uint16_t y, uint16_t Data)
{
	Lcd_SetXY(x,y);
	Lcd_WriteData_16Bit(Data);

}    


void Lcd_Clear(uint16_t Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	Lcd_WriteData_16Bit(Color);
    }   
}



