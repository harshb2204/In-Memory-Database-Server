#define _GNU_SOURCE

#ifndef inmemdb
#define inmemdb

#pragma GCC diagnostic ignored "-Wstringop-truncation"
#pragma GCC diagnostic push

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <stdarg.h>

#define HOST "127.0.0.1"
#define PORT "12000"

typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;

// Forward declaration
struct s_client;
typedef struct s_client Client;


typedef int32 (*Callback)(Client*, int8*, int8*);

struct s_cmdhandler {
    int8* cmd;
    Callback handler;
};

typedef struct s_cmdhandler CmdHandler;

struct s_client
{
    int s;
    char ip[16];
    int16 port;
};



void mainloop(int);
void childloop(Client*);
int initializeserver(int16);
int main(int, char**);

#endif

