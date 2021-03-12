#ifndef __ddcSockets__
#define __ddcSockets__

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define __DSOCKET_BUFFER_SIZE 1024

struct dsocketClient;
struct dsocketServer;

struct dsocketServer make_dsocketServer(int port);
int dsocketServer_bind(struct dsocketServer* sck);
int dsocketServer_start_listen(struct dsocketServer* sck);
int dsocketServer_listen(struct dsocketServer* sck);
int dsocketServer_send(struct dsocketServer sck, int client, const char* data, long length);
int dsocketServer_receive(struct dsocketServer sck, int client, char* buffer, long length);

struct dsocketClient make_dsocketClient(char* addr, int port);
void raze_dsocketClient(struct dsocketClient* sck);
int dsocketClient_connect(struct dsocketClient* sck);
int dsocketClient_send(struct dsocketClient sck, const char* data, long length);
int dsocketClient_receive(struct dsocketClient sck, char* buffer, long length);

struct dsocketClient
{
	int dscr;
	int port;
	struct sockaddr_in server;
	char* addr;
};

struct dsocketServer
{
	int dscr;
	int port;
	int opt;
	struct sockaddr_in server;
	int server_len;
};

struct dsocketServer make_dsocketServer(int port)
{
	struct dsocketServer output;
	output.server_len = sizeof(output.server);
	output.port = port;
	output.opt = 1;
	return output;
}

int dsocketServer_bind(struct dsocketServer* sck)
{
	if ((sck->dscr = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		return 1;
	if (setsockopt(sck->dscr, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &(sck->opt), sizeof(sck->opt)))
		return 1;
	sck->server.sin_family = AF_INET;
	sck->server.sin_addr.s_addr = INADDR_ANY;
	sck->server.sin_port = htons(sck->port);
	if (bind(sck->dscr, (struct sockaddr*)&sck->server, sizeof(sck->server)) < 0)
		return 1;
	return 0;
}
int dsocketServer_start_listen(struct dsocketServer* sck)
{
	if (listen(sck->dscr, 3) < 0)
		return 1;
	return 0;
}
int dsocketServer_listen(struct dsocketServer* sck)
{
	int client_out = -1;
	if ((client_out = accept(sck->dscr, (struct sockaddr*)&sck->server, (socklen_t*)&(sck->server_len))) < 0)
		return -1;
	return client_out;
}
int dsocketServer_send(struct dsocketServer sck, int client, const char* data, long length)
{
	send(client, data, length, 0);
	return 1;
}
int dsocketServer_receive(struct dsocketServer sck, int client, char* buffer, long length)
{
	read(client, buffer, length);
	return 1;
}

struct dsocketClient make_dsocketClient(char* addr, int port)
{
	struct dsocketClient output;
	output.addr = addr;
	output.port = port;
	return output;
}

void raze_dsocketClient(struct dsocketClient* sck)
{
	//raze_ddString(&(sck->addr));
}

int dsocketClient_connect(struct dsocketClient* sck)
{
	sck->dscr = socket(AF_INET, SOCK_STREAM, 0);
	if (sck->dscr == -1) return 1;
	sck->server.sin_family = AF_INET;
	sck->server.sin_port = htons(sck->port);
	if (inet_pton(AF_INET, sck->addr, &sck->server.sin_addr) <= 0) return 1;
	return connect(sck->dscr, (struct sockaddr*)&sck->server, sizeof(sck->server));
}
int dsocketClient_send(struct dsocketClient sck, const char* data, long length)
{
	return send(sck.dscr, data, length, 0);
}
int dsocketClient_receive(struct dsocketClient sck, char* buffer, long length)
{
	read(sck.dscr, buffer, length);
	return 1;
}

#endif
