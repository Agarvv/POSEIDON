#include <parse.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int parse(char* data, struct request *req) {
    
    char* l = strstr(data, "\r\n");

    char* req_l = malloc((l - data) + 2); 
    if(req_l == NULL) {
        perror("Error in Malloc"); 
    }

    memcpy(req_l, data, l - data);
    

    req_l[(l - data) + 1] = '\0'; 
    
    /* printf("%s", req_l);
    printf("%s", "\n THAT WAS REQ LINE\n");
    fflush(stdout);
    */
    
    char method[6]; 
    method[5] = '\0'; 
    char* m = strchr(data, ' '); 
    if(m != NULL) {
        memcpy(method, data, m - data); 
        memcpy(req->method, method, sizeof(method)); 
        
        printf("%s", req->method);
        
        printf("\nThat was The Method\n"); 
        fflush(stdout); 
        
        
    } else {
        return 1;
    }
    
    char* p = strchr(m + 1, ' '); 
    char* path = malloc((p - (m + 1)) + 2);
    memcpy(path, m + 1, p - (m + 1)); 
    path[p - (m + 1)] = '\0'; 
    
    req->path = path;
    
    
    printf("%s", req->path); 
    printf("\nThat was The PATH\n"); 
    fflush(stdout); 
    
    
    
    char* v = strstr(p + 1, "\r\n"); 

    memcpy(req->version, p + 1, v - (p + 1)); 
    req->version[v - (p + 1)] = '\0';
    
    printf("%s", req->version); 
    printf("\nThat was The VERSION\n"); 
    fflush(stdout);  

    char* end_of_req_line = l + 1;

    for(int i = 0; i < MAX_H; i++) {
      char* line = strstr(end_of_req_line, "\r\n");
    }
    
    return 0;
}

