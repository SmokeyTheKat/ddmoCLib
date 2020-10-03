#include <ddcDef.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include "ddcHolder.h"

int main(void)
{
	holder h = make_holder(5);

	hpush(h, bool true);
	hpush(h, int, true);

	return 0;
}



