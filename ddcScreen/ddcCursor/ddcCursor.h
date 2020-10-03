#ifndef __ddcCursor__
#define __ddcCursor__

#include <ddcVec.h>
#include <ddcPrint.h>
#include <ddcMath.h>
#include <ddcString.h>

#define __CURSOR_STACK_LENGTH 10

const ddsize consoleWidth = 148;
const ddsize consoleHeight = 47;

ddVec2 cursorPosition;
static ddVec2 __v2empty;
static ddVec2 __cursorPositionStack[__CURSOR_STACK_LENGTH];

void init_cursor(void);
void cursor_moveTo(int x, int y);
void cursor_moveToVec(ddVec2 v);
void cursor_move(int x, int y);
void cursor_moveVec(ddVec2 v);
void cursor_moveUp(void);
void cursor_moveDown(void);
void cursor_moveLeft(void);
void cursor_moveRight(void);
void cursor_return(void);
void cursor_home(void);
void cursor_deleteLine(void);
bool cursor_pop(void);
bool cursor_push(void);
void cursor_chWrite(const char* ch);
void cursor_dsWrite(const ddString ds);
void cursor_chWriteLine(const char* ch);
void cursor_dsWriteLine(const ddString ds);
void cursor_clear(void);

#define cursor_dsWriteL cursor_dsWriteLine
#define cursor_chWriteL cursor_chWriteLine



void init_cursor(void)
{
	__v2empty = make_ddVec2(-1, -1);
	cursorPosition = make_ddVec2(0, 0);
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
		__cursorPositionStack[i] = make_ddVec2(-1, -1);
}


void cursor_moveTo(int x, int y)
{
	cursorPosition.x = x;
	cursorPosition.y = y;
	chPrint("\x1b[");
	intPrint(y);
	chPrint(";");
	intPrint(x);
	chPrint("H");
}
void cursor_moveToVec(ddVec2 v)
{
	cursor_moveTo(v.x, v.y);
}
void cursor_move(int x, int y)
{
	cursorPosition.x += x;
	cursorPosition.y += y;
	int dx = ddabs(x) / x;
	int dy = ddabs(y) / y;
	if (x != 0)
	{
		if (dx == -1)
		{
			chPrint("\x1b[");
			intPrint(ddabs(x));
			chPrint("N");
		}
		else
		{
			chPrint("\x1b[");
			intPrint(x);
			chPrint("C");

		}

	}
	if (y != 0)
	{
		if (dy == -1)
		{
			chPrint("\x1b[");
			intPrint(ddabs(y));
			chPrint("A");
		}
		else
		{
			chPrint("\x1b[");
			intPrint(y);
			chPrint("B");

		}

	}
}
void cursor_moveVec(ddVec2 v)
{
	cursor_move(v.x, v.y);
}
void cursor_moveUp(void)
{
	chPrint("\x1b[A");
	cursorPosition.y++;
}
void cursor_moveDown(void)
{
	chPrint("\x1b[B");
	cursorPosition.y--;
}
void cursor_moveLeft(void)
{
	chPrint("\x1b[D");
	cursorPosition.x--;
}
void cursor_moveRight(void)
{
	chPrint("\x1b[C");
	cursorPosition.x++;
}
void cursor_return(void)
{
	chPrint("\r");
	cursorPosition.x = 0;
}
void cursor_home(void)
{
	cursor_moveTo(0, 0);
}
void cursor_deleteLine(void)
{
	chPrint("\x1b[2K");
}
bool cursor_pop(void)
{
	for (int i = __CURSOR_STACK_LENGTH - 1; i >= 0; i--)
	{
		if (!v2cmp(__v2empty, __cursorPositionStack[i]))
		{
			v2set(&cursorPosition, __cursorPositionStack[i]);
			v2set(&__cursorPositionStack[i], __v2empty);
			cursor_moveToVec(cursorPosition);
			return true;
		}
	}
	return false;
}
bool cursor_push(void)
{
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
	{
		if (v2cmp(__v2empty, __cursorPositionStack[i]))
		{
			v2set(&__cursorPositionStack[i], cursorPosition);
			return true;
		}
	}
	return false;
}
void cursor_chWrite(const char* ch)
{
	ddsize _len;
	chlen(ch, &_len);
	__ddPrint(ch, _len);
	cursorPosition.x += _len;
}
void cursor_dsWrite(const ddString ds)
{
	dsPrint(ds);
	cursorPosition.x += ds.length;
}
void cursor_chWriteLine(const char* ch)
{
	ddsize _len;
	chlen(ch, &_len);
	__ddPrint(ch, _len);
	cPrint(dnl);
	cursorPosition.y++;
	cursorPosition.x = 0;
}
void cursor_dsWriteLine(const ddString ds)
{
	dsPrint(ds);
	cPrint(dnl);
	cursorPosition.y++;
	cursorPosition.x = 0;
}
void cursor_clear(void)
{
	cursor_moveTo(consoleWidth, consoleHeight);
	chPrint("\x1b[1J");
	chPrint("\x1b[0;0H");
	cursorPosition.x = 0;
	cursorPosition.y = 0;
}


#endif
