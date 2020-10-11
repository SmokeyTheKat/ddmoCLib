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
	SET_DDARGS__;
	if (daHasch(da, "yo"))
	{
		chPrintL("yo yo yo");
	}

	init_cursor();
	cursor_clear();

	//cursor_setBColorRGB(255, 255, 255);
	cursor_setFColorRGB(0, 0, 0);

	int inc = 3;

	for (int i = 0; i < 170; i += inc)
	{
		for (int j = 0; j < 170; j += inc)
		{
			for (int k = 0; k < 170; k += inc)
			{
				cursor_setFColorRGB((int)ddMap(i, 0, 170, 0, 255),
							(int)ddMap(j, 0, 170, 0, 255),
							(int)ddMap(k, 0, 170, 0, 255));
				//cursor_setBColorRGB((int)ddMap(k, 0, 170, 0, 255),
			//				(int)ddMap(i, 0, 170, 0, 255),
			//				(int)ddMap(j, 0, 170, 0, 255));
				chPrint(cset_block); 
			}
		}
	}

	//cursor_chWrite("YO");
	chPrintL("");

	return 0;
}
