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
#include<websocket.h>




void handle(void* args) {
    int upgrade = 0;
    char* sec_ws_key;

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
        
    
        for(int i = 0; i < req.header_n; i++) {
            
            if(upgrade ==  1 && strncmp("Upgrade", req.headers[i].key, 7) == 0) {
                if(strncmp(req.headers[i].value, "websocket", 9) == 0) {
                    printf("\n WS \n");
                    
                    for(int p = 0; p < req.header_n; p++) {
                        if(strncmp(req.headers[p].key, "Sec-WebSocket-Key", 17) == 0) {
                            printf("\n pen\n");
                            printf("\n %s \n", req.headers[p].value); 
                            fflush(stdout);
                            sec_ws_key = req.headers[p].value;
                        
                        }else {
                            printf("\n Pollaaa\n");
                        }
                    }
                    
                   char* ws_s_key =  ws_handshake(sec_ws_key);
                  
                   write(handle_context->client_fd,
"HTTP/1.1 101 Switching Protocols\r\n"
"Upgrade: websocket\r\n"
"Connection: Upgrade\r\n"
"Sec-WebSocket-Accept: ", 97);

fflush(stdout);
write(handle_context->client_fd, ws_s_key, strlen(ws_s_key));

write(handle_context->client_fd,
"\r\n\r\n", 4);
close(handle_context->client_fd);
                    
                }
            }
            
            
            
             if(strncmp(req.headers[i].key, "Connection", 10) == 0) {
                
                printf("\n OK 1\n");
                fflush(stdout);
                
                if(strncmp(req.headers[i].value, "Upgrade", 7) == 0) {
                    
                    printf("\n OK 2\n");
                    fflush(stdout);
                    
                     
                    upgrade = 1; 
                }
                
                
            }
            
          
        }
        
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
