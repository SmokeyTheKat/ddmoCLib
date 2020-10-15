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


typedef struct ddApplication ddApplication;
typedef struct ddSelect ddSelect;
typedef struct ddPanel ddPanel;
typedef struct ddText ddText;

typedef enum ddaTextAlign ddaTextAlign;
enum ddaTextAlign { ALIGN_LEFT=0, ALIGN_CENTER, ALIGN_RIGHT };

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

ddSelect make_ddSelect(ddPanel* _dp, ddsize _ds, ddColor _sbgc);
void raze_ddSelect(ddSelect* _ds);
void draw_ddSelect(ddSelect _ds);



struct ddApplication
{
	ddString name;
	Ostatus status;
	ddGArray drawStack;
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

	Ostatus status;
};

struct ddSelect
{
	Ostatus status;

	ddPanel* panel;

	void (**onSelect)(int);
	ddText* options;
	ddsize optionsLength;
	ddsize optionsSize;

	ddColor selectedBGColor;
};

struct ddPanel
{
	ddVec2 position;
	ddVec2 size;

	Ostatus status;

	ddSquare element;
	ddText title;

	ddColor BGColor;
};


ddText make_ddText(ddString _text, ddVec2 _pos, ddColor _fgc, ddColor _bgc)
{
	ddText _o;
	_o.text       = _text;
	_o.position   = _pos;
	_o.FGColor    = _fgc;
	_o.BGColor    = _bgc;
	_o.textAlign  = ALIGN_LEFT;
	return _o;
}
void raze_ddText(ddText* _dt)
{
	raze_ddString(&(_dt->text));
	//_dt->status = delted;
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
	_o.element = make_ddSquare(_pos, _size, " ");
	return _o;
}
void raze_ddPanel(ddPanel* _ds)
{
	raze_ddText(&(_ds->title));
}
void draw_ddPanel(ddPanel _ds)
{
	cursor_colorPush();
	cursor_setFGColor(make_ddColor(0,0,0));
	cursor_setBGColor(_ds.BGColor);
	draw_ddSquare(_ds.element);

	draw_linePoints(_ds.position, make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y), cset_horizontalBar);
	draw_linePoints(_ds.position, make_ddVec2(_ds.position.x, _ds.position.y+_ds.size.y-1), cset_verticalBar);
	draw_linePoints(make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y+_ds.size.y-1),
					make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y), cset_verticalBar);
	draw_linePoints(make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y+_ds.size.y-1),
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


void* __get_init_value(ddsize _index, ddApplication _da)
{
	cursor_init();
	cursor_home();
	for (int i = 0; i < cursorPosition.x; i++)
	{
		cursor_moveTo
	}
}



ddSelect make_ddSelect(ddPanel* _dp, ddsize _ds, ddColor _sbgc)
{
	ddSelect _o;
	_o.panel = _dp;
	_o.optionsSize = _ds;
	_o.options = make(ddText, _ds);
	_o.optionsLength = 0;
	_o.selectedBGColor = _sbgc;
	return _o;
}
void raze_ddSelect(ddSelect* _ds)
{
	raze_ddPanel(_ds->panel);
	if (_ds->options != nullptr)
	{
		for (int i = 0; i < _ds->optionsLength; i++)
		{
			raze_ddText(&(_ds->options[i]));
		}
		raze(_ds->options);
		raze(_ds->onSelect);
	}
}
bool ddSelect_addOption(ddSelect* _ds, ddText _dt)
{
	if (_ds->optionsLength+1 > _ds->optionsSize)
		return false; 
	
	_ds->options[_ds->optionsLength] = _dt;

	_ds->optionsLength++;
	return true;
}
void draw_ddSelect(ddSelect _ds)
{
	draw_ddPanel(*(_ds.panel));
	for (int i = 0; i < _ds.optionsLength; i++)
	{
		_ds.options[i].position.x = _ds.panel->position.x+1;
		_ds.options[i].position.y = _ds.panel->position.y+1+i;
		draw_ddText(_ds.options[i]);
	}
}





#endif
