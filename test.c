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
	ddPrint_int(69);
	ddPrint_nl();
	ddPrint_int(-69);
	ddPrint_nl();
	return 0;
}
