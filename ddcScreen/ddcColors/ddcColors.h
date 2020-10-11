#ifndef __ddcColors__
#define __ddcColors__

#include <ddcDef.h>
#include <ddcString.h>
#include <ddcPrint.h>

typedef struct ddFColor ddFColor;
typedef struct ddBColor ddBColor;
typedef struct ddColor ddColor;

struct ddColor
{
	int r;
	int g;
	int b;
};

struct ddFColor
{
	ddString color;
};
struct ddBColor
{
	ddString color;
};

ddFColor make_ddFColor(int r, int g, int b);
ddBColor make_ddBColor(int r, int g, int b);
void raze_ddFColor(ddFColor* dfc);
void raze_ddBColor(ddBColor* dbc);

ddColor make_ddColor(int r, int g, int b)
{
	ddColor _o;
	_o.r = r;
	_o.g = g;
	_o.b = b;
	return _o;
}

ddFColor make_ddFColor(int r, int g, int b)
{
	ddFColor _o;
	ddString cs = make_ddString("");
	dsPushChFront(&cs, "\x1b[38;2;");
	ddString dr = intTds(r);
	ddString dg = intTds(g);
	ddString db = intTds(b);

	dsPushDsBack(&cs, dr);
	dsPushChBack(&cs, ";");
	dsPushDsBack(&cs, dg);
	dsPushChBack(&cs, ";");
	dsPushDsBack(&cs, db);
	dsPushChBack(&cs, "m");

	raze_ddString(&dr);
	raze_ddString(&dg);
	raze_ddString(&db);
	_o.color = cs;
	return _o;
}

ddBColor make_ddBColor(int r, int g, int b)
{
	ddBColor _o;
	ddString cs = make_ddString("");
	dsPushChFront(&cs, "\x1b[48;2;");
	ddString dr = intTds(r);
	ddString dg = intTds(g);
	ddString db = intTds(b);

	dsPushDsBack(&cs, dr);
	dsPushChBack(&cs, ";");
	dsPushDsBack(&cs, dg);
	dsPushChBack(&cs, ";");
	dsPushDsBack(&cs, db);
	dsPushChBack(&cs, "m");

	raze_ddString(&dr);
	raze_ddString(&dg);
	raze_ddString(&db);
	_o.color = cs;
	return _o;
}
void raze_ddFColor(ddFColor* _dfc)
{
	raze_ddString(&(_dfc->color));
}
void raze_ddBColor(ddBColor* _dbc)
{
	raze_ddString(&(_dbc->color));
}


#endif
