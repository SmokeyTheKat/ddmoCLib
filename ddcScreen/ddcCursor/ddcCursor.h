#ifndef __ddcCursor__
#define __ddcCursor__

#include <ddcVec.h>
#include <ddcPrint.h>
#include <ddcMath.h>
#include <ddcString.h>
#include <ddcColors.h>

#define __CURSOR_STACK_LENGTH 10

const ddsize g_consoleWidth = 170;
const ddsize g_consoleHeight = 47;

ddVec2 g_cursorPosition;
ddColor g_cursorFGColor;
ddColor g_cursorBGColor;

static ddVec2 __v2empty;
static ddVec2 __cursorPositionStack[__CURSOR_STACK_LENGTH];
static ddColor __cursorFGStack[__CURSOR_STACK_LENGTH];
static ddColor __cursorBGStack[__CURSOR_STACK_LENGTH];

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
void cursor_setFGColor(ddColor dc);
void cursor_setFGColorRGB(int r, int g, int b);
void cursor_setBGColor(ddColor dc);
void cursor_setBGColorRGB(int r, int g, int b);
bool cursor_colorPush(void);
bool cursor_colorPop(void);

#define cursor_dsWriteL cursor_dsWriteLine
#define cursor_chWriteL cursor_chWriteLine



void init_cursor(void)
{
	__v2empty = make_ddVec2(-1, -1);
	g_cursorBGColor = make_ddColor(0, 0, 0);
	g_cursorFGColor = make_ddColor(255, 255, 255);
	g_cursorPosition = make_ddVec2(0, 0);
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
		__cursorPositionStack[i] = make_ddVec2(-1, -1);
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
		__cursorFGStack[i] = make_ddColor(0,420,0);
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
		__cursorBGStack[i] = make_ddColor(0,420,0);
}


void cursor_moveTo(int x, int y)
{
	x++;
	y++;
	g_cursorPosition.x = x;
	g_cursorPosition.y = y;
	ddPrint_cstring("\x1b[");
	ddPrint_int(y);
	ddPrint_cstring(";");
	ddPrint_int(x);
	ddPrint_cstring("H");
}
void cursor_moveToVec(ddVec2 v)
{
	cursor_moveTo(v.x, v.y);
}
void cursor_move(int x, int y)
{
	g_cursorPosition.x += x;
	g_cursorPosition.y += y;
	int dx = (x >= 0) ? 1 : -1;
	int dy = (y >= 0) ? 1 : -1;
	if (x != 0)
	{
		if (dx == -1)
		{
			ddPrint_cstring("\x1b[");
			ddPrint_int(ddMath_abs(x));
			ddPrint_cstring("D");
		}
		else
		{
			ddPrint_cstring("\x1b[");
			ddPrint_int(x);
			ddPrint_cstring("C");

		}

	}
	if (y != 0)
	{
		if (dy == -1)
		{
			ddPrint_cstring("\x1b[");
			ddPrint_int(ddMath_abs(y));
			ddPrint_cstring("A");
		}
		else
		{
			ddPrint_cstring("\x1b[");
			ddPrint_int(y);
			ddPrint_cstring("B");

		}

	}
}
void cursor_moveVec(ddVec2 v)
{
	cursor_move(v.x, v.y);
}
void cursor_moveUp(void)
{
	ddPrint_cstring("\x1b[A");
	g_cursorPosition.y++;
}
void cursor_moveDown(void)
{
	ddPrint_cstring("\x1b[B");
	g_cursorPosition.y--;
}
void cursor_moveLeft(void)
{
	ddPrint_cstring("\x1b[D");
	g_cursorPosition.x--;
}
void cursor_moveRight(void)
{
	ddPrint_cstring("\x1b[C");
	g_cursorPosition.x++;
}
void cursor_return(void)
{
	ddPrint_cstring("\r");
	g_cursorPosition.x = 0;
}
void cursor_home(void)
{
	cursor_moveTo(0, 0);
}
void cursor_deleteLine(void)
{
	ddPrint_cstring("\x1b[2K");
}
bool cursor_pop(void)
{
	for (int i = __CURSOR_STACK_LENGTH - 1; i >= 0; i--)
	{
		if (!ddVec2_compare(__v2empty, __cursorPositionStack[i]))
		{
			ddVec2_set(&g_cursorPosition, __cursorPositionStack[i]);
			ddVec2_set(&__cursorPositionStack[i], __v2empty);
			cursor_moveToVec(g_cursorPosition);
			return true;
		}
	}
	return false;
}
bool cursor_push(void)
{
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
	{
		if (ddVec2_compare(__v2empty, __cursorPositionStack[i]))
		{
			ddVec2_set(&__cursorPositionStack[i], g_cursorPosition);
			return true;
		}
	}
	return false;
}
void cursor_chWrite(const char* ch)
{
	ddsize _len;
	cstring_get_length(ch, &_len);
	__ddPrint(ch, _len);
	g_cursorPosition.x += _len;
}
void cursor_dsWrite(const ddString ds)
{
	ddPrint_ddString(ds);
	g_cursorPosition.x += ds.length;
}
void cursor_chWriteLine(const char* ch)
{
	ddsize _len;
	cstring_get_length(ch, &_len);
	__ddPrint(ch, _len);
	ddPrint_nl();
	g_cursorPosition.y++;
	g_cursorPosition.x = 0;
}
void cursor_dsWriteLine(const ddString ds)
{
	ddPrint_ddString(ds);
	ddPrint_nl();
	g_cursorPosition.y++;
	g_cursorPosition.x = 0;
}
void cursor_clear(void)
{
	cursor_moveTo(g_consoleWidth, g_consoleHeight);
	cursor_setBGColor(g_cursorBGColor);
	ddPrint_cstring("\x1b[1J");
	ddPrint_cstring("\x1b[0;0H");
	g_cursorPosition.x = 0;
	g_cursorPosition.y = 0;
}


void cursor_setFGColorRGB(int r, int g, int b)
{
	if (r < 0 && g < 0 && b < 0)
		return;
	g_cursorFGColor = make_ddColor(r, g, b);
	ddFColor dfc = make_ddFColor(r, g, b);
	ddPrint_ddString(dfc.color);
	raze_ddFColor(&dfc);
}
void cursor_setFGColor(ddColor dc)
{
	 cursor_setFGColorRGB(dc.r, dc.g, dc.b);
}

void cursor_setBGColorRGB(int r, int g, int b)
{
	if (r < 0 && g < 0 && b < 0)
		return;
	g_cursorBGColor = make_ddColor(r, g, b);
	ddBColor dbc = make_ddBColor(r, g, b);
	ddPrint_ddString(dbc.color);
	raze_ddBColor(&dbc);
}
void cursor_setBGColor(ddColor dc)
{
	cursor_setBGColorRGB(dc.r, dc.g, dc.b);
}
bool cursor_colorPop(void)
{
	for (int i = __CURSOR_STACK_LENGTH - 1; i >= 0; i--)
	{
		if (__cursorFGStack[i].g != 420)
		{
			cursor_setFGColor(__cursorFGStack[i]);
			cursor_setBGColor(__cursorBGStack[i]);
			__cursorFGStack[i].g = 420;
			__cursorBGStack[i].g = 420;
			return true;
		}
	}
	return false;
}
bool cursor_colorPush(void)
{
	for (int i = 0; i < __CURSOR_STACK_LENGTH; i++)
	{
		if (__cursorFGStack[i].g == 420)
		{
			__cursorFGStack[i] = g_cursorFGColor;
			__cursorBGStack[i] = g_cursorBGColor;
			return true;
		}
	}
	return false;
}


#endif
