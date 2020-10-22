#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include "ddcKeyboard.h"

MAINF__
{
	//ddPrint_int_nl(ddKey_getch());
	for(;;)ddKey_getch();

	return 0;
}
