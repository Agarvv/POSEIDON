
#include <stdio.h> 
#include <stdlib.h>     
#include <string.h>     
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>
#include <pthread.h>
#include <sys/epoll.h>


#define MAX_CLIENTS 50

struct in_addr ipv4_addr; 
in_port_t port = 8080;

struct sockaddr_in socket_addr; 
struct sockaddr_in peeraddr; 

struct ctx {
    int clients[MAX_CLIENTS];
    int index;
}; 

union http_method {
    char get[4];
    char post[5]; 
};


struct request {
    union http_method method; 
    char* route; 
    float version; 
};

struct hnd_context {
    int client_fd;
    int server_fd;
    char* data; 
}; 

struct ctx* context; 

struct epoll_event event; 

struct epoll_event events[10]; 

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
    ipv4_addr.s_addr = htonl(INADDR_ANY);

    socket_addr.sin_family = AF_INET; 
    socket_addr.sin_port = htons(atoi(getenv("PORT")));
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

void parse(char* data, struct request *req) {
    
}

void* handle(void* args) {
    
    struct hnd_context *handle_context = (struct hnd_context* )args; 
    
    printf("%s", handle_context->data); 
    fflush(stdout); 
    
    
    insert(handle_context->client_fd); 
    
    
    
    read(handle_context->client_fd, handle_context->data, 5000); 
    
    
    printf("%s", handle_context->data);
    struct request req; 
    parse(handle_context->data, &req); 
    
    
    
    
    printf("%s", handle_context->data); 
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


    write(handle_context->client_fd, res, strlen(res)); 
    
    
    drop_client(handle_context->client_fd); 
    close(handle_context->client_fd); 
}

int main() {
    
   init_ctx(); 
   int socket_fd = start_http(); 
   event.events = EPOLLIN; 
   event.data.fd = socket_fd; 
   
   
   char data[5000]; 
   memset(data, 0, sizeof(data)); 
   
   socklen_t client_len = sizeof(peeraddr); 
   struct epoll_event events[10];
   
   int e_fd = epoll_create(1); 
   if(e_fd == -1) {
       perror("epollcreate");
   }
   
   if(epoll_ctl(e_fd, EPOLL_CTL_ADD, socket_fd, &event) != 0) {
       perror("Error in epoll_ctl"); 
   }
   
   int n = epoll_wait(e_fd, events, 10, -1);
   
   for(int i = 0; i < 10; i++) {
       if(events[i].data.fd == socket_fd && events[i].events == EPOLLIN) {
           
        int fd = accept(socket_fd, (struct sockaddr*)&peeraddr, &client_len);
       
       struct hnd_context *handle_context = malloc(sizeof(struct hnd_context));
       
       handle_context->client_fd = fd; 
       handle_context->server_fd = socket_fd; 
       handle_context->data = &data[0]; 
       
       handle(handle_context); 
       }
   }
   
   while(1);
   
   
   
   
   
   
   
   
   /*
   while(1) {
       pthread_t thread; 

       
       int fd = accept(socket_fd, (struct sockaddr*)&peeraddr, &client_len);
       
       struct hnd_context *handle_context = malloc(sizeof(struct hnd_context));
       
       handle_context->client_fd = fd; 
       handle_context->server_fd = socket_fd; 
       handle_context->data = &data[0]; 
       
    
       
       pthread_create(&thread, NULL, &handle, handle_context); 
       
       //pthread_join(thread, NULL);
       //close(fd); 
   }
   */

   return 0; 
}