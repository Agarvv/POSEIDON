
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
#include<parse.h>
#include<worker.h>
#include<main.h>
#include<palloc.h>
#define HSIZE 2
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

struct epoll_event event; 

struct epoll_event events[10];

struct htable htable_entries[2 * HSIZE] = {
    {"connection", handle_connection},
    {"content-length", handle_content_length}
};

int phhash_djb2(char* arg, int index) {
    unsigned long hash = 5381;
    int c = 0;
    
    for(int i = 0; i < strlen(arg); i++) {
        printf("%d\n", strlen(arg));
        fflush(stdout);

        c = *arg;
    
        arg = arg + 1;
        
        hash = ((hash << 5) + hash) + c; 

    }
    
    
    return (hash % HSIZE) + HSIZE;
}

void http_hhtable_init() {
  for(int i = 0; i < HSIZE; i++) {
   int n = phhash_djb2(htable_entries[i].hname, i); 

   // htable_entries[n].f = htable_entries[i].f;
  }
  while(1);
}

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
    int port = 8080;
    char* env_p = getenv("PORT"); 
    if(env_p != NULL) {
        printf("PORT OK"); 
        fflush(stdout);
        port = atoi(env_p);
    }
    
    socket_addr.sin_port = htons(port); 
    socket_addr.sin_addr = ipv4_addr;
    
    //printf("polla enorme\n");
  // fflush(stdout);


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

void fork_workers(int socket_fd) {
    for(int i = 0; i < 8; i++){
       int pid = fork(); 
       if(pid == 0) {
           worker_event_loop(socket_fd); 
       }
   }
}

void worker_event_loop(int socket_fd) {

   
   socklen_t client_len = sizeof(peeraddr); 
   struct epoll_event events[10];
   
   
   int e_fd = epoll_create(1); 
   if(e_fd == -1) {
       perror("epollcreate");
   }
   
   if(epoll_ctl(e_fd, EPOLL_CTL_ADD, socket_fd, &event) != 0) {
       perror("Error in epoll_ctl"); 
   }
   
   while(1) {
   int n = epoll_wait(e_fd, events, 10, -1);
   
   for(int i = 0; i < 10; i++) {
       if(events[i].data.fd == socket_fd && events[i].events == EPOLLIN) {
           
    fflush(stdout); 
        int fd = accept(socket_fd, (struct sockaddr*)&peeraddr, &client_len);
       
       struct hnd_context *handle_context = malloc(sizeof(struct hnd_context));
       
       handle_context->client_fd = fd; 
       handle_context->server_fd = socket_fd; 
       //handle_context->data = &data[0]; 
       printf("Hola\n");
       handle(handle_context); 
       }
   }
   }
   
   while(1);
}


int main() {
    
   init_ctx(); 
   int socket_fd = start_http(); 
   
   event.events = EPOLLIN; 
   event.data.fd = socket_fd; 
   
   http_hhtable_init();
   while(1);
   fork_workers(socket_fd);
   
   while(1);
   return 0; 
}