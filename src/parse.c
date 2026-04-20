#include <parse.h>
#include<stdio.h>

void parse(char* data, struct request *req) {
    sscanf(data, "%s", req->method);
}

