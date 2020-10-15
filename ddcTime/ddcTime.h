#ifndef __ddcTime__
#define __ddcTime__

#include <ddcDef.h>
#include <time.h>

#define ddTimeThis(x,y,v) ddTimerStart();for (int i = 0; i < y; i++){x};v=ddTimerStop();

void ddTimerStart(void);
double ddTimerStop(void);
double ddTimerTime(void);
bool ddTimerIsPast(double _v);

static clock_t __dt_begin;
static clock_t __dt_end;

void ddTimerStart(void)
{
	__dt_begin = clock();
}
double ddTimerStop(void)
{
	__dt_end = clock();
	return ((double)(__dt_end - __dt_begin) / CLOCKS_PER_SEC);
}
double ddTimerTime(void)
{
	return ((double)(clock() - __dt_begin) / CLOCKS_PER_SEC);
}
bool ddTimerIsPast(double _v)
{
	return (_v < ((double)(clock() - __dt_begin) / CLOCKS_PER_SEC));
}


#endif
