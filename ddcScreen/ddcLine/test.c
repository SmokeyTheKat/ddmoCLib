#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcTime.h>
#include <ddcDef.h>
#include <ddcArguments.h>
#include "ddcLine.h"
#include <ddcVec.h>
#include <stdio.h>
#include <ddcCharSets.h>

MAINF__
{
	SET_DDARGS__;
	if (daHasch(da, "yo"))
	{
		chPrintL("yo yo yo");
	}
	init_cursor();
	cursor_clear();

	draw_line(make_ddLine(make_ddVec2(5, 2), make_ddVec2(53, 4)), cset_block);

/*

	ddVec2 p1 = make_ddVec2(8,2);
	ddVec2 p2 = make_ddVec2(82,33);

	draw_line(make_ddLine(p1, p2), cset_block);

	ddVec2 p1 = make_ddVec2(0,0);
	ddVec2 p2 = make_ddVec2(70,35);

	ddsize len = 1000;
	double* times = make(double, len);
	for (ddsize i = 0; i < len; i++)
	{
		ddTimerStart();
		draw_line(make_ddLine(p1, p2), cset_block);
		times[i] = ddTimerStop();
	}

	double total = 0;
	for (ddsize i = 0; i < len; i++)
	{
		total += times[i];
	}

	printf("%f", total/len);

	chPrintL("");

	raze(times);






	for (int i = 0; i < 79; i++)
	{
		for (int j = 0; j < 38; j++)
		{
			p1 = make_ddVec2(i, j);
			draw_line(make_ddLine(p1, p2), cset_block);
			draw_line(make_ddLine(p2, p3), cset_block);
			draw_line(make_ddLine(p3, p1), cset_block);
			usleep(10000);
			cursor_clear();
		}
	}

	



	for (int i = 0; i < 40; i++)
	{
		draw_lineO2(make_ddLine(make_ddVec2(0, 0), make_ddVec2(170, i)), cset_block);
		usleep(100000);
		draw_lineO2(make_ddLine(make_ddVec2(0, 0), make_ddVec2(170, i)), " ");
		if (i == 39)
		{
			for (int j = 170; j >= 0; j--)
			{
				draw_lineO2(make_ddLine(make_ddVec2(0, 0), make_ddVec2(j, 39)), cset_block);
				usleep(100000);
				draw_lineO2(make_ddLine(make_ddVec2(0, 0), make_ddVec2(j, 39)), " ");
				if (j == 2)
				{
					for (int k = 0; k < 170; k++)
					{
						draw_lineO2(make_ddLine(make_ddVec2(k, 0), make_ddVec2(0, 39)), cset_block);
						usleep(100000);
						draw_lineO2(make_ddLine(make_ddVec2(k, 0), make_ddVec2(0, 39)), " ");
					}
				}
			}
			i = 1;

		}
	}

*/

	cursor_moveTo(0, 40);

	return 0;
}
