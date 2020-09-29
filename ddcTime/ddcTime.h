#ifndef __ddcTime__
#define __ddcTime__

#include <ddcDef.h>

#include <time.h>


static clock_t __dt_begin;
static clock_t __dt_end;

void ddTimerStart()
{
	__dt_begin = clock();
}
double ddTimerStop()
{
	__dt_end = clock();
	return ((double)(__dt_end - __dt_begin) / CLOCKS_PER_SEC);
}


#endif
