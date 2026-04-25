

struct request {
    char method[5]; //limited protocol scope... for now
    char* path; 
    char version[10];
    
    char* body;
};



int parse(char* data, struct request *req);