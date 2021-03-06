#ifndef __ddcSockets__
#define __ddcSockets__

#include <sys/socket.h>
#include <arpa/inet.h>

struct dsocket
{
	int dscr;
	int port;
	struct sockaddr_in server;
	ddString addr;
};

struct dsocket make_dsocket(char* addr, int port)
{
	struct dsocket output;
	output.addr = make_ddString(addr);
	output.port = port;
}

void raze_dsocket(struct dsocket* sck)
{
	raze_ddString(&(sck->addr);
}

int dsocket_connect(struct dsocket sck)
{
	sck.dscr = socket(AF_INET, SOCK_STREAM, 0);
	if (sck.dscr == -1) return 0;
	sck.server.sin_addr.s_addr = inet_addr(sck.addr.cstr);
	sck.server.sin_family = AF_INET;
	sck.server.sin_port = htons(sck.port);
	if (connect(sck.dscr, (struct sockaddr*)&sck.server, sizeof(sck.server)) < 0)
		return 0;
	return 1;
}

#endif
