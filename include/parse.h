#define MAX_H

struct request {
    char method[5]; //limited protocol scope... for now
    char* path; 
    char version[10];
    char* body;
    struct header headers[MAX_H];
};

struct header {
    char* key;
    char* value;
};

int parse(char* data, struct request *req);