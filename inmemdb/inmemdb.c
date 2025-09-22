#include "inmemdb.h"

bool servercontinuation;
bool childcontinuation;

int32 handle_hello(Client*, int8*, int8*);
CmdHandler handlers[] = {
    {(int8*)"hello", handle_hello }
};

Callback getcmd(int8 *cmd){
    printf("%zu\n", sizeof(handlers));
    return NULL;
}


int32 handle_hello(Client *cli, int8* folder, int8 *args){
        dprintf(cli->s, "hello '%s'\n", folder ); 
        return 0;
}

void zero(int8 *str, int16 size){
    int8 *p;
    int16 n;
    for(n = 0, p=str;n<size;p++,n++){
            *p = 0;
    }
    return;
    //Takes a pointer to memory (int8 *str) and a size in bytes (int16 size).
    //Iterates through each byte of that memory.
    //Writes 0 into each byte.
    //zero() is just a manual implementation of memset(..., 0, ...).
}

void childloop(Client *cli) {
    int8 buf[256]; // buffer for input
    int16 n;

    int8 cmd[256], folder[256], args[256];
    zero(buf, 256);
    zero(cmd, 256);
    zero(folder, 256);
    zero(args, 256);

    // Read from socket
    n = read(cli->s, (char*) buf, 255);
    if (n <= 0) {
        return; // nothing read or error
    }
    buf[n] = 0; // null-terminate

    // Strip trailing newlines/carriage returns
    char *end = (char*)buf + strlen((char*)buf) - 1;
    while (end >= (char*)buf && (*end == '\n' || *end == '\r')) {
        *end = 0;
        end--;
    }

    // Example: "insert /Users/harsh iqwbfiw"

    char *token;
    char *saveptr;

    // First word → cmd
    token = strtok_r((char*)buf, " ", &saveptr);
    if (token) {
        strncpy((char*)cmd, token, 255);
    }

    // Second word → folder
    token = strtok_r(NULL, " ", &saveptr);
    if (token) {
        strncpy((char*)folder, token, 255);
    }

    // Remaining → args
    token = strtok_r(NULL, "", &saveptr); // take rest of string
    if (token) {
        strncpy((char*)args, token, 255);
    }

    // Print results
    dprintf(cli->s, "\ncmd:\t%s\n", cmd);
    dprintf(cli->s, "folder:\t%s\n", folder);
    dprintf(cli->s, "args:\t%s\n", args);

    return;
}


void mainloop(int s){
    struct sockaddr_in cli;
    int32 len;
    int s2;
    char *ip;
    int16 port;
    Client* client;
    pid_t pid;


    s2 = accept(s, (struct sockaddr *)&cli, (unsigned int *)&len);

    if(s2<0){
        
        return;

    }

    port = (int16)ntohs((int)cli.sin_port);
    ip = inet_ntoa(cli.sin_addr);
    printf("Connection from %s:%d\n", ip, port);

    client = (Client*)malloc(sizeof(struct s_client));
    assert(client);

    zero((int8 *)client, sizeof(struct s_client));
    client->s = s2;
    client-> port = port;
    strncpy(client->ip, ip, 15);

    pid = fork();
    if(pid){
        free(client);
        return;
    }
    else{
        dprintf(s2, "100 Connected to inmemdb server\n");
        childcontinuation = true;
        while(childcontinuation){
                    childloop(client);


        }
        close(s2);
        free(client);
    }


    return;

}

int initializeserver(int16 port){
    struct sockaddr_in sock;
    int s;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = inet_addr(HOST);

    s = socket(AF_INET, SOCK_STREAM, 0);
    assert(s>0);

    errno = 0;
    if(bind(s, (struct sockaddr *)&sock, sizeof(sock))){
        assert_perror(errno);
    }


    errno = 0;
    if(listen(s, 20)){
        assert_perror(errno);
    }
    
    printf("Server listening on %s: %d\n", HOST, port); 
    return s;
}


int main(int argc, char *argv[]){

    char *sport;
    int16 port;


    getcmd((int8*)"hello");
    if(argc<2){
        sport = PORT;
    }
    else{
        sport = argv[1];
    }

    port = (int16)atoi(sport);

    int s = initializeserver(port);

    servercontinuation = true;

    while(servercontinuation){
        mainloop(s);

    }

    printf("Shutting down\n");
    close(s);
    return 0;

}

#pragma GCC diagnostic pop