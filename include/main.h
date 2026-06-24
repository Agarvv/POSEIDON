#define MAX_CLIENTS 50
#define HSIZE 100
#define PPROTOCOL_HTTP11 1 
#define PPROTOCOL_WS 2

void init_ctx(); 
int start_http();
int main();
int insert(int fd);
void drop_client(int fd); 
void worker_event_loop(int socket_fd);
void fork_workers(int socket_fd);
int phhash_djb2(char* arg);
void http_hhtable_init();
void htable_insert(char* s, char* (*f)(), char* d);
void route(int method, char* path);
struct pbuffer_chain_node* init_routes();

struct htable {
    char* hname;
    char* (*f)();
    //void (*d)(); 
    char* d; // used when dependencies between headers
    char* dv; 
    int r; 
};

extern struct htable htable_entries[2 * HSIZE];

struct client {
    int protocol;
};

struct ctx {
    struct client clients[MAX_CLIENTS];
    int index;
}; 



struct hnd_context {
    int client_fd;
    int server_fd;
    char* data; 
    struct client* cl;
}; 