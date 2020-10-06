#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include "ddcMap.h"

MAINF__
{
	SET_DDARGS__;

	fltPrint(ddMap(0.02, 0, 1, 0, 10));
	chPrintL("");

	return 0;
}
