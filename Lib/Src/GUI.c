
#include "Lcd_Driver.h"
#include "GUI.h"
#include "Font.h"
#include <locale.h>

//using namespace std;


uint16_t LCD_BGR2RGB(uint16_t c)
{
	uint16_t  r, g, b, rgb;   
	b = (c >> 0) & 0x1f;
	g = (c >> 5) & 0x3f;
	r = (c >> 11) & 0x1f;	 
	rgb = (b << 11) + (g << 5) + (r << 0);		 
	return (rgb);
}


static void _draw_circle_8(int xc, int yc, int x, int y, uint16_t c)
{
	Gui_DrawPoint(xc + x, yc + y, c);
	Gui_DrawPoint(xc - x, yc + y, c);
	Gui_DrawPoint(xc + x, yc - y, c);
	Gui_DrawPoint(xc - x, yc - y, c);
	Gui_DrawPoint(xc + y, yc + x, c);
	Gui_DrawPoint(xc - y, yc + x, c);
	Gui_DrawPoint(xc + y, yc - x, c);
	Gui_DrawPoint(xc - y, yc - x, c);
}


void Gui_Circle(uint16_t X, uint16_t Y, uint16_t R, uint16_t fc) 
{
	//BresenhamЛг·Ё 
    unsigned short  a, b; 
	int c; 
	a = 0; 
	b = R; 
	c = 3 - 2*R; 
	while (a < b) 
	{ 
		Gui_DrawPoint(X + a, Y + b, fc);      //        7 
		Gui_DrawPoint(X - a, Y + b, fc);      //        6 
		Gui_DrawPoint(X + a, Y - b, fc);      //        2 
		Gui_DrawPoint(X - a, Y - b, fc);      //        3 
		Gui_DrawPoint(X + b, Y + a, fc);      //        8 
		Gui_DrawPoint(X - b, Y + a, fc);      //        5 
		Gui_DrawPoint(X + b, Y - a, fc);      //        1 
		Gui_DrawPoint(X - b, Y - a, fc);      //        4 

		if(c < 0) c = c + 4*a + 6; 
		else 
		{ 
			c = c + 4*(a - b) + 10; 
			b -= 1; 
		} 
		a += 1; 
	} 
	if (a == b) 
	{ 
		Gui_DrawPoint(X + a, Y + b, fc); 
		Gui_DrawPoint(X + a, Y + b, fc); 
		Gui_DrawPoint(X + a, Y - b, fc); 
		Gui_DrawPoint(X - a, Y - b, fc); 
		Gui_DrawPoint(X + b, Y + a, fc); 
		Gui_DrawPoint(X - b, Y + a, fc); 
		Gui_DrawPoint(X + b, Y - a, fc); 
		Gui_DrawPoint(X - b, Y - a, fc); 
	} 
} 


void Fill_Circle(uint16_t X, uint16_t Y, uint16_t R, uint16_t fc)
{
	int x = 0, y = R, yi, d;
	d = 3 - 2 * R;
	while (x <= y) 
	{
		for (yi = x; yi <= y; yi++)
		{
			_draw_circle_8(X, Y, x, yi, fc);
		}
		if (d < 0) 
		{
			d = d + 4 * x + 6;
		}
		else 
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}


void Gui_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t Color)   
{
	int dx,              // difference in x's
    dy,              // difference in y's
    dx2,             // dx,dy * 2
    dy2, 
    x_inc,           // amount in pixel space to move during drawing
    y_inc,           // amount in pixel space to move during drawing
    error,           // the discriminant i.e. error i.e. decision variable
    index;           // used for looping	


	Lcd_SetXY(x0, y0);
	dx = x1 - x0;
	dy = y1 - y0;

	if (dx >= 0)
	{
		x_inc = 1;
	}
	else
	{
		x_inc = -1;
		dx    = -dx;  
	} 
	
	if (dy >= 0)
	{
		y_inc = 1;
	} 
	else
	{
		y_inc = -1;
		dy    = -dy; 
	} 

	dx2 = dx << 1;
	dy2 = dy << 1;

	if (dx > dy)
	{
		// initialize error term
		error = dy2 - dx; 

		// draw the line
		for(index = 0 ; index <= dx ; index++)
		{
			//»­µг
			Gui_DrawPoint(x0, y0, Color);
			
			// test if error has overflowed
			if(error >= 0) 
			{
				error -= dx2;

				// move to next line
				y0 += y_inc;
			} // end if error overflowed

			// adjust the error term
			error += dy2;

			// move to the next pixel
			x0 += x_inc;
		} // end for
	} // end if |slope| <= 1
	else
	{
		// initialize error term
		error = dx2 - dy; 

		// draw the line
		for(index = 0 ; index <= dy ; index++)
		{
			// set the pixel
			Gui_DrawPoint(x0, y0, Color);

			// test if error overflowed
			if(error >= 0)
			{
				error -= dy2;

				// move to next line
				x0 += x_inc;
			} // end if error overflowed

			// adjust the error term
			error += dx2;

			// move to the next pixel
			y0 += y_inc;
		} // end for
	} // end else |slope| > 1
}


void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	Gui_DrawLine(x1, y1, x2, y1, color);
	Gui_DrawLine(x1, y1, x1, y2, color);
	Gui_DrawLine(x1, y2, x2, y2, color);
	Gui_DrawLine(x2, y1, x2, y2, color);
}  


void LCD_DrawFillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	uint16_t i, j;			
	uint16_t width = x2 - x1 + 1; 		
	uint16_t height = y2 - y1 + 1;		
	Lcd_SetRegion(x1, y1, x2, y2);
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			Lcd_WriteData_16Bit(color);
		}   
	}
}


void Draw_Triangel(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	Gui_DrawLine(x0, y0, x1, y1, color);
	Gui_DrawLine(x1, y1, x2, y2, color);
	Gui_DrawLine(x2, y2, x0, y0, color);
}

static void _swap(uint16_t *a, uint16_t *b)
{
	uint16_t tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}


void Fill_Triangel(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	uint16_t a, b, y, last;
	int dx01, dy01, dx02, dy02, dx12, dy12;
	long sa = 0;
	long sb = 0;
	if (y0 > y1) 
	{
		_swap(&y0, &y1); 
		_swap(&x0, &x1);
	}
	if (y1 > y2) 
	{
		_swap(&y2, &y1); 
		_swap(&x2, &x1);
	}
	if (y0 > y1) 
	{
		_swap(&y0, &y1); 
		_swap(&x0, &x1);
	}
	if (y0 == y2) 
	{ 
		a = b = x0;
		if (x1 < a)
		{
			a = x1;
		}
		else if (x1 > b)
		{
			b = x1;
		}
		if (x2 < a)
		{
			a = x2;
		}
		else if (x2 > b)
		{
			b = x2;
		}
		LCD_DrawFillRectangle(a, y0, b, y0, color);
		return;
	}
	dx01 = x1 - x0;
	dy01 = y1 - y0;
	dx02 = x2 - x0;
	dy02 = y2 - y0;
	dx12 = x2 - x1;
	dy12 = y2 - y1;
	
	if (y1 == y2)
	{
		last = y1; 
	}
	else
	{
		last = y1 - 1; 
	}
	for (y = y0; y <= last; y++) 
	{
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;
		if (a > b)
		{
			_swap(&a, &b);
		}
		LCD_DrawFillRectangle(a, y, b, y, color);
	}
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for (; y <= y2; y++) 
	{
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if (a > b)
		{
			_swap(&a, &b);
		}
		LCD_DrawFillRectangle(a, y, b, y, color);
	}
}


void Gui_box(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t bc)
{
	Gui_DrawLine(x, y, x + w, y, 0xEF7D);
	Gui_DrawLine(x + w - 1, y + 1, x + w - 1, y + 1 + h, 0x2965);
	Gui_DrawLine(x, y + h, x + w, y + h, 0x2965);
	Gui_DrawLine(x, y, x, y + h, 0xEF7D);
	Gui_DrawLine(x + 1, y + 1, x + 1 + w - 2, y + 1 + h - 2, bc);
}


void Gui_box2(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t mode)
{
	if (mode == 0) {
		Gui_DrawLine(x, y, x + w, y, 0xEF7D);
		Gui_DrawLine(x + w - 1, y + 1, x + w - 1, y + 1 + h, 0x2965);
		Gui_DrawLine(x, y + h, x + w, y + h, 0x2965);
		Gui_DrawLine(x, y, x, y + h, 0xEF7D);
	}
	if (mode == 1) {
		Gui_DrawLine(x, y, x + w, y, 0x2965);
		Gui_DrawLine(x + w - 1, y + 1, x + w - 1, y + 1 + h, 0xEF7D);
		Gui_DrawLine(x, y + h, x + w, y + h, 0xEF7D);
		Gui_DrawLine(x, y, x, y + h, 0x2965);
	}
	if (mode == 2) {
		Gui_DrawLine(x, y, x + w, y, 0xffff);
		Gui_DrawLine(x + w - 1, y + 1, x + w - 1, y + 1 + h, 0xffff);
		Gui_DrawLine(x, y + h, x + w, y + h, 0xffff);
		Gui_DrawLine(x, y, x, y + h, 0xffff);
	}
}


void DisplayButtonDown(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	Gui_DrawLine(x1, y1, x2, y1, GRAY2);   //H
	Gui_DrawLine(x1 + 1, y1 + 1, x2, y1 + 1, GRAY1);   //H
	Gui_DrawLine(x1, y1, x1, y2, GRAY2);   //V
	Gui_DrawLine(x1 + 1, y1 + 1, x1 + 1, y2, GRAY1);   //V
	Gui_DrawLine(x1, y2, x2, y2, WHITE);   //H
	Gui_DrawLine(x2, y1, x2, y2, WHITE);   //V
}


void DisplayButtonUp(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	Gui_DrawLine(x1, y1, x2, y1, WHITE);  //H
	Gui_DrawLine(x1, y1, x1, y2, WHITE);  //V
	
	Gui_DrawLine(x1 + 1, y2 - 1, x2, y2 - 1, GRAY1);   //H
	Gui_DrawLine(x1, y2, x2, y2, GRAY2);   //H
	Gui_DrawLine(x2 - 1, y1 + 1, x2 - 1, y2, GRAY1);   //V
    Gui_DrawLine(x2, y1, x2, y2, GRAY2);  //V
}


void PutStringToLCD(uint8_t ix, uint8_t iy,  uint16_t fc, uint16_t bc, char* iString, uint8_t iLength, const uint8_t* fontRus, const uint8_t* fontEng, uint8_t fontSize, uint8_t gap)
{
	iLength--;
    uint8_t xpos = ix;
    for(int sym = 0; sym<iLength; ++sym)
    {
        uint8_t sm = iString[sym];
        uint8_t snum = (sm<0xC0 ? sm - 0x20 : sm - 0xC0);
        const uint8_t* symbol = &(sm < 0xC0 ? fontEng:fontRus)[(1 + fontSize * 2)*(snum)];
        for(uint8_t x = 0; x < symbol[0]; ++x)
        {
            for(uint8_t y = 0; y < fontSize; ++y)
            {
                if(symbol[1 + y / 8 + x * 2] & (0x01<<(y % 8)))
					Gui_DrawPoint(xpos + x, iy + y, fc);
                else
					Gui_DrawPoint(xpos + x, iy + y, bc);
            }
        }
        xpos += symbol[0]+gap;
    }
}

uint8_t PutChangedCharsToLCD(uint8_t ix, uint8_t iy, uint16_t fc, uint16_t bc, char* iString, uint8_t iLength, const uint8_t* fontRus, const uint8_t* fontEng, uint8_t fontSize, uint8_t gap)
{
	iLength--;
    uint8_t xpos = ix;
	uint8_t foundChanged = 0; 
	uint8_t endxpos = ix;
	
	for (int sym = 0; sym < iLength; ++sym)
    {
	    if (iString[sym] == 0)
	    {
		    continue;
	    }
		uint8_t sm = iString[sym];
		uint8_t snum = (sm < 0xC0 ? sm - 0x20 : sm - 0xC0);
		const uint8_t* symbol = &(sm < 0xC0 ? fontEng:fontRus)[(1 + fontSize * 2)*(snum)];
			for(uint8_t x = 0; x < symbol[0] + gap; ++x)
			{
				for(uint8_t y = 0; y < fontSize; ++y)
				{
					endxpos = xpos + x;
					uint16_t cc = bc;
					if (symbol[1 + y / 8 + x * 2] & (0x01 << (y % 8)))
					{
						cc = fc;
					}
					Gui_DrawPoint(endxpos, iy + y, cc);
				}
			}
        xpos += symbol[0] + gap;
    }
	
	for(uint8_t x = 0; x < 3; ++x)
	{
		for(uint8_t y = 0; y < fontSize; ++y)
		{
			endxpos = xpos + x;
			Gui_DrawPoint(endxpos, iy + y, bc);
		}
	}
	return endxpos;
}




