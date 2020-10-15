#ifndef __ddcShapes__
#define __ddcShapes__


#include <ddcVec.h>
#include <ddcCursor.h>
#include <ddcPrint.h>
#include <ddcMath.h>
#include <ddcMap.h>
#include <ddcCharSets.h>
#include <ddcLine.h>


typedef struct ddSquare ddSquare;

struct ddSquare
{
	ddVec2 position;
	ddVec2 size;
	char* chr;
};

ddSquare make_ddSquare(ddVec2 _pos, ddVec2 _size, const char* _ch);
ddSquare make_ddSquarePoints(ddVec2 _pos1, ddVec2 _pos2, const char* _ch);
void draw_ddSquare(ddSquare _dsq);
void drawOutline_ddSquare(ddSquare _dsq);



ddSquare make_ddSquare(ddVec2 _pos, ddVec2 _size, const char* _ch)
{
	ddSquare _o;
	_o.position = _pos;
	_o.size = _size;
	_o.chr = _ch;
	return _o;
}
ddSquare make_ddSquarePoints(ddVec2 _pos1, ddVec2 _pos2, const char* _ch)
{
	ddSquare _o;
	_o.position = _pos1;
	_o.size = make_ddVec2(_pos2.x - _pos1.x, _pos2.y - _pos1.y);
	_o.chr = _ch;
	return _o;
}













void draw_ddSquare(ddSquare _dsq)
{
	for (int i = 0; i < _dsq.size.y; i++)
	{
		cursor_moveTo(_dsq.position.x, _dsq.position.y+i);
		for (int j = 0; j < _dsq.size.x; j++)
		{
			cursor_chWrite(_dsq.chr);
		}
	}
}
void drawOutline_ddSquare(ddSquare _dsq)
{
	draw_linePoints(make_ddVec2(_dsq.position.x, _dsq.position.y),
			make_ddVec2(_dsq.position.x+_dsq.size.x-1, _dsq.position.y), _dsq.chr);
	draw_linePoints(make_ddVec2(_dsq.position.x, _dsq.position.y),
			make_ddVec2(_dsq.position.x, _dsq.position.y+_dsq.size.y-1), _dsq.chr);

	draw_linePoints(make_ddVec2(_dsq.position.x+_dsq.size.x-1, _dsq.position.y+_dsq.size.y-1),
			make_ddVec2(_dsq.position.x, _dsq.position.y+_dsq.size.y-1), _dsq.chr);
	draw_linePoints(make_ddVec2(_dsq.position.x+_dsq.size.x-1, _dsq.position.y+_dsq.size.y-1),
			make_ddVec2(_dsq.position.x+_dsq.size.x-1, _dsq.position.y), _dsq.chr);
}




#endif
