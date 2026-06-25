
#include <stdio.h> 
#include <stdlib.h>     
#include <string.h>     
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>
#include <pthread.h>
#include <sys/epoll.h>
#include<parse.h>
#include<worker.h>
#include<main.h>
#include<palloc.h>


struct in_addr ipv4_addr; 
in_port_t port = 8080;

struct sockaddr_in socket_addr; 
struct sockaddr_in peeraddr; 

struct ctx* context; 

struct epoll_event event; 

struct epoll_event events[10];

struct pbuffer_chain routes_buffer_chain;
struct parena routes_arena;

struct patricia_tree ptree_routes;

struct htable htable_entries[2 * HSIZE] = {
    {"host", handle_host},
    {"connection", handle_connection, "upgrade"},
    {"content-length", handle_content_length},
    {"content-type", handle_content_type},
    {"user-agent", handle_user_agent},
    {"accept", handle_accept},
    {"accept-encoding", handle_accept_encoding},
    {"accept-language", handle_accept_language},
    {"accept-charset", handle_accept_charset},
    {"upgrade", handle_upgrade, "connection"},
    {"upgrade-insecure-requests", handle_upgrade_insecure_requests},
    {"sec-websocket-key", handle_websocket_key},
    {"sec-websocket-version", handle_websocket_version},
    {"sec-websocket-protocol", handle_websocket_protocol},
    {"sec-websocket-extensions", handle_websocket_extensions},
    {"origin", handle_origin},
    {"access-control-allow-origin", handle_access_control_allow_origin},
    {"access-control-allow-methods", handle_access_control_allow_methods},
    {"access-control-allow-headers", handle_access_control_allow_headers},
    {"access-control-max-age", handle_access_control_max_age},
    {"access-control-allow-credentials", handle_access_control_allow_credentials},
    {"access-control-request-method", handle_cors_preflight},
    {"access-control-request-headers", handle_cors_preflight},
    {"sec-fetch-dest", handle_sec_fetch_dest},
    {"sec-fetch-mode", handle_sec_fetch_mode},
    {"sec-fetch-site", handle_sec_fetch_site},
    {"sec-fetch-user", handle_sec_fetch_user},
    {"cache-control", handle_cache_control},
    {"if-modified-since", handle_if_modified_since},
    {"if-none-match", handle_if_none_match},
    {"if-match", handle_if_match},
    {"if-unmodified-since", handle_if_unmodified_since},
    {"if-range", handle_if_range},
    {"etag", handle_etag},
    {"pragma", handle_pragma},
    {"authorization", handle_authorization},
    {"cookie", handle_cookie},
    {"set-cookie", handle_set_cookie},
    {"referer", handle_referer},
    {"dnt", handle_dnt},
    {"sec-ch-ua", handle_sec_ch_ua},
    {"sec-ch-ua-mobile", handle_sec_ch_ua_mobile},
    {"sec-ch-ua-platform", handle_sec_ch_ua_platform},
    {"content-encoding", handle_content_encoding},
    {"transfer-encoding", handle_transfer_encoding},
    {"te", handle_te},
    {"accept-ranges", handle_accept_ranges},
    {"range", handle_range},
    {"last-modified", handle_last_modified},
    {"location", handle_location},
    {"server", handle_server},
    {"www-authenticate", handle_www_authenticate},
    {"proxy-authenticate", handle_proxy_authenticate},
    {"proxy-authorization", handle_proxy_authorization},
    {"keep-alive", handle_keep_alive},
    {"expect", handle_expect},
    {"max-forwards", handle_max_forwards},
    {"vary", handle_vary},
    {"retry-after", handle_retry_after},
    {"date", handle_date},
    {"strict-transport-security", handle_strict_transport_security},
    {"content-security-policy", handle_content_security_policy},
    {"x-frame-options", handle_x_frame_options},
    {"x-content-type-options", handle_x_content_type_options},
    {"x-xss-protection", handle_x_xss_protection},
    {"x-powered-by", handle_x_powered_by},
    {"x-requested-with", handle_x_requested_with},
    {"x-forwarded-for", handle_x_forwarded_for},
    {"x-forwarded-host", handle_x_forwarded_host},
    {"x-forwarded-proto", handle_x_forwarded_proto},
    {"x-csrf-token", handle_x_csrf_token},
    {"x-idempotency-key", handle_x_idempotency_key},
    {"x-rate-limit-limit", handle_x_rate_limit_limit},
    {"x-rate-limit-remaining", handle_x_rate_limit_remaining},
    {"x-rate-limit-reset", handle_x_rate_limit_reset},
    {"early-data", handle_early_data},
    {"sec-gpc", handle_sec_gpc},
    {"save-data", handle_save_data},
    {"viewport-width", handle_viewport_width},
    {"device-memory", handle_device_memory},
    {"downlink", handle_downlink},
    {"ect", handle_ect},
    {"rtt", handle_rtt},
    {"sec-ch-prefers-color-scheme", handle_sec_ch_prefers_color_scheme},
    {"sec-ch-prefers-reduced-motion", handle_sec_ch_prefers_reduced_motion},
    {"sec-ch-prefers-reduced-data", handle_sec_ch_prefers_reduced_data},
    {"sec-ch-ua-arch", handle_sec_ch_ua_arch},
    {"sec-ch-ua-model", handle_sec_ch_ua_model},
    {"sec-ch-ua-bitness", handle_sec_ch_ua_bitness},
    {"sec-ch-ua-full-version", handle_sec_ch_ua_full_version},
    {"sec-ch-ua-full-version-list", handle_sec_ch_ua_full_version_list},
    {"sec-ch-ua-wow64", handle_sec_ch_ua_wow64},
    {"x-client-data", handle_x_client_data},
    {"x-forwarded-port", handle_x_forwarded_port},
    {"x-original-forwarded-for", handle_x_original_forwarded_for},
    {"x-proxy-user-ip", handle_x_proxy_user_ip},
    {"x-real-ip", handle_x_real_ip},
    {"x-uid", handle_x_uid},
    {"x-wap-profile", handle_x_wap_profile},
    {"x-device-user-agent", handle_x_device_user_agent}
};

struct pbuffer_chain_node* init_routes() {
    pinit(&routes_arena);
    
    struct pbuffer_chain_node *head = malloc(sizeof(struct pbuffer_chain_node));
    
    struct patricia_tree_node *p = malloc(4096);
    
    head->size = 4096;
    head->fsize = 4096;
    
    head->p = p;
    
    routes_buffer_chain.head = head; 
    routes_buffer_chain.tail = NULL;
    routes_buffer_chain.len = 4096;
    
    ptree_routes.root = head; 
    
   // root.p.children[a].p.children[b];
    
    return head;
}

void route(int method, char* path) {
    
}

int phhash_djb2(char* str) {
    

    unsigned int hash = 2166136261u;
    
    while (*str) {
        
        hash ^= (unsigned char)*str;
        hash *= 16777619u;
        str++;
    }
    
    
    return (hash % HSIZE) + HSIZE;
}

void htable_insert(char* s, char* (*f)(), char* d) {
    
    int n = phhash_djb2(s);
   /*  
     printf("%dC\n", n);
        fflush(stdout);
   */ 
    
    if(htable_entries[n].f == NULL) {
          htable_entries[n].f = f;
          htable_entries[n].hname = s;
          htable_entries[n].d = d; 
    
        return;
    } else {
       
        while(htable_entries[n].f != NULL) {
            n++;
            if(n == HSIZE * 2) {
                n = 0; 
            }
        }
    } 
     
    printf("%d\n", n);
        fflush(stdout);
     htable_entries[n].f = f;
     htable_entries[n].hname = s;
     htable_entries[n].d = d; 
     
}

void http_hhtable_init() {
    
  for(int i = 99; i < HSIZE; i++) {
        htable_entries[i].f = NULL;
  }

  for(int i = 0; i < 98; i++) {
     
 
   htable_insert(htable_entries[i].hname, htable_entries[i].f, htable_entries[i].d); 
  
  }
  
}

void init_ctx() {
    context = malloc(sizeof(struct ctx));
    context->index = 0; 
}

/* 
int insert(int fd) {
    int index = context->index; 
    
    if(index == (MAX_CLIENTS - 1)) {
        return -1; 
    }
    
    context->clients[context->index] = fd; 
    context->index++; 
    

    return 0;
}

void drop_client(int fd) {
    int index = 0; 
    for(int i = 0; i < MAX_CLIENTS - 1; i++) {
        if(context->clients[i] == fd) {
            index = i; 
        }
    }
    
    context->clients[index] = 0; 
    context->index--; 
}

*/

int start_http() {
    
    ipv4_addr.s_addr = htonl(INADDR_ANY);
    
    
    socket_addr.sin_family = AF_INET;
    int port = 8080;
    char* env_p = getenv("PORT"); 
    if(env_p != NULL) {
        printf("PORT OK"); 
        fflush(stdout);
        port = atoi(env_p);
    }
    
    socket_addr.sin_port = htons(port); 
    socket_addr.sin_addr = ipv4_addr;
    

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    int b = bind(socket_fd, (struct sockaddr*)&socket_addr, sizeof(socket_addr)); 
    
    if(b != 0) {
        perror("ERROR IN BIND"); 
    }
    
    if(listen(socket_fd, 100) == -1) {
	   perror("error listening");
    }
    
    return socket_fd; 
}

void fork_workers(int socket_fd) {
    for(int i = 0; i < 8; i++){
       int pid = fork(); 
       if(pid == 0) {
           worker_event_loop(socket_fd); 
       }
   }
}

void worker_event_loop(int socket_fd) {

   struct ctx pcontext; 
   
   socklen_t client_len = sizeof(peeraddr); 
   struct epoll_event events[10];
   
   
   int e_fd = epoll_create(1); 
   if(e_fd == -1) {
       perror("epollcreate");
   }
   
   if(epoll_ctl(e_fd, EPOLL_CTL_ADD, socket_fd, &event) != 0) {
       perror("Error in epoll_ctl"); 
   }
   
   while(1) {
       printf("Sleeping\n");
   int n = epoll_wait(e_fd, events, 10, -1);
   printf("Awake %d\n", n);
   
   for(int i = 0; i < n; i++) {
       if(events[i].data.fd == socket_fd && events[i].events & EPOLLIN) {
        
        struct epoll_event pevent;
        
        int fd = accept(socket_fd, (struct sockaddr*)&peeraddr, &client_len);
        
        
       
                
        pevent.events = EPOLLIN; 
        pevent.data.fd = fd; 
        
   
   
   
   
        
        
        if(epoll_ctl(e_fd, EPOLL_CTL_ADD, fd, &pevent) != 0) {
       perror("Error in epoll_ctl"); 
   }
   
        
        struct client cl; 
        cl.protocol = PPROTOCOL_HTTP11; 
        
        
        pcontext.clients[fd - 3] = cl; 
        
       
       struct hnd_context *handle_context = malloc(sizeof(struct hnd_context));
       
       handle_context->cl = &cl; 
       handle_context->client_fd = fd; 
       handle_context->server_fd = socket_fd; 
       //handle_context->data = &data[0]; 
       printf("Hola\n");
       
       handle(handle_context); 
      
       } else if(events[i].events & EPOLLIN) {
           printf("c9nnection\n");
           
           unsigned char byte[4096];
               int b = read(events[i].data.fd, byte, 4096);
               printf("jd %d\n", b);
               
           /*
           
           struct hnd_context *handle_context = malloc(sizeof(struct hnd_context));
           handle_context->client_fd = events[i].data.fd; 
           handle_context->server_fd = socket_fd;
           
           handle_context->cl = &pcontext.clients[events[i].data.fd - 3]; 
        
           
           if(handle_context->cl->protocol == PPROTOCOL_HTTP11){
               handle(handle_context);
           } else if(handle_context->cl->protocol == PPROTOCOL_WS){
              
               unsigned char byte[4096];
               int b = read(events[i].data.fd, byte, 4096);
               printf("jd %d\n", b);
               
               
               printf("Wrbsocket\n");
           } else {
               printf("oTyer\n");
           }
           
           */
       }
       
   }
   }
   
   while(1);
}


int main() {
   init_ctx(); 
   int socket_fd = start_http(); 
   
   event.events = EPOLLIN; 
   event.data.fd = socket_fd; 
   
   http_hhtable_init();
   
   route(PMETHOD_GET, "/main");
   
   fork_workers(socket_fd);
   
   while(1);
   return 0; 
}