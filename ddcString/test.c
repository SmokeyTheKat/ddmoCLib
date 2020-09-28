#include <ddcDef.h>
#include <ddcPrint.h>
#include "ddcString.h"

int main(void)
{
	ddString ds = dsmul("#    ", 10);
	dsPrintL(ds);
	raze_ddString(&ds);
	return 0;
}
