#include <ddcArguments.h>
#include <ddcPrint.h>
#include <ddcString.h>
#include <stdio.h>
#include "ddcDef.h"

int v = 0;

MAINF__
{
	SET_DDARGS__;
	int v;
	run
	oBLOCK
		if (daHasch(da, "yo"))
		{
			leave(1);
		}
		if (daHasch(da, "bro"))
		{
			leave(2);
		}
		leave(3);
	cBLOCK
	end(1)
	{
		chPrintL("yoyoyoyoyoyoyoyoyoyoyo");
	}
	end(2)
	{
		chPrintL("whats up brooo");
	}
	end(3)
	{
		chPrintL("YOU GONNA SAY SOMETHING BRO!?!");
	}
	return 0;
}
