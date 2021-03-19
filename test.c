#include "./ddcDef.h"
#include "./ddcColors.h"
#include "./ddcString.h"
#include "./ddcPrint.h"
#include <stdio.h>
#include <string.h>
#include <math.h>



int main(int argc, char** argv)
{
	ddString a = make_ddString("ello :)\n");
	ddString_push_char_front(&a, 'H');
	ddPrints(a.cstr);
	return 0;
}
