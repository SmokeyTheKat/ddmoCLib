#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include <ddcVec.h>
#include "ddcCursor.h"

MAINF__
{
	SET_DDARGS__;
	if (daHasch(da, "yo"))
	{
		chPrintL("yo yo yo");
	}

	init_cursor();
	cursor_clear();

	cursor_chWrite("YO");

	return 0;
}
