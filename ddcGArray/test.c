#include <ddcDef.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include "ddcGArray.h"

int main(void)
{
	ddGArray h = make_ddGArray(5);


	int i = 5;
	bool b = true;


	dga_push(&h, i, int);
	dga_push(&h, b, bool);

	if (dga_get(h, 1, bool))
		intPrint(dga_get(h, 0, int));

	chPrintL("");

	
	raze_ddGArray(&h);

	return 0;
}



