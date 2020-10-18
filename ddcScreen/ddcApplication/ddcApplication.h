#ifndef __ddcApplications__
#define __ddcApplications__

#include <ddcDef.h>
#include <ddcVec.h>
#include <ddcCursor.h>
#include <ddcShapes.h>
#include <ddcCharSets.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include <ddcGArray.h>

struct ddApplication;
struct ddSelect;
struct ddPanel;
struct ddText;


typedef struct ddApplication ddApplication;
typedef struct ddSelect ddSelect;
typedef struct ddPanel ddPanel;
typedef struct ddText ddText;

typedef enum ddaTextAlign ddaTextAlign;
typedef enum ddAppDrawingElems ddAppDrawingElems;
enum ddaTextAlign { ALIGN_LEFT=0, ALIGN_CENTER, ALIGN_RIGHT };
enum ddAppDrawingElems { DDAE_NONE=0, DDAE_DDSELECT, DDAE_DDPANEL, DDAE_TEXT, DDAE_LINE };

ddApplication init_ddApplication(ddString _name, ddColor _fgc, ddColor _bgc);
void exit_ddApplication(ddApplication* _da);
void update_ddApplication(ddApplication* _da);
void loop_ddApplication(void (*f)(void));

ddText make_ddText(ddString _text, ddVec2 _pos, ddColor _fgc, ddColor _bgc);
void raze_ddText(ddText* _dt);
void draw_ddText(ddText _dt);

ddPanel make_ddPanel(ddVec2 _pos, ddVec2 _size, ddText _title, ddColor _bgc);
void raze_ddPanel(ddPanel* _dp);
void draw_ddPanel(ddPanel _dp);

ddSelect make_ddSelect(ddVec2 _pos, ddVec2 _size, ddText _title, ddColor _bgc, ddsize _ds, ddColor _sbc);
void raze_ddSelect(ddSelect* _ds);
void draw_ddSelect(ddSelect _ds);


struct ddApplication
{
	ddString name;
	DOStatus status;
	ddGArray drawStack;
	ddAppDrawingElems* drawStackElems;
	ddColor BGColor;
	ddColor FGColor;
};

struct ddText
{
	ddVec2 position;
	ddString text;
	ddColor FGColor;
	ddColor BGColor;

	ddaTextAlign textAlign;

	DOStatus status;
};

struct ddPanel
{
	ddVec2 position;
	ddVec2 size;

	DOStatus status;

	ddSquare element;
	ddText title;

	ddColor BGColor;
	ddColor FGColor;
};

struct ddSelect
{
	ddPanel panel;

	void (**onSelect)(int);
	ddText* options;
	ddsize optionsLength;
	ddsize optionsSize;

	ddColor selectedBGColor;

	DOStatus status;
};



ddText make_ddText(ddString _text, ddVec2 _pos, ddColor _fgc, ddColor _bgc)
{
	ddText _o;
	_o.text       = _text;
	_o.position   = _pos;
	_o.FGColor    = _fgc;
	_o.BGColor    = _bgc;
	_o.textAlign  = ALIGN_LEFT;
	_o.status     = DOS_ACTIVE;
	return _o;
}
ddText make_dft_ddText(ddString _text)
{
	ddText _o;
	_o.text       = _text;
	_o.position   = make_ddVec2(0,0);
	_o.FGColor    = make_ddColor(-1,-1,-1);
	_o.BGColor    = make_ddColor(-1,-1,-1);
	_o.textAlign  = ALIGN_LEFT;
	_o.status     = DOS_ACTIVE;
	return _o;
}
void raze_ddText(ddText* _dt)
{
	if (_dt->status != DOS_DELETED)
		raze_ddString(&(_dt->text));
	_dt->status = DOS_DELETED;
}
void draw_ddText(ddText _dt)
{
	cursor_colorPush();
	if (_dt.textAlign == ALIGN_LEFT)
	{
		cursor_setFGColor(_dt.FGColor);
		cursor_setBGColor(_dt.BGColor);
		cursor_moveToVec(_dt.position);
		cursor_dsWrite(_dt.text);
	}
	cursor_colorPop();
}




ddPanel make_ddPanel(ddVec2 _pos, ddVec2 _size, ddText _title, ddColor _bgc)
{
	ddPanel _o;
	_o.position = _pos;
	_o.size = _size;
	_o.title = _title;
	_o.BGColor = _bgc;
	_o.FGColor = make_ddColor(0,0,0);
	_o.element = make_ddSquare(_pos, _size, " ");
	_o.status = DOS_ACTIVE;
	return _o;
}
void raze_ddPanel(ddPanel* _ds)
{
	if (_ds->status != DOS_DELETED)
	{
		raze_ddText(&(_ds->title));
	}
	_ds->status = DOS_DELETED;
}
void draw_ddPanel(ddPanel _ds)
{
	cursor_colorPush();
	cursor_setFGColor(make_ddColor(0,0,0));
	cursor_setBGColor(_ds.BGColor);
	draw_ddSquare(_ds.element);

	draw_thick_line_points(_ds.position, make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y), cset_horizontalBar);
	draw_thick_line_points(_ds.position, make_ddVec2(_ds.position.x, _ds.position.y+_ds.size.y-1), cset_verticalBar);
	draw_thick_line_points(make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y+_ds.size.y-1),
					make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y), cset_verticalBar);
	draw_thick_line_points(make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y+_ds.size.y-1),
					make_ddVec2(_ds.position.x, _ds.position.y+_ds.size.y-1), cset_horizontalBar);

	cursor_moveToVec(_ds.position);
	cursor_chWrite(cset_upRightBar);

	cursor_moveTo(_ds.position.x+_ds.size.x-1, _ds.position.y);
	cursor_chWrite(cset_upLeftBar);

	cursor_moveTo(_ds.position.x, _ds.position.y+_ds.size.y-1);
	cursor_chWrite(cset_downRightBar);

	cursor_moveTo(_ds.position.x+_ds.size.x-1, _ds.position.y+_ds.size.y-1);
	cursor_chWrite(cset_downLeftBar);


	_ds.title.position = make_ddVec2((_ds.position.x+((int)(_ds.size.x/2)))-((int)(_ds.title.text.length/2)), (_ds.position.y));
	draw_ddText(_ds.title);

	cursor_moveTo(((_ds.position.x+((int)(_ds.size.x/2)))-((int)(_ds.title.text.length/2)))-1, _ds.position.y);
	cursor_chWrite(cset_rightStopBar);

	cursor_moveTo(((_ds.position.x+((int)(_ds.size.x/2)))-((int)(_ds.title.text.length/2)))+_ds.title.text.length, _ds.position.y);
	cursor_chWrite(cset_leftStopBar);


	cursor_colorPop();
}


ddSelect make_ddSelect(ddVec2 _pos, ddVec2 _size, ddText _title, ddColor _bgc, ddsize _ds, ddColor _sbc)
{
	ddSelect _o;
	_o.panel = make_ddPanel(_pos, _size, _title, _bgc);
	_o.optionsSize = _ds;
	_o.options = make(ddText, _ds);
	//_o.onSelect = calloc(_ds, sizeof(void (*)(int)) );
	_o.optionsLength = 0;
	_o.selectedBGColor = _sbc;
	_o.status = DOS_ACTIVE;
	return _o;
}
void raze_ddSelect(ddSelect* _ds)
{
	if (_ds->status != DOS_DELETED)
	{
		for (int i = 0; i < _ds->optionsLength; i++)
		{
			raze_ddText(&(_ds->options[i]));
		}
		raze(_ds->options);
		raze(_ds->onSelect);
	}
	_ds->status = DOS_DELETED;
}
bool ddSelect_addOption(ddSelect* _ds, ddText _dt)
{
	if (_ds->status != DOS_DELETED) return false;
	if (_ds->optionsLength+1 > _ds->optionsSize)
		return false; 
	
	_ds->options[_ds->optionsLength] = _dt;

	_ds->optionsLength++;
	return true;
}
void draw_ddSelect(ddSelect _ds)
{
	draw_ddPanel(_ds.panel);
	cursor_setBGColor(_ds.panel.BGColor);
	cursor_setFGColor(_ds.panel.FGColor);
	for (int i = 0; i < _ds.optionsLength; i++)
	{
		_ds.options[i].position.x = _ds.panel.position.x+1;
		_ds.options[i].position.y = _ds.panel.position.y+1+i;
		draw_ddText(_ds.options[i]);
	}
}





#endif
