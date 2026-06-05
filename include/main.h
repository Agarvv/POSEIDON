#define MAX_CLIENTS 50
#define HSIZE 100

void init_ctx(); 
int start_http();
int main();
int insert(int fd);
void drop_client(int fd); 
void worker_event_loop(int socket_fd);
void fork_workers(int socket_fd);
int phhash_djb2(char* arg);
void http_hhtable_init();
void htable_insert(char* s, int (*f)(), char* d);

struct htable {
    char* hname;
    int (*f)();
    //void (*d)(); 
    char* d; // used when dependencies between headers
    int r; 
};

extern struct htable htable_entries[2 * HSIZE];

struct hnd_context {
    int client_fd;
    int server_fd;
    char* data; 
}; 