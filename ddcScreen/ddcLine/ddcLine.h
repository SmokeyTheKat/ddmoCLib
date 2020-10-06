#ifndef __ddcLine__
#define __ddcLine__

#include <ddcCursor.h>
#include <ddcString.h>
#include <ddcMath.h>
#include <ddcVec.h>
#include <ddcPrint.h>
#include <ddcCharSets.h>

#include <time.h>

typedef struct ddLine ddLine;

struct ddLine
{
	ddVec2 p1;
	ddVec2 p2;
	float slope;
	float constant;
};
ddLine make_ddLine(ddVec2 _p1, ddVec2 _p2)
{
	ddLine dl;
	dl.p1 = _p1;
	dl.p2 = _p2;
	dl.slope = ((_p2.y - _p1.y) / (_p2.x - _p1.x));
	dl.constant = (_p1.y - (dl.slope * _p1.x));
	return dl;
}



void draw_linePoints(ddVec2 p1, ddVec2 p2);
void draw_line(ddLine dl);


float get_dist(ddVec2 a, ddVec2 b)
{
	float o = b.y - a.y;
	float p = b.x - a.x;
	return (float)(sqrt(pow(o,2)+pow(p,2)));
}


void draw_linePoints(ddVec2 p1, ddVec2 p2)
{
	draw_line(make_ddLine(p1, p2));
}
void draw_line(ddLine dl)
{


	ddVec2 p = make_ddVec2(dl.p1.x, dl.p1.y);



	/*
	 * start you code
	 * point1 = "dl.p1"
	 * point1 = "dl.p1"
	 * point2 = "dl.p2"
	 * to get y or x do "dl.p1.x" or "dl.p2.y"
	 * p is the cursor or the current position
	 * p is initizalized as the first point (dl.p1.x, dl.p2.y)
	 *
	 * to draw:
	 * cursor_moveTo(p.x, p.y);
	 * cursor_chWrite(cset_block);
	 *
	 *
	 * to test, exit and type:
	 * gcc test.c -o test
	 * ./test
	 *
	 *
	 *
	 *
	 */

/*
	//int dx = dl.p2.x-dl.p1.x/ddabs(dl.p2.x-dl.p1.x);
	//int dy = dl.p2.y-dl.p1.y/ddabs(dl.p2.y-dl.p1.y);
	int dx = (dl.p1.x <= dl.p2.x) ? 1 : -1;
	int dy = (dl.p1.y <= dl.p2.y) ? 1 : -1;
	int brx;
	int bry;
	if (dx == 1)
		brx = dl.p2.x;
	else
		brx = dl.p1.x;
	if (dy == 1)
		bry = dl.p2.y;
	else
		bry = dl.p1.y;
	int cx = 1;
	int cy = 1;
	while(p.x < dl.p2.x || p.y < dl.p2.y)
	//while(!v2cmp(p, dl.p2))
	{
		float rx = cx/brx;
		float ry = cy/bry;
		if (rx < ry)
		{
			cx++;
			p.x += dx;
		}
		else if (ry < rx)
		{
			cy++;
			p.y += dy;
		}
		else if (rx == ry)
		{
			if (1/brx < 1/bry)
			{
				cx++;
				p.x += dx;
			}
			else
			{
				cy++;
				p.y += dy;
			}
		}
		intPrint(cx);
		//cursor_moveTo(p.x, p.y);
		//cursor_chWrite(cset_block);
	}
*/

}


#endif
