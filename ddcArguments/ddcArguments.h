#include <ddcDef.h>
#include <ddcString.h>

#ifndef __ddcArguments__
#define __ddcArguments__
typedef struct ddArguments ddArguments;

struct ddArguments
{
	ddsize agsc;
	char** ags;
};

ddArguments make_ddArguments(char** _ags, ddsize _agsc)
{
	ddArguments _o;
	_o.ags = _ags;
	_o.agsc = _agsc;
	return _o;
}

bool daHasch(ddArguments _da, const char* _ch)
{
	for (ddsize i = 0; i < _da.agsc; i++)
	{
		if (chcmp(_ch, _da.ags[i]))  return true;
	}
	return false;
}
bool daHasds(ddArguments _da, ddString _ds)
{
	for (ddsize i = 0; i < _da.agsc; i++)
	{
		bool _t = true;
		for (ddsize j = 0; j < _ds.length; j++)
		{
			if (_ds.cstr[i] != _da.ags[i][j]) _t = false; break;
		}
		if (_t)  return true;
	}
	return false;
}
#endif
