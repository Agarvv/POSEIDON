
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

struct ctx {
    int clients[MAX_CLIENTS];
    int index;
}; 

struct ctx* context; 

struct epoll_event event; 

struct epoll_event events[10];

struct htable htable_entries[2 * HSIZE] = {
    {"connection", handle_connection},
    {"content-length", handle_content_length},
    {"accept", handle_accept},
    {"accept-encoding", handle_accept_encoding},
    {"accept-language", handle_accept_language},
    {"accept-charset", handle_accept_charset},
    {"authorization", handle_authorization},
    {"cache-control", handle_cache_control},
    {"cookie", handle_cookie},
    {"host", handle_host},
    {"origin", handle_origin},
    {"referer", handle_referer},
    {"user-agent", handle_user_agent},
    {"upgrade", handle_upgrade},
    {"via", handle_via},
    {"x-forwarded-for", handle_x_forwarded_for},
    {"x-requested-with", handle_x_requested_with},
    {"if-modified-since", handle_if_modified_since},
    {"if-none-match", handle_if_none_match},
    {"range", handle_range},
    {"te", handle_te},
    {"content-type", handle_content_type},
    {"content-encoding", handle_content_encoding},
    {"transfer-encoding", handle_transfer_encoding},
    {"keep-alive", handle_keep_alive},
    {"expect", handle_expect},
    
    {"pragma", handle_pragma},
    
    {"warning", handle_warning},
    {"age", handle_age},
    {"etag", handle_etag},
    {"location", handle_location},
    {"server", handle_server},
    {"set-cookie", handle_set_cookie},
    {"x-powered-by", handle_x_powered_by},
    {"x-frame-options", handle_x_frame_options},
    {"x-content-type-options", handle_x_content_type_options},
    {"x-xss-protection", handle_x_xss_protection},
    {"strict-transport-security", handle_strict_transport_security},
    {"content-security-policy", handle_content_security_policy},
    {"access-control-allow-origin", handle_access_control_allow_origin},
    {"access-control-allow-methods", handle_access_control_allow_methods},
    {"access-control-allow-headers", handle_access_control_allow_headers},
    {"access-control-max-age", handle_access_control_max_age},
    {"access-control-allow-credentials", handle_access_control_allow_credentials},
    {"dnt", handle_dnt},
    {"sec-ch-ua", handle_sec_ch_ua},
    {"sec-ch-ua-mobile", handle_sec_ch_ua_mobile},
    {"sec-ch-ua-platform", handle_sec_ch_ua_platform},
    {"sec-fetch-dest", handle_sec_fetch_dest},
    {"sec-fetch-mode", handle_sec_fetch_mode},
    {"sec-fetch-site", handle_sec_fetch_site},
    {"sec-fetch-user", handle_sec_fetch_user},
    {"last-modified", handle_last_modified},
    {"if-match", handle_if_match},
    {"if-range", handle_if_range},
    {"if-unmodified-since", handle_if_unmodified_since},
    {"accept-patch", handle_accept_patch},
    {"accept-ranges", handle_accept_ranges},
    {"allow", handle_allow},
    {"alt-svc", handle_alt_svc},
    {"date", handle_date},
    {"retry-after", handle_retry_after},
    {"vary", handle_vary},
    {"www-authenticate", handle_www_authenticate},
    {"proxy-authenticate", handle_proxy_authenticate},
    {"proxy-authorization", handle_proxy_authorization},
    {"from", handle_from},
    {"max-forwards", handle_max_forwards},
    {"priority", handle_priority},
    {"tk", handle_tk},
    {"x-cache", handle_x_cache},
    {"x-cache-hits", handle_x_cache_hits},
    {"x-ua-compatible", handle_x_ua_compatible},
    {"x-csrf-token", handle_x_csrf_token},
    {"x-idempotency-key", handle_x_idempotency_key},
    {"x-rate-limit-limit", handle_x_rate_limit_limit},
    {"x-rate-limit-remaining", handle_x_rate_limit_remaining},
    {"x-rate-limit-reset", handle_x_rate_limit_reset},
    {"x-total-count", handle_x_total_count},
    {"clear-site-data", handle_clear_site_data},
    {"cross-origin-embedder-policy", handle_cross_origin_embedder_policy},
    {"cross-origin-opener-policy", handle_cross_origin_opener_policy},
    {"cross-origin-resource-policy", handle_cross_origin_resource_policy},
    {"expect-ct", handle_expect_ct},
    {"feature-policy", handle_feature_policy},
    {"nela", handle_nela},
    {"report-to", handle_report_to},
    {"sourcemap", handle_sourcemap},
    {"x-dns-prefetch-control", handle_x_dns_prefetch_control},
    {"x-download-options", handle_x_download_options},
    {"x-permitted-cross-domain-policies", handle_x_permitted_cross_domain_policies},
    {"x-redirect-by", handle_x_redirect_by},
    {"x-request-id", handle_x_request_id},
    {"x-runtime", handle_x_runtime},
    {"x-version", handle_x_version},
    {"x-backend-server", handle_x_backend_server},
    {"x-forwarded-host", handle_x_forwarded_host},
    {"x-forwarded-proto", handle_x_forwarded_proto}
};


int phhash_djb2(char* str) {
    
    unsigned int hash = 2166136261u;
    
    while (*str) {
        hash ^= (unsigned char)*str;
        hash *= 16777619u;
        str++;
    }
    
    return (hash % HSIZE) + HSIZE;
}

void htable_insert(char* s, void (*f)()) {
    int n = phhash_djb2(s);
    
    while(htable_entries[n].f != NULL) {
        n++;
    }
    printf("%d\n", n);
    fflush(stdout);
    htable_entries[n].f = f;
}

void http_hhtable_init() {
    
  for(int i = 0; i < 2 * HSIZE; i++) {
        htable_entries[i].f = NULL;
  }

  for(int i = 0; i < 98; i++) {
 
   htable_insert(htable_entries[i].hname, htable_entries[i].f); 
  
  }
  
}

void init_ctx() {
    context = malloc(sizeof(struct ctx));
    context->index = 0; 
}

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
    
    //printf("polla enorme\n");
  // fflush(stdout);


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
   int n = epoll_wait(e_fd, events, 10, -1);
   
   for(int i = 0; i < 10; i++) {
       if(events[i].data.fd == socket_fd && events[i].events == EPOLLIN) {
           
    fflush(stdout); 
        int fd = accept(socket_fd, (struct sockaddr*)&peeraddr, &client_len);
       
       struct hnd_context *handle_context = malloc(sizeof(struct hnd_context));
       
       handle_context->client_fd = fd; 
       handle_context->server_fd = socket_fd; 
       //handle_context->data = &data[0]; 
       printf("Hola\n");
       handle(handle_context); 
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
  
   fork_workers(socket_fd);
   
   while(1);
   return 0; 
}