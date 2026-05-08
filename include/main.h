
void init_ctx(); 
int start_http();
int main();
int insert(int fd);
void drop_client(int fd); 
void worker_event_loop(int socket_fd);
void fork_workers(int socket_fd);

struct hnd_context {
    int client_fd;
    int server_fd;
    char* data; 
}; 