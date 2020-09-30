#include <ddcDef.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include "ddcHolder.h"

int main(void)
{
	holder h = make_holder(5);

	ddString ds = make_ddString("OMG");

	hpush(h, int, 5);
	hpush(h, bool, true);
	hpush(h, ddString, ds);
	
	if (hget(h, 1, int) == true)
	{
		dsPrintL((hget(h, 2, ddString)));
	}
	raze_ddString(&hget(h, 2, ddString));
	raze_holder(&h);
	return 0;
}
