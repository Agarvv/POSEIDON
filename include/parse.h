#ifndef PARSE_H
#define PARSE_H

#define MAX_H 100

struct header {
    char* key;
    int koffset;
    char* value;
    int voffset;
};

struct request {
    char method[5];
    char* path; 
    char version[10];
    char* body;
    struct header headers[MAX_H];
    int header_n;
};

int parse(char* data, struct request *req);
int parse_header(char* li, struct request *req, int index);

#endif