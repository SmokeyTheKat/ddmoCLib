#ifndef __ddcApplications__
#define __ddcApplications__

#include <ddcDef.h>
#include <ddcVec.h>
#include <ddcCursor.h>
#include <ddcShapes.h>
#include <ddcCharSets.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include <ddcHolder.h>


typedef struct ddApplication ddApplication
typedef struct ddSelect ddSelect;

struct ddApplication
{
	ddString name;
	oStatus status;
	ddHolder drawStack;
	ddColor BGColor;
	ddColor FGColor;
};

struct ddSelect
{
	ddVec2 position;
	ddSquare element;
	ddString title;


	void** onSelect;
	ddString* options;
	ddsize optionsLength;

	ddColor BGColor;
	ddColor optionBGColor;
	ddColor optionFGColor;
	ddColor optionSelectedFGColor;
};

void make_ddSelect(ddVec2 position);
void ddSelect_draw();






#endif
