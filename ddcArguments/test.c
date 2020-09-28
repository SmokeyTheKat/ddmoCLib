#include "ddcArguments.h"

int main(ddsize agsc, char** ags)
{
	ddArguments da = readArguments(ags, agsc);
	ddString ds = nddString("yo");
	if (daHasds(da, ds))
	{
		printf("OMGOMGOMGM\n");
	}
	else
	{
		printf(da.ags[1]);
		printf("\n");
	}
	return 0;
}
