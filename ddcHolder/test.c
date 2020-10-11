#include <ddcDef.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include "ddcHolder.h"

int main(void)
{
	ddHolder h = make_ddHolder(5);

	hpush(h, bool, true);
	hpush(h, int, true);

	return 0;
}



