#include "./ddcArgs.h"
#include "./ddcCharSets.h"
#include "./ddcPrint.h"
#include "./ddcGArray.h"
#include "./ddcMem.h"
#include "./ddcString.h"
#include "./ddcVec.h"
#include "./ddcBits.h"
#include "./ddcNLoops.h"
#include "./ddcTime.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	pArgs args = init_pArgs(argc, argv);
	cursor_clear();
	cursor_home();
	gArray arr = make_gArray(10);
	int a = 4;
	ddString d = make_ddString("HELLO");
	ddString_push_cstring_back(&d, " bro\n");
	gArray_push(&arr, d);
	gArray_push(&arr, a);
	ddPrint_int(gArray_pop(&arr, int));
	ddPrints(gArray_pop(&arr, ddString).cstr);
	ddPrint_nl();
	return 0;
}
