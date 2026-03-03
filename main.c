#include <stdio.h> 
#include <stdlib.h>     
#include <string.h>     
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>

#define MAX_CLIENTS 50

struct in_addr ipv4_addr; 
in_port_t port = 8080;

struct sockaddr_in socket_addr; 
struct sockaddr_in peeraddr; 

struct ctx {
    int clients[MAX_CLIENTS];
    int index;
}; 

struct ctx* context; 

void init_ctx() {
    context = malloc(sizeof(struct ctx));
    context->index = 0; 
}

int insert(int fd) {
    int index = context->index; 
    
    if(index == (MAX_CLIENTS - 1)) {
        return -1; 
    }
    
    context->clients[context->index] = fd; 
    context->index++; 
    return 0;
}

void drop_client(int fd) {
    int index = 0; 
    for(int i = 0; i < MAX_CLIENTS - 1; i++) {
        if(context->clients[i] == fd) {
            index = i; 
        }
    }
    
    context->clients[index] = 0; 
    context->index--; 
}

int start_http() {
    ipv4_addr.s_addr = htonl(0x7F000001);

    socket_addr.sin_family = AF_INET; 
    socket_addr.sin_port = htons(port);
    socket_addr.sin_addr = ipv4_addr;

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    int b = bind(socket_fd, (struct sockaddr*)&socket_addr, sizeof(socket_addr)); 
    
    if(b != 0) {
        perror("ERROR IN BIND"); 
    }
    
    if(listen(socket_fd, 100) == -1) {
	   perror("error listening");
    }
    
    return socket_fd; 
}

void handle(int client_fd, int server_fd, char* data) {
    
    
    printf("%s", "polla\n"); 
    
    insert(client_fd); 
    
    read(client_fd, data, 5000); 
    
    printf("%s", data);
    fflush(stdout); 
    
    

    char res[] =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n"
"Content-Length: 199\r\n"  
"Connection: close\r\n"
"\r\n"
"<!DOCTYPE html>\r\n"
"<html>\r\n"
"<head>\r\n"
"  <meta charset=\"UTF-8\">\r\n"
"  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\r\n"
"  \r\n"
"  <title>Pito en C</title>\r\n"
"</head>\r\n"
"<body>\r\n"
"  <h1>human</h1>\r\n"
"</body>\r\n"
"</html>\r\n"
"\0";


    write(client_fd, res, strlen(res)); 
    
    drop_client(client_fd); 
}

int main() {
   init_ctx(); 
   int socket_fd = start_http(); 
   
   char data[5000]; 
   memset(data, 0, sizeof(data)); 
   
   socklen_t client_len = sizeof(peeraddr); 

   while(1) {
       int fd = accept(socket_fd, (struct sockaddr*)&peeraddr, &client_len);
       handle(fd, socket_fd, data); 
       close(fd); 
   }

   return 0; 
}