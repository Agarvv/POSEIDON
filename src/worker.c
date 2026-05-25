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

void handle_host(void)
{
    printf("processing host\n");
    fflush(stdout);
}

void handle_connection(void)
{
    printf("processing connection\n");
    fflush(stdout);
}

void handle_content_length(void)
{
    printf("processing content-length\n");
    fflush(stdout);
}

void handle_content_type(void)
{
    printf("processing content-type\n");
    fflush(stdout);
}

void handle_user_agent(void)
{
    printf("processing user-agent\n");
    fflush(stdout);
}

void handle_accept(void)
{
    printf("processing accept\n");
    fflush(stdout);
}

void handle_accept_encoding(void)
{
    printf("processing accept-encoding\n");
    fflush(stdout);
}

void handle_accept_language(void)
{
    printf("processing accept-language\n");
    fflush(stdout);
}

void handle_accept_charset(void)
{
    printf("processing accept-charset\n");
    fflush(stdout);
}

void handle_upgrade(void)
{
    printf("processing upgrade\n");
    fflush(stdout);
}

void handle_upgrade_insecure_requests(void)
{
    printf("processing upgrade-insecure-requests\n");
    fflush(stdout);
}

void handle_websocket_key(void)
{
    printf("processing sec-websocket-key\n");
    fflush(stdout);
}

void handle_websocket_version(void)
{
    printf("processing sec-websocket-version\n");
    fflush(stdout);
}

void handle_websocket_protocol(void)
{
    printf("processing sec-websocket-protocol\n");
    fflush(stdout);
}

void handle_websocket_extensions(void)
{
    printf("processing sec-websocket-extensions\n");
    fflush(stdout);
}

void handle_origin(void)
{
    printf("processing origin\n");
    fflush(stdout);
}

void handle_access_control_allow_origin(void)
{
    printf("processing access-control-allow-origin\n");
    fflush(stdout);
}

void handle_access_control_allow_methods(void)
{
    printf("processing access-control-allow-methods\n");
    fflush(stdout);
}

void handle_access_control_allow_headers(void)
{
    printf("processing access-control-allow-headers\n");
    fflush(stdout);
}

void handle_access_control_max_age(void)
{
    printf("processing access-control-max-age\n");
    fflush(stdout);
}

void handle_access_control_allow_credentials(void)
{
    printf("processing access-control-allow-credentials\n");
    fflush(stdout);
}

void handle_cors_preflight(void)
{
    printf("processing cors-preflight\n");
    fflush(stdout);
}

void handle_sec_fetch_dest(void)
{
    printf("processing sec-fetch-dest\n");
    fflush(stdout);
}

void handle_sec_fetch_mode(void)
{
    printf("processing sec-fetch-mode\n");
    fflush(stdout);
}

void handle_sec_fetch_site(void)
{
    printf("processing sec-fetch-site\n");
    fflush(stdout);
}

void handle_sec_fetch_user(void)
{
    printf("processing sec-fetch-user\n");
    fflush(stdout);
}

void handle_cache_control(void)
{
    printf("processing cache-control\n");
    fflush(stdout);
}

void handle_if_modified_since(void)
{
    printf("processing if-modified-since\n");
    fflush(stdout);
}

void handle_if_none_match(void)
{
    printf("processing if-none-match\n");
    fflush(stdout);
}

void handle_if_match(void)
{
    printf("processing if-match\n");
    fflush(stdout);
}

void handle_if_unmodified_since(void)
{
    printf("processing if-unmodified-since\n");
    fflush(stdout);
}

void handle_if_range(void)
{
    printf("processing if-range\n");
    fflush(stdout);
}

void handle_etag(void)
{
    printf("processing etag\n");
    fflush(stdout);
}

void handle_pragma(void)
{
    printf("processing pragma\n");
    fflush(stdout);
}

void handle_authorization(void)
{
    printf("processing authorization\n");
    fflush(stdout);
}

void handle_cookie(void)
{
    printf("processing cookie\n");
    fflush(stdout);
}

void handle_set_cookie(void)
{
    printf("processing set-cookie\n");
    fflush(stdout);
}

void handle_referer(void)
{
    printf("processing referer\n");
    fflush(stdout);
}

void handle_dnt(void)
{
    printf("processing dnt\n");
    fflush(stdout);
}

void handle_sec_ch_ua(void)
{
    printf("processing sec-ch-ua\n");
    fflush(stdout);
}

void handle_sec_ch_ua_mobile(void)
{
    printf("processing sec-ch-ua-mobile\n");
    fflush(stdout);
}

void handle_sec_ch_ua_platform(void)
{
    printf("processing sec-ch-ua-platform\n");
    fflush(stdout);
}

void handle_content_encoding(void)
{
    printf("processing content-encoding\n");
    fflush(stdout);
}

void handle_transfer_encoding(void)
{
    printf("processing transfer-encoding\n");
    fflush(stdout);
}

void handle_te(void)
{
    printf("processing te\n");
    fflush(stdout);
}

void handle_accept_ranges(void)
{
    printf("processing accept-ranges\n");
    fflush(stdout);
}

void handle_range(void)
{
    printf("processing range\n");
    fflush(stdout);
}

void handle_last_modified(void)
{
    printf("processing last-modified\n");
    fflush(stdout);
}

void handle_location(void)
{
    printf("processing location\n");
    fflush(stdout);
}

void handle_server(void)
{
    printf("processing server\n");
    fflush(stdout);
}

void handle_www_authenticate(void)
{
    printf("processing www-authenticate\n");
    fflush(stdout);
}

void handle_proxy_authenticate(void)
{
    printf("processing proxy-authenticate\n");
    fflush(stdout);
}

void handle_proxy_authorization(void)
{
    printf("processing proxy-authorization\n");
    fflush(stdout);
}

void handle_keep_alive(void)
{
    printf("processing keep-alive\n");
    fflush(stdout);
}

void handle_expect(void)
{
    printf("processing expect\n");
    fflush(stdout);
}

void handle_max_forwards(void)
{
    printf("processing max-forwards\n");
    fflush(stdout);
}

void handle_vary(void)
{
    printf("processing vary\n");
    fflush(stdout);
}

void handle_retry_after(void)
{
    printf("processing retry-after\n");
    fflush(stdout);
}

void handle_date(void)
{
    printf("processing date\n");
    fflush(stdout);
}

void handle_strict_transport_security(void)
{
    printf("processing strict-transport-security\n");
    fflush(stdout);
}

void handle_content_security_policy(void)
{
    printf("processing content-security-policy\n");
    fflush(stdout);
}

void handle_x_frame_options(void)
{
    printf("processing x-frame-options\n");
    fflush(stdout);
}

void handle_x_content_type_options(void)
{
    printf("processing x-content-type-options\n");
    fflush(stdout);
}

void handle_x_xss_protection(void)
{
    printf("processing x-xss-protection\n");
    fflush(stdout);
}

void handle_x_powered_by(void)
{
    printf("processing x-powered-by\n");
    fflush(stdout);
}

void handle_x_requested_with(void)
{
    printf("processing x-requested-with\n");
    fflush(stdout);
}

void handle_x_forwarded_for(void)
{
    printf("processing x-forwarded-for\n");
    fflush(stdout);
}

void handle_x_forwarded_host(void)
{
    printf("processing x-forwarded-host\n");
    fflush(stdout);
}

void handle_x_forwarded_proto(void)
{
    printf("processing x-forwarded-proto\n");
    fflush(stdout);
}

void handle_x_csrf_token(void)
{
    printf("processing x-csrf-token\n");
    fflush(stdout);
}

void handle_x_idempotency_key(void)
{
    printf("processing x-idempotency-key\n");
    fflush(stdout);
}

void handle_x_rate_limit_limit(void)
{
    printf("processing x-rate-limit-limit\n");
    fflush(stdout);
}

void handle_x_rate_limit_remaining(void)
{
    printf("processing x-rate-limit-remaining\n");
    fflush(stdout);
}

void handle_x_rate_limit_reset(void)
{
    printf("processing x-rate-limit-reset\n");
    fflush(stdout);
}

void handle_early_data(void)
{
    printf("processing early-data\n");
    fflush(stdout);
}

void handle_sec_gpc(void)
{
    printf("processing sec-gpc\n");
    fflush(stdout);
}

void handle_save_data(void)
{
    printf("processing save-data\n");
    fflush(stdout);
}

void handle_viewport_width(void)
{
    printf("processing viewport-width\n");
    fflush(stdout);
}

void handle_device_memory(void)
{
    printf("processing device-memory\n");
    fflush(stdout);
}

void handle_downlink(void)
{
    printf("processing downlink\n");
    fflush(stdout);
}

void handle_ect(void)
{
    printf("processing ect\n");
    fflush(stdout);
}

void handle_rtt(void)
{
    printf("processing rtt\n");
    fflush(stdout);
}

void handle_sec_ch_prefers_color_scheme(void)
{
    printf("processing sec-ch-prefers-color-scheme\n");
    fflush(stdout);
}

void handle_sec_ch_prefers_reduced_motion(void)
{
    printf("processing sec-ch-prefers-reduced-motion\n");
    fflush(stdout);
}

void handle_sec_ch_prefers_reduced_data(void)
{
    printf("processing sec-ch-prefers-reduced-data\n");
    fflush(stdout);
}

void handle_sec_ch_ua_arch(void)
{
    printf("processing sec-ch-ua-arch\n");
    fflush(stdout);
}

void handle_sec_ch_ua_model(void)
{
    printf("processing sec-ch-ua-model\n");
    fflush(stdout);
}

void handle_sec_ch_ua_bitness(void)
{
    printf("processing sec-ch-ua-bitness\n");
    fflush(stdout);
}

void handle_sec_ch_ua_full_version(void)
{
    printf("processing sec-ch-ua-full-version\n");
    fflush(stdout);
}

void handle_sec_ch_ua_full_version_list(void)
{
    printf("processing sec-ch-ua-full-version-list\n");
    fflush(stdout);
}

void handle_sec_ch_ua_wow64(void)
{
    printf("processing sec-ch-ua-wow64\n");
    fflush(stdout);
}

void handle_x_client_data(void)
{
    printf("processing x-client-data\n");
    fflush(stdout);
}

void handle_x_forwarded_port(void)
{
    printf("processing x-forwarded-port\n");
    fflush(stdout);
}

void handle_x_original_forwarded_for(void)
{
    printf("processing x-original-forwarded-for\n");
    fflush(stdout);
}

void handle_x_proxy_user_ip(void)
{
    printf("processing x-proxy-user-ip\n");
    fflush(stdout);
}

void handle_x_real_ip(void)
{
    printf("processing x-real-ip\n");
    fflush(stdout);
}

void handle_x_uid(void)
{
    printf("processing x-uid\n");
    fflush(stdout);
}

void handle_x_wap_profile(void)
{
    printf("processing x-wap-profile\n");
    fflush(stdout);
}

void handle_x_device_user_agent(void)
{
    printf("processing x-device-user-agent\n");
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
    
    void (*f)();
    char* l = toLowerS(h->key);
    
    
    int n = phhash_djb2(l);
    
    int len = strlen(l); 
     
     
    while(strncmp(l, htable_entries[n].hname, len) != 0) {
        n++;
        
        if(n >= 200) {
            n = 0;
        }
    }
    
    printf("%s\n", htable_entries[n].hname);
    fflush(stdout);
    

    
    f = htable_entries[n].f;
    f();

    
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


