#include "./ddcArgs.h"
#include "./ddcCharSets.h"
#include "./ddcPrint.h"
#include "./ddcGArray.h"
#include "./ddcMem.h"
#include "./ddcString.h"
#include "./ddcVec.h"
#include "./ddcBits.h"
#include "./ddcNLoops.h"
#include "./ddcTime.h"
#include "./ddcSocket.h"
#include "./ddcLine.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	struct dsocketServer srv = make_dsocketServer(8080);
	dsocketServer_bind(&srv);
	dsocketServer_start_listen(&srv);
	int client = dsocketServer_listen(&srv);
	char buffer[1024] = {0};
	dsocketServer_receive(srv, client, buffer, 1024);
	ddPrintf("recv: %s\n", buffer);
	dsocketServer_send(srv, client, "OMG", 5);
	
	return 0;
}
