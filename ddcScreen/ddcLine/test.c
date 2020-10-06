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



	draw_line(make_ddLine(make_ddVec2(2, 8), make_ddVec2(9, 2)));

	cursor_moveTo(0, 40);

	return 0;
}
