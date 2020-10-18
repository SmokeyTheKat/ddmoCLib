#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include <ddcVec.h>
#include "ddcCursor.h"
#include <ddcColors.h>
#include <ddcMap.h>
#include <ddcCharSets.h>

MAINF__
{

	init_cursor();
	cursor_clear();

	//cursor_setBColorRGB(255, 255, 255);
	cursor_setFGColorRGB(0, 0, 0);

	int inc = 3;

yo:

	for (int i = 0; i < 170; i += inc)
	{
		for (int j = 0; j < 170; j += inc)
		{
			for (int k = 0; k < 170; k += inc)
			{
				cursor_setFGColorRGB((int)ddMap(i, 0, 170, 0, 255),
							(int)ddMap(j, 0, 170, 0, 255),
							(int)ddMap(k, 0, 170, 0, 255));
				//cursor_setBColorRGB((int)ddMap(k, 0, 170, 0, 255),
			//				(int)ddMap(i, 0, 170, 0, 255),
			//				(int)ddMap(j, 0, 170, 0, 255));
				ddPrint_cstring(cset_block); 
				usleep(100);
			}
		}
	}
goto yo;
	for(;;);

	//cursor_chWrite("YO");
	ddPrint_nl();

	return 0;
}
