#ifndef __ddcBeep_h__
#define __ddcBeep_h__

#include <stdlib.h>

void ddBeep(void)
{
	system("printf '\a' >> /dev/tty1");
}

#endif
