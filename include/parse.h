

struct request_line {
    char method[5]; //limited protocol scope... for now
    char* path; 
    char version[8];
};

struct http_headers {
    
};

struct request {
    struct request_line req_line; 
    struct http_headers headers; 
    char* body;
};



int parse(char* data, struct request *req);