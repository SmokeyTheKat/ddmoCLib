#include <ddcDef.h>
#include <ddcPrint.h>
#include "ddcString.h"


int main(void)
{
	ddString ds = make_ddString("YO");
	dsPrint(ds);
	raze_ddString(&ds);
	if (ds.status == deleted)
	{
		chPrintC(3, "OMG", " BRO");
	}
	return 0;
}
