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

	ddText dt = make_ddText(make_ddString("yo"),
				make_ddVec2(2, 2),
				make_ddColor(0,0,255),
				make_ddColor(0,255,0));

	ddText vdt = make_ddText(make_ddString("omg"),
				 make_ddVec2(0, 0),
				 make_ddColor(0,0,0),
				 make_ddColor(255,255,0));

	ddText dsdt = make_ddText(make_ddString("yo"),
				 make_ddVec2(0, 0),
				 make_ddColor(0,0,0),
				 make_ddColor(255,0,0));

	ddPanel dp = make_ddPanel(make_ddVec2(90,10),
				  make_ddVec2(41,20),
				  vdt,
				  make_ddColor(255,255,0));
	ddPanel dsp = make_ddPanel(make_ddVec2(20,10),
					      make_ddVec2(31,20),
					      vdt,
					      make_ddColor(255,255,0));

	ddSelect ds = make_ddSelect(&dsp, 5, make_ddColor(0,0,255));

	ddSelect_addOption(&ds, dsdt);
	ddSelect_addOption(&ds, dsdt);
	ddSelect_addOption(&ds, dsdt);
	ddSelect_addOption(&ds, dsdt);



	draw_ddText(dt);
	draw_ddPanel(dp);
	draw_ddSelect(ds);

	cursor_moveTo(0,40);
	raze_ddText(&dt);
	raze_ddPanel(&dp);

	return 0;
}
