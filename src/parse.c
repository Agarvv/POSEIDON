#include <parse.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int parse_header(char* li, struct request *req, int index) {
    if(li == NULL) {
        printf("Error\n"); 
    }
    
    char* k = strchr(li, ':'); 
    
    
    if(k == NULL) {
        printf("Error parse 1\n");
        return -1; 
    }
    
    //printf("%s", (li - k)); 
    
    char* key = malloc((k - li) + 2); 

    if(key == NULL) {
        perror("error in malloc");
        return -1; 
    }
    
    
    key[(li - k) + 1] = '\0'; 
    memcpy(key, li, (k - li)); 
    req->headers[index].key = key; 
    
    char* v = strstr(li, "\r\n"); 
    
    if(v == NULL) {
        printf("Error parse 3\n");
        return -1; 
    }
    
    
    char* value = malloc((k - v) + 2);
    
    if(value == NULL) {
        perror("error in malloc 2");
        return -1; 
    }
    
    value[(v - k) + 1] = '\0'; 
    memcpy(value, k + 2, (k - v)); 
    req->headers[index].value = value; 
    
    printf("%s", req->headers[index].value);
    printf("\n That was the Header Value\n"); 
    
    printf("%s", req->headers[index].key);
    printf("\n That was the Header Key\n"); 
    
    
    return 0; 
}

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
    char* li; 

    for(int i = 0; i < MAX_H; i++) {
      char* line = strstr(end_of_req_line, "\r\n");
      
     
      parse_header(line, req, i); 
      printf("%s", "parsing header\n");
    
      while(1);
    }
    
    return 0;
}

