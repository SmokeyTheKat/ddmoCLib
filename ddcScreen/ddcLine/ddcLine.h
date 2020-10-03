#ifndef __ddcLine__
#define __ddcLine__

#include <ddcCursor.h>
#include <ddcString.h>
#include <ddcMath.h>
#include <ddcVec.h>
#include <ddcPrint.h>

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



void draw_linePoints(ddVec2 p1, ddVec2 p2)
{
	draw_line(make_ddLine(p1, p2));
}
void draw_line(ddLine dl)
{
/*
	if (dl.p1.x > dl.p2.x)
	{
		ddVec2 t = dl.p1;
		dl.p1 = dl.p2;
		dl.p2 = t;
	}
*/

/*
	float p = (int)dl.p1.x;
	float inc = 0.1;
	cursor_moveTo(p, (int)dl.p1.y);
	for (p; p < (int)dl.p2.x; p += inc)
	{
		int mt = (int)((p*dl.slope)+dl.constant);
		cursor_moveTo(p, mt);
		cursor_chWrite("#");
	}
*/
	ddVec2 p = make_ddVec2(dl.p1.x, dl.p1.y);
	while(!v2cmp(p, dl.p2))
	{
		int dx = (dl.p2.x - p.x);
		int mdx;
		if (dx != 0)
			mdx = (dx / ddabs(dx));

		int dy = (dl.p2.y - p.y);
		int mdy;
		if (dy != 0)
			mdy = (dy / ddabs(dy));
		if ((ddabs(dx) / dl.p2.x) > (ddabs(dy) / dl.p2.y))
			p.x += mdx;
		else
			p.y += mdy;
		cursor_moveTo(p.x, p.y);
		cursor_chWrite("#");
	}


}


#endif
