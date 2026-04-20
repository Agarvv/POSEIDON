

struct request {
    char method[5]; 
    char route[64]; 
    char version[32]; 
};



void parse(char* data, struct request *req);