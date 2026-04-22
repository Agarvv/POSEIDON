#include <parse.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void parse(char* data, struct request *req) {
    
    char* l = strstr("\r\n", data); 
    
    char* req_l = malloc((l - data) + 2); 
    
    printf("%d", l - data);
    printf("l\n");
    fflush(stdout);
    
    memcpy(req_l, data, l - data);
    

    req_l[(l - data) + 1] = '/0'; 
}

