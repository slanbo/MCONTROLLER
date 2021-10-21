
#ifndef _GUI_H_
#define _GUI_H_

#ifdef __cplusplus
 extern "C" {
#endif

uint16_t LCD_BGR2RGB(uint16_t c);
void Gui_Circle(uint16_t X,uint16_t Y,uint16_t R,uint16_t fc); 
void Fill_Circle(uint16_t X,uint16_t Y,uint16_t R,uint16_t fc);
void Gui_DrawLine(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1,uint16_t Color); 
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void LCD_DrawFillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color); 
void Draw_Triangel(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void Fill_Triangel(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void Gui_box(uint16_t x, uint16_t y, uint16_t w, uint16_t h,uint16_t bc);
void Gui_box2(uint16_t x,uint16_t y,uint16_t w,uint16_t h, uint8_t mode);
void DisplayButtonDown(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void DisplayButtonUp(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);

void PutStringToLCD(uint8_t ix, uint8_t iy,  uint16_t fc, uint16_t bc, char* iString, uint8_t iLength, const uint8_t* fontRus, const uint8_t* fontEng, uint8_t fontSize, uint8_t gap);	 
	 
uint8_t PutChangedCharsToLCD(uint8_t ix, uint8_t iy, uint16_t fc, uint16_t bc, char* iString, uint8_t iLength, const uint8_t* fontRus, const uint8_t* fontEng, uint8_t fontSize, uint8_t gap);
	 
#ifdef __cplusplus
}
#endif
#endif