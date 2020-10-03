#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include "ddcLine.h"
#include <ddcVec.h>
#include <stdio.h>

MAINF__
{
	SET_DDARGS__;
	if (daHasch(da, "yo"))
	{
		chPrintL("yo yo yo");
	}
	init_cursor();
	cursor_clear();


	ddVec2 p1 = make_ddVec2(3,  3);
	ddVec2 p2 = make_ddVec2(30, 8);
	ddVec2 p3 = make_ddVec2(30, 20);
	ddVec2 p4 = make_ddVec2(3,  20);

	for(;;)
	{
		p1.x++;
		p2.x++;
		p3.x++;
		p4.x++;

		draw_linePoints(p1, p2);
		draw_linePoints(p2, p3);
		draw_linePoints(p3, p4);
		draw_linePoints(p4, p1);
		sleep(1);
		cursor_clear();
	}



	//draw_line(make_ddLine(make_ddVec2(0, 0), make_ddVec2(90, 30)));


	cursor_moveTo(0, 40);

	return 0;
}
