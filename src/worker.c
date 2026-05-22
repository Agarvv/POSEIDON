#include<stdio.h>
#include <stdlib.h>    
#include <string.h>     
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>
#include <pthread.h>
#include <sys/epoll.h>
#include<worker.h>
#include<parse.h>
#include<main.h>
#include<websocket.h>
#include<palloc.h>
#include<ctype.h>

void handle_connection() { }
void handle_content_length() { }
void handle_accept() { }
void handle_accept_encoding() { }
void handle_accept_language() { }
void handle_accept_charset() { }
void handle_authorization() { }
void handle_cache_control() { }
void handle_cookie() { }
void handle_host() { }
void handle_origin() { }
void handle_referer() { }
void handle_user_agent() { }
void handle_upgrade() { }
void handle_via() { }
void handle_x_forwarded_for() { }
void handle_x_requested_with() { }
void handle_if_modified_since() { }
void handle_if_none_match() { }
void handle_range() { }
void handle_te() { }
void handle_content_type() { }
void handle_content_encoding() { }
void handle_transfer_encoding() { }
void handle_keep_alive() { }
void handle_expect() { }
void handle_pragma() { }
void handle_warning() { }
void handle_age() { }
void handle_etag() { }
void handle_location() { }
void handle_server() { }
void handle_set_cookie() { }
void handle_x_powered_by() { }
void handle_x_frame_options() { }
void handle_x_content_type_options() { }
void handle_x_xss_protection() { }
void handle_strict_transport_security() { }
void handle_content_security_policy() { }
void handle_access_control_allow_origin() { }
void handle_access_control_allow_methods() { }
void handle_access_control_allow_headers() { }
void handle_access_control_max_age() { }
void handle_access_control_allow_credentials() { }
void handle_dnt() { }
void handle_sec_ch_ua() { }
void handle_sec_ch_ua_mobile() { }
void handle_sec_ch_ua_platform() { }
void handle_sec_fetch_dest() { }
void handle_sec_fetch_mode() { }
void handle_sec_fetch_site() { }
void handle_sec_fetch_user() { }
void handle_last_modified() { }
void handle_if_match() { }
void handle_if_range() { }
void handle_if_unmodified_since() { }
void handle_accept_patch() { }
void handle_accept_ranges() { }
void handle_allow() { }
void handle_alt_svc() { }
void handle_date() { }
void handle_retry_after() { }
void handle_vary() { }
void handle_www_authenticate() { }
void handle_proxy_authenticate() { }
void handle_proxy_authorization() { }
void handle_from() { }
void handle_max_forwards() { }
void handle_priority() { }
void handle_tk() { }
void handle_x_cache() { }
void handle_x_cache_hits() { }
void handle_x_ua_compatible() { }
void handle_x_csrf_token() { }
void handle_x_idempotency_key() { }
void handle_x_rate_limit_limit() { }
void handle_x_rate_limit_remaining() { }
void handle_x_rate_limit_reset() { }
void handle_x_total_count() { }
void handle_clear_site_data() { }
void handle_cross_origin_embedder_policy() { }
void handle_cross_origin_opener_policy() { }
void handle_cross_origin_resource_policy() { }
void handle_expect_ct() { }
void handle_feature_policy() { }
void handle_nela() { }
void handle_report_to() { }
void handle_sourcemap() { }
void handle_x_dns_prefetch_control() { }
void handle_x_download_options() { }
void handle_x_permitted_cross_domain_policies() { }
void handle_x_redirect_by() { }
void handle_x_request_id() { }
void handle_x_runtime() { }
void handle_x_version() { }
void handle_x_backend_server() { }
void handle_x_forwarded_host() { }
void handle_x_forwarded_proto() { }


char* toLowerS(char* s) {
    int len = strlen(s); 
    for(int i = 0; i < len; i++) {
        s[i] = tolower((unsigned char)s[i]); 
    }

    return s;
}

void process_header(struct pbuffer_chain *buffer_chain,  struct header *h) { 
    
    char* l = toLowerS(h->key);
    
    
    int n = phhash_djb2(l);
    
    
    printf("%d\n", n);
    printf("%s\n", l);
    fflush(stdout);
}


void handle(void* args) {
    struct parena *arena; 
    pinit(arena); 
    char* data = palloc(5000, arena); 

    int upgrade = 0;
    char* sec_ws_key;
    struct pbuffer_chain res_buffer_chain;
    struct pbuffer_chain_node node; 
    node.size = 5000;
    
    node.p = palloc(5000, arena); 
    node.next = NULL;
    
    res_buffer_chain.head = &node;
    res_buffer_chain.len = 5000;

    struct hnd_context *handle_context = (struct hnd_context*)args;
    handle_context->data = data; 
    

   printf("%s", handle_context->data);
   fflush(stdout);

    insert(handle_context->client_fd);
     
    read(handle_context->client_fd, handle_context->data, 5000);

    printf("%s data:", handle_context->data);

    struct request req;
    parse(handle_context->data, &req);
    
    for(int i = 0; i < req.header_n; i++) {
        
        
        process_header(&res_buffer_chain, &req.headers[i]); 
    }
    
    /*
    if (strncmp(req.method, "HEAD", 4) == 0) {

        char head_res[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Connection: close\r\n"
        "\r\n";

        write(handle_context->client_fd, head_res, strlen(head_res));
       // printf("%s res:", head_res);
       // fflush(stdout);
    }
    else if (strncmp(req.method, "GET", 3) == 0) {
        
    
        for(int i = 0; i < req.header_n; i++) {
            
            if(upgrade ==  1 && strncmp("Upgrade", req.headers[i].key, 7) == 0) {
                if(strncmp(req.headers[i].value, "websocket", 9) == 0) {
                    printf("\n WS \n");
                    
                    for(int p = 0; p < req.header_n; p++) {
                        if(strncmp(req.headers[p].key, "Sec-WebSocket-Key", 17) == 0) {
                            printf("\n pen\n");
                            printf("\n %s \n", req.headers[p].value); 
                            fflush(stdout);
                            sec_ws_key = req.headers[p].value;
                        
                        }else {
                            printf("\n Pollaaa\n");
                        }
                    }
                    
                   char* ws_s_key =  ws_handshake(sec_ws_key);
                  
                   write(handle_context->client_fd,
"HTTP/1.1 101 Switching Protocols\r\n"
"Upgrade: websocket\r\n"
"Connection: Upgrade\r\n"
"Sec-WebSocket-Accept: ", 97);

fflush(stdout);
write(handle_context->client_fd, ws_s_key, strlen(ws_s_key));

write(handle_context->client_fd,
"\r\n\r\n", 4);

                    
                }
            }
            
            
            
             if(strncmp(req.headers[i].key, "Connection", 10) == 0) {
                
                printf("\n OK 1\n");
                fflush(stdout);
                
                if(strncmp(req.headers[i].value, "Upgrade", 7) == 0) {
                    
                    printf("\n OK 2\n");
                    fflush(stdout);
                    
                     
                    upgrade = 1; 
                }
                
                
            }
            
          
        }
        
        
        */
        
        
        
        
        
        
        
        /*
        char res[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<!DOCTYPE html>\r\n"
        "<html>\r\n"
        "<head>\r\n"
        "  <title>Pito en C</title>\r\n"
        "</head>\r\n"
        "<body>\r\n"
        "  <h1>human</h1>\r\n"
        "</body>\r\n"
        "</html>\r\n";
        

        write(handle_context->client_fd, res, strlen(res));
        */
       // printf("%s res:", res);
       // fflush(stdout);
    }

    ///drop_client(handle_context->client_fd);
    // close(handle_context->client_fd);


