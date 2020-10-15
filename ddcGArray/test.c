#include <ddcDef.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include "ddcGArray.h"

int main(void)
{
	ddGArray h = make_ddGArray(5);


	int i = 5;
	bool b = true;

	dga_push(&h, b);
	dga_push(&h, i);
	i = 4;
	chPrintL("");

	if (dga_get(h, 0, bool))
		intPrint(dga_get(h, 1, int));

	chPrintL("");
	chPrintL("");

	
	raze_ddGArray(&h);

	return 0;
}



