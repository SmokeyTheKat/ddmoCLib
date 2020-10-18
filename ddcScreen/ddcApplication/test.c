#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include <ddcCursor.h>
#include "ddcApplication.h"

MAINF__
{
	init_cursor();
	cursor_clear();

	ddSelect ds1 = make_ddSelect(make_ddVec2(2,1),
					      make_ddVec2(30,20),
					      make_dft_ddText(make_constant_ddString("RED")),
					      make_ddColor(255,0,0), 5, make_ddColor(0,0,255));
	ddSelect ds2 = make_ddSelect(make_ddVec2(34,1),
					      make_ddVec2(30,20),
					      make_dft_ddText(make_constant_ddString("GREEN")),
					      make_ddColor(0,255,0), 5, make_ddColor(0,0,255));
	ddSelect ds3 = make_ddSelect(make_ddVec2(66,1),
					      make_ddVec2(30,20),
					      make_dft_ddText(make_constant_ddString("BLUE")),
					      make_ddColor(0,0,255), 5, make_ddColor(0,0,255));
	ddSelect ds4 = make_ddSelect(make_ddVec2(98,1),
					      make_ddVec2(30,20),
					      make_dft_ddText(make_constant_ddString("YELLOW")),
					      make_ddColor(255,255,0), 5, make_ddColor(0,0,255));
	ddSelect ds5 = make_ddSelect(make_ddVec2(130,1),
					      make_ddVec2(30,20),
					      make_dft_ddText(make_constant_ddString("AQUA")),
					      make_ddColor(0,255,255), 5, make_ddColor(0,0,255));

	ddSelect_addOption(&ds1, make_dft_ddText(make_ddString("pick me yo")));
	ddSelect_addOption(&ds1, make_dft_ddText(make_ddString("no pick me")));
	ddSelect_addOption(&ds1, make_dft_ddText(make_ddString("yo")));
	ddSelect_addOption(&ds1, make_dft_ddText(make_ddString("omg")));
	ddSelect_addOption(&ds1, make_dft_ddText(make_ddString("BAHAHAHA")));

	ddSelect_addOption(&ds2, make_dft_ddText(make_ddString("pick me yo")));
	ddSelect_addOption(&ds2, make_dft_ddText(make_ddString("no pick me")));
	ddSelect_addOption(&ds2, make_dft_ddText(make_ddString("yo")));
	ddSelect_addOption(&ds2, make_dft_ddText(make_ddString("omg")));
	ddSelect_addOption(&ds2, make_dft_ddText(make_ddString("BAHAHAHA")));

	ddSelect_addOption(&ds3, make_dft_ddText(make_ddString("pick me yo")));
	ddSelect_addOption(&ds3, make_dft_ddText(make_ddString("no pick me")));
	ddSelect_addOption(&ds3, make_dft_ddText(make_ddString("yo")));
	ddSelect_addOption(&ds3, make_dft_ddText(make_ddString("omg")));
	ddSelect_addOption(&ds3, make_dft_ddText(make_ddString("BAHAHAHA")));

	ddSelect_addOption(&ds4, make_dft_ddText(make_ddString("pick me yo")));
	ddSelect_addOption(&ds4, make_dft_ddText(make_ddString("no pick me")));
	ddSelect_addOption(&ds4, make_dft_ddText(make_ddString("yo")));
	ddSelect_addOption(&ds4, make_dft_ddText(make_ddString("omg")));
	ddSelect_addOption(&ds4, make_dft_ddText(make_ddString("BAHAHAHA")));

	ddSelect_addOption(&ds5, make_dft_ddText(make_ddString("pick me yo")));
	ddSelect_addOption(&ds5, make_dft_ddText(make_ddString("no pick me")));
	ddSelect_addOption(&ds5, make_dft_ddText(make_ddString("yo")));
	ddSelect_addOption(&ds5, make_dft_ddText(make_ddString("omg")));
	ddSelect_addOption(&ds5, make_dft_ddText(make_ddString("BAHAHAHA")));

	draw_ddSelect(ds1);
	draw_ddSelect(ds2);
	draw_ddSelect(ds3);
	draw_ddSelect(ds4);
	draw_ddSelect(ds5);

	cursor_moveTo(0,40);
	//raze_ddSelect(&ds1);
	//raze_ddSelect(&ds2);
	//raze_ddSelect(&ds3);
	//raze_ddSelect(&ds4);
	//raze_ddSelect(&ds5);

	return 0;
}
