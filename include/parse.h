#define MAX_H 100


struct header {
    char* key;
    char* value;
};


struct request {
    char method[5]; //limited protocol scope... for now
    char* path; 
    char version[10];
    char* body;
    struct header headers[MAX_H];
};


int parse(char* data, struct request *req);
int parse_header(char* li, struct request *req, int index); 