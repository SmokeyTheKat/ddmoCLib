#include <ddcString.h>
#include <ddcDef.h>
#include "ddcPrint.h"

#if __x86_64__
#define __TEST__ "64"
#else
#define __TEST__ "32"
#endif

int main(void)
{
	ddString ds = nddString("omg");
	dsPrintL(ds);
	return 0;
}
