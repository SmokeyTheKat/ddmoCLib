#ifndef __ddcSockets__
#define __ddcSockets__

#ifdef __unix__

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define __DSOCKET_BUFFER_SIZE 1024

struct dsocket_udp_client;
struct dsocket_udp_server;

static struct dsocket_udp_server make_dsocket_udp_server(int port);
static int dsocket_udp_server_bind(struct dsocket_udp_server* sck);
static struct sockaddr_in dsocket_udp_server_receive(struct dsocket_udp_server sck, char* buffer, long* length, long max_length);
static int dsocket_udp_server_send(struct dsocket_udp_server sck, struct sockaddr_in client, char* buffer, long length);

static struct dsocket_udp_client make_dsocket_udp_client(char* addr, int port);
static int dsocket_udp_client_connect(struct dsocket_udp_client* sck);
static int dsocket_udp_client_send(struct dsocket_udp_client sck, char* buffer, long length);
static int dsocket_udp_client_receive(struct dsocket_udp_client sck, char* buffer, long* length, long max_length);

struct dsocket_udp_client
{
	int dscr;
	int port;
	char* addr;
	struct sockaddr_in server;
	int server_len;
};

struct dsocket_udp_server
{
	int dscr;
	int port;
	struct sockaddr_in server;
	int server_len;
};

static struct dsocket_udp_client make_dsocket_udp_client(char* addr, int port)
{
	struct dsocket_udp_client output;
	output.addr = addr;
	output.port = port;
	return output;
}
static int dsocket_udp_client_connect(struct dsocket_udp_client* sck)
{
	if ((sck->dscr = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		return 1;
	sck->server.sin_family = AF_INET;
	sck->server.sin_port = htons(sck->port);
	sck->server.sin_addr.s_addr = inet_addr(sck->addr);
}

static int dsocket_udp_client_send(struct dsocket_udp_client sck, char* buffer, long length)
{
	sendto(sck.dscr, buffer, length, 0, (struct sockaddr*)&sck.server, sizeof(sck.server));
}
static int dsocket_udp_client_receive(struct dsocket_udp_client sck, char* buffer, long* length, long max_length)
{
	int len;
	*length = recvfrom(sck.dscr, buffer, max_length, MSG_WAITALL, (struct sockaddr*)&sck.server, &len);
}

static struct dsocket_udp_server make_dsocket_udp_server(int port)
{
	struct dsocket_udp_server output;
	output.server_len = sizeof(output.server);
	output.port = port;
	return output;
}

static int dsocket_udp_server_bind(struct dsocket_udp_server* sck)
{
	if ((sck->dscr = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		return 1;
	sck->server.sin_port = htons(sck->port);
	sck->server.sin_family = AF_INET;
	sck->server.sin_addr.s_addr = INADDR_ANY;
	if (bind(sck->dscr, (struct sockaddr*)&sck->server, sizeof(sck->server)) < 0)
		return 1;
}

static int dsocket_udp_server_send(struct dsocket_udp_server sck, struct sockaddr_in client, char* buffer, long length)
{
	recvfrom(sck.dscr, buffer, length, MSG_CONFIRM, (struct sockaddr*)&client, sizeof(client));
}

static struct sockaddr_in dsocket_udp_server_receive(struct dsocket_udp_server sck, char* buffer, long* length, long max_length)
{
	struct sockaddr_in client = {0};
	int client_len = sizeof(client);
	*length = recvfrom(sck.dscr, buffer, max_length, MSG_WAITALL, (struct sockaddr*)&client, &client_len);
	return client;
}





struct dsocket_tcp_client;
struct dsocket_tcp_server;

static struct dsocket_tcp_server make_dsocket_tcp_server(int port);
static int dsocket_tcp_server_bind(struct dsocket_tcp_server* sck);
static int dsocket_tcp_server_start_listen(struct dsocket_tcp_server* sck);
static int dsocket_tcp_server_listen(struct dsocket_tcp_server* sck);
static int dsocket_tcp_server_send(struct dsocket_tcp_server sck, int client, const char* data, long length);
static int dsocket_tcp_server_receive(struct dsocket_tcp_server sck, int client, char* buffer, long length);

static struct dsocket_tcp_client make_dsocket_tcp_client(char* addr, int port);
static void raze_dsocket_tcp_client(struct dsocket_tcp_client* sck);
static int dsocket_tcp_client_connect(struct dsocket_tcp_client* sck);
static int dsocket_tcp_client_send(struct dsocket_tcp_client sck, const char* data, long length);
static int dsocket_tcp_client_receive(struct dsocket_tcp_client sck, char* buffer, long length);

struct dsocket_tcp_client
{
	int dscr;
	int port;
	struct sockaddr_in server;
	char* addr;
};

struct dsocket_tcp_server
{
	int dscr;
	int port;
	int opt;
	struct sockaddr_in server;
	int server_len;
};

static struct dsocket_tcp_server make_dsocket_tcp_server(int port)
{
	struct dsocket_tcp_server output;
	output.server_len = sizeof(output.server);
	output.port = port;
	output.opt = 1;
	return output;
}

static int dsocket_tcp_server_bind(struct dsocket_tcp_server* sck)
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
static int dsocket_tcp_server_start_listen(struct dsocket_tcp_server* sck)
{
	if (listen(sck->dscr, 3) < 0)
		return 1;
	return 0;
}
static int dsocket_tcp_server_listen(struct dsocket_tcp_server* sck)
{
	int client_out = -1;
	if ((client_out = accept(sck->dscr, (struct sockaddr*)&sck->server, (socklen_t*)&(sck->server_len))) < 0)
		return -1;
	return client_out;
}
static int dsocket_tcp_server_send(struct dsocket_tcp_server sck, int client, const char* data, long length)
{
	send(client, data, length, 0);
	return 1;
}
static int dsocket_tcp_server_receive(struct dsocket_tcp_server sck, int client, char* buffer, long length)
{
	return read(client, buffer, length);
}

static struct dsocket_tcp_client make_dsocket_tcp_client(char* addr, int port)
{
	struct dsocket_tcp_client output;
	output.addr = addr;
	output.port = port;
	return output;
}

static void raze_dsocket_tcp_client(struct dsocket_tcp_client* sck)
{
	//raze_ddString(&(sck->addr));
}

static int dsocket_tcp_client_connect(struct dsocket_tcp_client* sck)
{
	sck->dscr = socket(AF_INET, SOCK_STREAM, 0);
	if (sck->dscr == -1) return 1;
	sck->server.sin_family = AF_INET;
	sck->server.sin_port = htons(sck->port);
	if (inet_pton(AF_INET, sck->addr, &sck->server.sin_addr) <= 0) return 1;

/*
	struct timeval timeout;      
	timeout.tv_sec = 0;
	timeout.tv_usec = 10000;
	
	if (setsockopt (sck->dscr, SOL_SOCKET, SO_RCVTIMEO, &timeout,
				sizeof timeout) < 0)
		error("setsockopt failed\n");

	if (setsockopt (sck->dscr, SOL_SOCKET, SO_SNDTIMEO, &timeout,
				sizeof timeout) < 0)
		error("setsockopt failed\n");
*/
	
	return connect(sck->dscr, (struct sockaddr*)&sck->server, sizeof(sck->server));
}
static int dsocket_tcp_client_send(struct dsocket_tcp_client sck, const char* data, long length)
{
	return send(sck.dscr, data, length, 0);
}
static int dsocket_tcp_client_receive(struct dsocket_tcp_client sck, char* buffer, long length)
{
	return read(sck.dscr, buffer, length);
}

#endif

#ifdef __WIN64

#include <stdio.h>
#include <winsock.h>

struct dsocket_tcp_client;
struct dsocket_tcp_server;

static void dsocket_init(void);

static struct dsocket_tcp_server make_dsocket_tcp_server(int port);
static int dsocket_tcp_server_bind(struct dsocket_tcp_server* sck);
static int dsocket_tcp_server_start_listen(struct dsocket_tcp_server* sck);
static int dsocket_tcp_server_listen(struct dsocket_tcp_server* sck);
static int dsocket_tcp_server_send(struct dsocket_tcp_server sck, int client, const char* data, long length);
static int dsocket_tcp_server_receive(struct dsocket_tcp_server sck, int client, char* buffer, long length);

static struct dsocket_tcp_client make_dsocket_tcp_client(char* addr, int port);
static void raze_dsocket_tcp_client(struct dsocket_tcp_client* sck);
static int dsocket_tcp_client_connect(struct dsocket_tcp_client* sck);
static int dsocket_tcp_client_send(struct dsocket_tcp_client sck, const char* data, long length);
static int dsocket_tcp_client_receive(struct dsocket_tcp_client sck, char* buffer, long length);

static void dsocket_init(void)
{
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		exit(1);
	}
}

struct dsocket_tcp_client
{
	int dscr;
	int port;
	struct sockaddr_in server;
	char* addr;
};

struct dsocket_tcp_server
{
	int dscr;
	int port;
	int opt;
	struct sockaddr_in server;
	int server_len;
};

static struct dsocket_tcp_server make_dsocket_tcp_server(int port)
{
	struct dsocket_tcp_server output;
	output.server_len = sizeof(output.server);
	output.port = port;
	output.opt = 1;
	return output;
}

static int dsocket_tcp_server_bind(struct dsocket_tcp_server* sck)
{
	if ((sck->dscr = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		return 1;
	/*if (setsockopt(sck->dscr, SOL_SOCKET, SO_REUSEADDR, (const char*)&(sck->opt), sizeof(sck->opt)))
		return 1;*/
	sck->server.sin_family = AF_INET;
	sck->server.sin_addr.s_addr = INADDR_ANY;
	sck->server.sin_port = htons(sck->port);
	if (bind(sck->dscr, (struct sockaddr*)&sck->server, sizeof(sck->server)) < 0)
		return 1;
	return 0;
}
static int dsocket_tcp_server_start_listen(struct dsocket_tcp_server* sck)
{
	if (listen(sck->dscr, 3) < 0)
		return 1;
	return 0;
}
static int dsocket_tcp_server_listen(struct dsocket_tcp_server* sck)
{
	int client_out = -1;
	if ((client_out = accept(sck->dscr, (struct sockaddr*)&sck->server, (int*)&(sck->server_len))) < 0)
		return -1;
	return client_out;
}
static int dsocket_tcp_server_send(struct dsocket_tcp_server sck, int client, const char* data, long length)
{
	send(client, data, length, 0);
	return 1;
}
static int dsocket_tcp_server_receive(struct dsocket_tcp_server sck, int client, char* buffer, long length)
{
	return recv(client, buffer, length, 0);
}

static struct dsocket_tcp_client make_dsocket_tcp_client(char* addr, int port)
{
	struct dsocket_tcp_client output;
	output.addr = addr;
	output.port = port;
	return output;
}

static void raze_dsocket_tcp_client(struct dsocket_tcp_client* sck)
{
}

static int dsocket_tcp_client_connect(struct dsocket_tcp_client* sck)
{
	sck->dscr = socket(AF_INET, SOCK_STREAM, 0);
	if (sck->dscr == -1) return 1;
	sck->server.sin_family = AF_INET;
	sck->server.sin_port = htons(sck->port);
	sck->server.sin_addr.s_addr = inet_addr(sck->addr);
	return connect(sck->dscr, (struct sockaddr*)&sck->server, sizeof(sck->server));
}
static int dsocket_tcp_client_send(struct dsocket_tcp_client sck, const char* data, long length)
{
	return send(sck.dscr, data, length, 0);
}
static int dsocket_tcp_client_receive(struct dsocket_tcp_client sck, char* buffer, long length)
{
	return recv(sck.dscr, buffer, length, 0);
}


#endif

#endif
