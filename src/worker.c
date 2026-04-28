#include<stdio.h>
#include <stdlib.h>    
#include <string.h>     
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>
#include <pthread.h>
#include <sys/epoll.h>


#include<worker.h>
#include<parse.h>
#include<main.h>


void handle(void* args) {

    struct hnd_context *handle_context = (struct hnd_context*)args;

   printf("%s", handle_context->data);
   fflush(stdout);

    insert(handle_context->client_fd);

    read(handle_context->client_fd, handle_context->data, 5000);

    printf("%s data:", handle_context->data);

    struct request req;
    parse(handle_context->data, &req);
    

    if (strncmp(req.method, "HEAD", 4) == 0) {

        char head_res[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Connection: close\r\n"
        "\r\n";

        write(handle_context->client_fd, head_res, strlen(head_res));
       // printf("%s res:", head_res);
       // fflush(stdout);
    }
    else if (strncmp(req.method, "GET", 3) == 0) {
        
    
        
        
        char res[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<!DOCTYPE html>\r\n"
        "<html>\r\n"
        "<head>\r\n"
        "  <title>Pito en C</title>\r\n"
        "</head>\r\n"
        "<body>\r\n"
        "  <h1>human</h1>\r\n"
        "</body>\r\n"
        "</html>\r\n";

        write(handle_context->client_fd, res, strlen(res));
       // printf("%s res:", res);
       // fflush(stdout);
    }

    drop_client(handle_context->client_fd);
    close(handle_context->client_fd);

}
