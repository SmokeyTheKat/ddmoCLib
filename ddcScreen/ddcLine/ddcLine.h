#ifndef __ddcLine__
#define __ddcLine__

#include <ddcCursor.h>
#include <ddcString.h>
#include <ddcMath.h>
#include <ddcVec.h>
#include <ddcPrint.h>
#include <ddcCharSets.h>

#include <stdio.h>

#include <time.h>

typedef struct ddLine ddLine;


void draw_linePoints(ddVec2 p1, ddVec2 p2, const char* ch);
void draw_line(ddLine dl, const char* ch);
ddLine make_ddLine(ddVec2 _p1, ddVec2 _p2);



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



void draw_linePoints(ddVec2 p1, ddVec2 p2, const char* ch)
{
	draw_line(make_ddLine(p1, p2), ch);
}


void draw_line(ddLine dl, const char* ch)
{
	const int ci[2]     = { ddabs(dl.p2.y-dl.p1.y), ddabs(dl.p2.x-dl.p1.x) };
	const int td        = ci[0]+ci[1];
	const int d[2]      = {(dl.p1.x <= dl.p2.x) ? 1 : -1, (dl.p1.y <= dl.p2.y) ? 1 : -1 };
	//int c[2]            = { ci[0], ci[1] };
	int c[2]            = { 0,0 };
	int po[2]           = { dl.p1.x, dl.p1.y };
	int i               = 0;
	cursor_moveTo(po[0], po[1]);
	cursor_chWrite(ch);
	switch (i < td)
	{
		case 1:
		{
			do
			{
				int v = (c[0]>c[1])+(c[0]==c[1]);
				c[v] += ci[v];
				po[v] += d[v];
				cursor_moveTo(po[0], po[1]);
				cursor_chWrite(ch);
				i++;
			} while (i < td);
		}
		case 0:	return;
	}
}


void draw_lineO(ddLine dl, const char* ch)
{
	ddVec2 p = make_ddVec2(dl.p1.x, dl.p1.y);

	int ndx = ddabs(dl.p2.x-dl.p1.x);
	int ndy = ddabs(dl.p2.y-dl.p1.y);

	int dx = (dl.p1.x <= dl.p2.x) ? 1 : -1;
	int dy = (dl.p1.y <= dl.p2.y) ? 1 : -1;

	int cxinc = ndy;
	int cyinc = ndx;

	int cx = cxinc;
	int cy = cyinc;

	cursor_moveTo(p.x, p.y);
	cursor_chWrite(ch);
	while(!v2cmp(p, dl.p2))
	{
		if (cx < cy)
		{
			cx+=cxinc;
			p.x += dx;
			cursor_moveToVec(p);
		}
		else if (cy < cx)
		{
			cy+=cyinc;
			p.y += dy;
			cursor_moveToVec(p);
		}
		else //if (cx == cy)
		{
			if (ndx <= ndy)
			{
				cx+=cxinc;
				p.x += dx;
				cursor_moveToVec(p);
			}
			else
			{
				cy+=cyinc;
				p.y += dy;
				cursor_moveToVec(p);
			}
		}
		cursor_chWrite(ch);
	}

}


void draw_lineO2(ddLine dl, const char* ch)
{
	int dx = dl.p2.x-dl.p1.x;
	int dy = dl.p2.y-dl.p1.y;
	int yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	int D = (2*dy) - dx;
	int y = dl.p1.y;

	for (int x = dl.p1.x; x < dl.p2.x; x++)
	{
		cursor_moveTo(x, y);
		cursor_chWrite(ch);
		int dd = (D > 0);
		y += yi*dd;
		D += (2*(dy-dx))*dd;
		D += (2*dy)*dd;
	}
}



#endif
