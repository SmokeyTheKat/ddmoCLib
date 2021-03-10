#include "./ddcColors.h"
#include "./ddcString.h"
#include "./ddcPrint.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char** argv)
{
	struct color c = HSVtoRGB(0, 100, 100);
	for (int i = 0; i < 360; i++)
	{
		c = HSVtoRGB(i, 100, 100);
		ddPrintf("[%d, %d, %d]: \x1b[38;2;%d;%d;%dm#\n", (int)c.r, (int)c.g, (int)c.b, (int)c.r, (int)c.g, (int)c.b);

	}
	return 0;
}
