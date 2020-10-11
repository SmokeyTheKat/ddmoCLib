#ifndef __ddcShapes__
#define __ddcShapes__


#include <ddcVec.h>
#include <ddcCursor.h>
#include <ddcPrint.h>
#include <ddcMath.h>
#include <ddcMap.h>
#include <ddcCharSets.h>


typedef struct ddSquare ddSquare;

struct ddSquare
{
	ddVec2 position;
	ddVec2 size;
};

ddSquare make_ddSquare(ddVec2 _pos, ddVec2 _size);
ddSquare make_ddSquarePoints(ddVec2 _pos1, ddVec2 _pos2);
void draw_ddSquare(ddSquare _dsq, const char* _ch);
void drawOutline_ddSquare(ddSquare _dsq, const char* _ch);



ddSquare make_ddSquare(ddVec2 _pos, ddVec2 _size)
{
	ddSquare _o;
	_o.position = _pos;
	_o.size = _size;
	return _o;
}
ddSquare make_ddSquarePoints(ddVec2 _pos1, ddVec2 _pos2)
{
	ddSquare _o;
	_o.position = _pos1;
	_o.size = make_ddVec2(_pos2.x - _pos1.x, _pos2.y - _pos1.y);
	return _o;
}













void draw_ddSquare(ddSquare _dsq, const char* _ch)
{
	for (int i = 0; i < _dsq.size.y; i++)
	{
		cursor_moveTo(_dsq.position.x, _dsq.position.y+i);
		for (int j = 0; j < _dsq.size.x; j++)
		{
			cursor_chWrite(_ch);
		}
	}
}
void drawOutline_ddSquare(ddSquare _dsq, const char* _ch)
{
	cursor_moveTo(_dsq.position.x, _dsq.position.y);
	for (int i = 0; i < _dsq.size.x; i++)
		cursor_chWrite(_ch);

	cursor_moveTo(_dsq.position.x, _dsq.position.y);
	for (int i = 0; i < _dsq.size.y; i++)
	{
		cursor_chWrite(_ch);
		cursor_moveLeft();
		cursor_moveDown();
	}
	cursor_moveTo(_dsq.position.x+_dsq.size.x-1, _dsq.position.y);
	for (int i = 0; i < _dsq.size.y; i++)
	{
		cursor_chWrite(_ch);
		cursor_moveLeft();
		cursor_moveDown();
	}

	cursor_moveTo(_dsq.position.x, _dsq.position.y+_dsq.size.y-1);
	for (int i = 0; i < _dsq.size.x; i++)
		cursor_chWrite(_ch);
}




#endif
