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
    

    req_l[(l - data) + 1] = '/0'; 
    printf("%s", req_l);
    printf("%s", "\n THAT WAS REQ LINE\n");
    fflush(stdout);
    
    return 0;
}

