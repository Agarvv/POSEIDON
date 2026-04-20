

struct hnd_context {
    int client_fd;
    int server_fd;
    char* data; 
}; 

void handle(void* args);