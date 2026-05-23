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

void handle_connection() { 
    printf("connection processing\n");
    fflush(stdout);
}
void handle_content_length() { 
    printf("content-length processing\n");
    fflush(stdout);
}
void handle_accept() { 
    printf("accept processing\n");
    fflush(stdout);
}
void handle_accept_encoding() { 
    printf("accept-encoding processing\n");
    fflush(stdout);
}
void handle_accept_language() { 
    printf("accept-language processing\n");
    fflush(stdout);
}
void handle_accept_charset() { 
    printf("accept-charset processing\n");
    fflush(stdout);
}
void handle_authorization() { 
    printf("authorization processing\n");
    fflush(stdout);
}
void handle_cache_control() { 
    printf("cache-control processing\n");
    fflush(stdout);
}
void handle_cookie() { 
    printf("cookie processing\n");
    fflush(stdout);
}
void handle_host() { 
    printf("host processing\n");
    fflush(stdout);
}
void handle_origin() { 
    printf("origin processing\n");
    fflush(stdout);
}
void handle_referer() { 
    printf("referer processing\n");
    fflush(stdout);
}
void handle_user_agent() { 
    printf("user-agent processing\n");
    fflush(stdout);
}
void handle_upgrade() { 
    printf("upgrade processing\n");
    fflush(stdout);
}
void handle_via() { 
    printf("via processing\n");
    fflush(stdout);
}
void handle_x_forwarded_for() { 
    printf("x-forwarded-for processing\n");
    fflush(stdout);
}
void handle_x_requested_with() { 
    printf("x-requested-with processing\n");
    fflush(stdout);
}
void handle_if_modified_since() { 
    printf("if-modified-since processing\n");
    fflush(stdout);
}
void handle_if_none_match() { 
    printf("if-none-match processing\n");
    fflush(stdout);
}
void handle_range() { 
    printf("range processing\n");
    fflush(stdout);
}
void handle_te() { 
    printf("te processing\n");
    fflush(stdout);
}
void handle_content_type() { 
    printf("content-type processing\n");
    fflush(stdout);
}
void handle_content_encoding() { 
    printf("content-encoding processing\n");
    fflush(stdout);
}
void handle_transfer_encoding() { 
    printf("transfer-encoding processing\n");
    fflush(stdout);
}
void handle_keep_alive() { 
    printf("keep-alive processing\n");
    fflush(stdout);
}
void handle_expect() { 
    printf("expect processing\n");
    fflush(stdout);
}
void handle_pragma() { 
    printf("pragma processing\n");
    fflush(stdout);
}
void handle_warning() { 
    printf("warning processing\n");
    fflush(stdout);
}
void handle_age() { 
    printf("age processing\n");
    fflush(stdout);
}
void handle_etag() { 
    printf("etag processing\n");
    fflush(stdout);
}
void handle_location() { 
    printf("location processing\n");
    fflush(stdout);
}
void handle_server() { 
    printf("server processing\n");
    fflush(stdout);
}
void handle_set_cookie() { 
    printf("set-cookie processing\n");
    fflush(stdout);
}
void handle_x_powered_by() { 
    printf("x-powered-by processing\n");
    fflush(stdout);
}
void handle_x_frame_options() { 
    printf("x-frame-options processing\n");
    fflush(stdout);
}
void handle_x_content_type_options() { 
    printf("x-content-type-options processing\n");
    fflush(stdout);
}
void handle_x_xss_protection() { 
    printf("x-xss-protection processing\n");
    fflush(stdout);
}
void handle_strict_transport_security() { 
    printf("strict-transport-security processing\n");
    fflush(stdout);
}
void handle_content_security_policy() { 
    printf("content-security-policy processing\n");
    fflush(stdout);
}
void handle_access_control_allow_origin() { 
    printf("access-control-allow-origin processing\n");
    fflush(stdout);
}
void handle_access_control_allow_methods() { 
    printf("access-control-allow-methods processing\n");
    fflush(stdout);
}
void handle_access_control_allow_headers() { 
    printf("access-control-allow-headers processing\n");
    fflush(stdout);
}
void handle_access_control_max_age() { 
    printf("access-control-max-age processing\n");
    fflush(stdout);
}
void handle_access_control_allow_credentials() { 
    printf("access-control-allow-credentials processing\n");
    fflush(stdout);
}
void handle_dnt() { 
    printf("dnt processing\n");
    fflush(stdout);
}
void handle_sec_ch_ua() { 
    printf("sec-ch-ua processing\n");
    fflush(stdout);
}
void handle_sec_ch_ua_mobile() { 
    printf("sec-ch-ua-mobile processing\n");
    fflush(stdout);
}
void handle_sec_ch_ua_platform() { 
    printf("sec-ch-ua-platform processing\n");
    fflush(stdout);
}
void handle_sec_fetch_dest() { 
    printf("sec-fetch-dest processing\n");
    fflush(stdout);
}
void handle_sec_fetch_mode() { 
    printf("sec-fetch-mode processing\n");
    fflush(stdout);
}
void handle_sec_fetch_site() { 
    printf("sec-fetch-site processing\n");
    fflush(stdout);
}
void handle_sec_fetch_user() { 
    printf("sec-fetch-user processing\n");
    fflush(stdout);
}
void handle_last_modified() { 
    printf("last-modified processing\n");
    fflush(stdout);
}
void handle_if_match() { 
    printf("if-match processing\n");
    fflush(stdout);
}
void handle_if_range() { 
    printf("if-range processing\n");
    fflush(stdout);
}
void handle_if_unmodified_since() { 
    printf("if-unmodified-since processing\n");
    fflush(stdout);
}
void handle_accept_patch() { 
    printf("accept-patch processing\n");
    fflush(stdout);
}
void handle_accept_ranges() { 
    printf("accept-ranges processing\n");
    fflush(stdout);
}
void handle_allow() { 
    printf("allow processing\n");
    fflush(stdout);
}
void handle_alt_svc() { 
    printf("alt-svc processing\n");
    fflush(stdout);
}
void handle_date() { 
    printf("date processing\n");
    fflush(stdout);
}
void handle_retry_after() { 
    printf("retry-after processing\n");
    fflush(stdout);
}
void handle_vary() { 
    printf("vary processing\n");
    fflush(stdout);
}
void handle_www_authenticate() { 
    printf("www-authenticate processing\n");
    fflush(stdout);
}
void handle_proxy_authenticate() { 
    printf("proxy-authenticate processing\n");
    fflush(stdout);
}
void handle_proxy_authorization() { 
    printf("proxy-authorization processing\n");
    fflush(stdout);
}
void handle_from() { 
    printf("from processing\n");
    fflush(stdout);
}
void handle_max_forwards() { 
    printf("max-forwards processing\n");
    fflush(stdout);
}
void handle_priority() { 
    printf("priority processing\n");
    fflush(stdout);
}
void handle_tk() { 
    printf("tk processing\n");
    fflush(stdout);
}
void handle_x_cache() { 
    printf("x-cache processing\n");
    fflush(stdout);
}
void handle_x_cache_hits() { 
    printf("x-cache-hits processing\n");
    fflush(stdout);
}
void handle_x_ua_compatible() { 
    printf("x-ua-compatible processing\n");
    fflush(stdout);
}
void handle_x_csrf_token() { 
    printf("x-csrf-token processing\n");
    fflush(stdout);
}
void handle_x_idempotency_key() { 
    printf("x-idempotency-key processing\n");
    fflush(stdout);
}
void handle_x_rate_limit_limit() { 
    printf("x-rate-limit-limit processing\n");
    fflush(stdout);
}
void handle_x_rate_limit_remaining() { 
    printf("x-rate-limit-remaining processing\n");
    fflush(stdout);
}
void handle_x_rate_limit_reset() { 
    printf("x-rate-limit-reset processing\n");
    fflush(stdout);
}
void handle_x_total_count() { 
    printf("x-total-count processing\n");
    fflush(stdout);
}
void handle_clear_site_data() { 
    printf("clear-site-data processing\n");
    fflush(stdout);
}
void handle_cross_origin_embedder_policy() { 
    printf("cross-origin-embedder-policy processing\n");
    fflush(stdout);
}
void handle_cross_origin_opener_policy() { 
    printf("cross-origin-opener-policy processing\n");
    fflush(stdout);
}
void handle_cross_origin_resource_policy() { 
    printf("cross-origin-resource-policy processing\n");
    fflush(stdout);
}
void handle_expect_ct() { 
    printf("expect-ct processing\n");
    fflush(stdout);
}
void handle_feature_policy() { 
    printf("feature-policy processing\n");
    fflush(stdout);
}
void handle_nela() { 
    printf("nela processing\n");
    fflush(stdout);
}
void handle_report_to() { 
    printf("report-to processing\n");
    fflush(stdout);
}
void handle_sourcemap() { 
    printf("sourcemap processing\n");
    fflush(stdout);
}
void handle_x_dns_prefetch_control() { 
    printf("x-dns-prefetch-control processing\n");
    fflush(stdout);
}
void handle_x_download_options() { 
    printf("x-download-options processing\n");
    fflush(stdout);
}
void handle_x_permitted_cross_domain_policies() { 
    printf("x-permitted-cross-domain-policies processing\n");
    fflush(stdout);
}
void handle_x_redirect_by() { 
    printf("x-redirect-by processing\n");
    fflush(stdout);
}
void handle_x_request_id() { 
    printf("x-request-id processing\n");
    fflush(stdout);
}
void handle_x_runtime() { 
    printf("x-runtime processing\n");
    fflush(stdout);
}
void handle_x_version() { 
    printf("x-version processing\n");
    fflush(stdout);
}
void handle_x_backend_server() { 
    printf("x-backend-server processing\n");
    fflush(stdout);
}
void handle_x_forwarded_host() { 
    printf("x-forwarded-host processing\n");
    fflush(stdout);
}
void handle_x_forwarded_proto() { 
    printf("x-forwarded-proto processing\n");
    fflush(stdout);
}

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
    
    void (*f)();
    
    /*
    printf("%d\n", n);
    printf("%s\n", l);
    fflush(stdout);
    */
    
    f = htable_entries[n].f;
    f();
    
    printf("After Call\n");
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


