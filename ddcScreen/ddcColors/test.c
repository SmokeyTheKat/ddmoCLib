#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include "ddcColors.h"

MAINF__
{
	SET_DDARGS__;
	if (daHasch(da, "yo"))
	{
		chPrintL("yo yo yo");
	}

	ddFColor dfc = make_ddFColor(255, 255 ,0);
	ddBColor dbc = make_ddBColor(0, 0, 255);
	dsPrint(dfc.color);
	dsPrint(dbc.color);
	chPrint("YOYO\n");

	return 0;
}
