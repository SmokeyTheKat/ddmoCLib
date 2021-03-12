#include "./ddcDef.h"
#include "./ddcColors.h"
#include "./ddcX11Env.h"
#include "./ddcString.h"
#include "./ddcPrint.h"
#include <stdio.h>
#include <string.h>
#include <math.h>


float fun(float x, float vy, float s, float r)
{
	float vx = (s+r)/2;
	if ((vx-r) == 0 || (vx-s) == 0) return 0.0;
	float a = vy/((vx-r)*(vx-s));
	return a*(x-r)*(x-s);
}


void draw(void)
{
	int width = ddXE_get_width();
	int height = ddXE_get_height();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int r = (int)fun(rand()%(x+1), 255, 0, width);
			int g = (int)fun(rand()%(y+1), 255, 0, height);
			int b = (int)fun(rand()%(x+y+1), 255, 0, width+height);
			ddXE_set_color(g, b, r);
			ddXE_set_pixel(x, y);
		}
	}
	ddXE_draw_text(width/2, height/2, "hello", 5);
}
void keypress(char c)
{
	ddPrintf("%c\n", c);
}

int main(int argc, char** argv)
{
	bool running = true;
	ddXE_start(draw, keypress, &running);
	return 0;
}
