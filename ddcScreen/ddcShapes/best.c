#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include <ddcCharSets.h>
#include "ddcShapes.h"

MAINF__
{
	init_cursor();
	cursorBGColor = make_ddColor(200, 0, 200);
	cursor_clear();
	

	int gv = 255;
	cursor_setBColorRGB(255,255,0);
	ddSquare dsq = make_ddSquare(make_ddVec2(1, 1), make_ddVec2(8,4));
	draw_ddSquare(dsq, " ");

	sleep(2);

	cursor_setBColorRGB(255,0,0);
	dsq = make_ddSquare(make_ddVec2(9, 0), make_ddVec2(0,5));
	drawOutline_ddSquare(dsq, " ");

/*

	cursor_setBColorRGB(0,0,255);
	dsq = make_ddSquare(make_ddVec2(66, 11), make_ddVec2(8,3));
	drawOutline_ddSquare(dsq, " ");

*/



	for(;;);

	cursor_moveTo(0, 47);
	
	return 0;
}
