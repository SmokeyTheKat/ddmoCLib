#include <ddcDef.h>
#include "ddcString.h"

int main(void)
{
	ddString ds = nddString("yo");
	printf(ds.cstr);
	dddString(&ds);
	return 0;
}
