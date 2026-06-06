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
#include<normalize.h> 


int handle_host(struct header h, struct res_builder *builder)
{
    printf("processing host\n");
    fflush(stdout);
    return 0;
}

int handle_connection(struct header *h, struct res_builder *builder)
{
    printf("%s processing connection\n", h->value);
    fflush(stdout);
    
    int dh = phhash_djb2(h->value); 
    
    static int ch, uh, kh = 0; 
    
    ch = phhash_djb2("close");
    uh = phhash_djb2("upgrade");
    kh = phhash_djb2("keep-alive");
    
    if(dh == ch) {
        printf("Close Connection\n");
        fflush(stdout);
        builder->connection = PCONNECTION_CLOSE; 
    } else if (dh == uh) {
        printf("Upgrade Connection\n");
        fflush(stdout);
        builder->connection = PCONNECTION_UPGRADE; 
    } else if(dh == kh) {
        printf("Keep Alive Connection\n");
        fflush(stdout);
        builder->connection = PCONNECTION_KEEP_ALIVE; 
    } else {
        printf("Not Suported Connection\n");
        fflush(stdout);
        builder->connection = -1; 
    }
    
    return 0;
}

int handle_content_length(struct header h, struct res_builder *builder)
{
    printf("processing content-length\n");
    fflush(stdout);
    return 0;
}

int handle_content_type(struct header h, struct res_builder *builder)
{
    printf("processing content-type\n");
    fflush(stdout);
    return 0;
}

int handle_user_agent(struct header h, struct res_builder *builder)
{
    printf("processing user-agent\n");
    fflush(stdout);
    return 0;
}

int handle_accept(struct header h, struct res_builder *builder)
{
    printf("processing accept\n");
    fflush(stdout);
    return 0;
}

int handle_accept_encoding(struct header h, struct res_builder *builder)
{
    printf("processing accept-encoding\n");
    fflush(stdout);
    return 0;
}

int handle_accept_language(struct header h, struct res_builder *builder)
{
    printf("processing accept-language\n");
    fflush(stdout);
    return 0;
}

int handle_accept_charset(struct header h, struct res_builder *builder)
{
    printf("processing accept-charset\n");
    fflush(stdout);
    return 0;
}

int handle_upgrade(struct header h, struct res_builder *builder)
{
    printf("processing upgrade\n");
    fflush(stdout);
    
    // if Race Condition...
    return -1;
    
    // else, 
    // continue upgrade header processing 
    return 0;
}

int handle_upgrade_insecure_requests(struct header h, struct res_builder *builder)
{
    printf("processing upgrade-insecure-requests\n");
    fflush(stdout);
    return 0;
}

int handle_websocket_key(struct header h, struct res_builder *builder)
{
    printf("processing sec-websocket-key\n");
    fflush(stdout);
    return 0;
}

int handle_websocket_version(struct header h, struct res_builder *builder)
{
    printf("processing sec-websocket-version\n");
    fflush(stdout);
    return 0;
}

int handle_websocket_protocol(struct header h, struct res_builder *builder)
{
    printf("processing sec-websocket-protocol\n");
    fflush(stdout);
    return 0;
}

int handle_websocket_extensions(struct header h, struct res_builder *builder)
{
    printf("processing sec-websocket-extensions\n");
    fflush(stdout);
    return 0;
}

int handle_origin(struct header h, struct res_builder *builder)
{
    printf("processing origin\n");
    fflush(stdout);
    return 0;
}

int handle_access_control_allow_origin(struct header h, struct res_builder *builder)
{
    printf("processing access-control-allow-origin\n");
    fflush(stdout);
    return 0;
}

int handle_access_control_allow_methods(struct header h, struct res_builder *builder)
{
    printf("processing access-control-allow-methods\n");
    fflush(stdout);
    return 0;
}

int handle_access_control_allow_headers(struct header h, struct res_builder *builder)
{
    printf("processing access-control-allow-headers\n");
    fflush(stdout);
    return 0;
}

int handle_access_control_max_age(struct header h, struct res_builder *builder)
{
    printf("processing access-control-max-age\n");
    fflush(stdout);
    return 0;
}

int handle_access_control_allow_credentials(struct header h, struct res_builder *builder)
{
    printf("processing access-control-allow-credentials\n");
    fflush(stdout);
    return 0;
}

int handle_cors_preflight(struct header h, struct res_builder *builder)
{
    printf("processing cors-preflight\n");
    fflush(stdout);
    return 0;
}

int handle_sec_fetch_dest(struct header h, struct res_builder *builder)
{
    printf("processing sec-fetch-dest\n");
    fflush(stdout);
    return 0;
}

int handle_sec_fetch_mode(struct header h, struct res_builder *builder)
{
    printf("processing sec-fetch-mode\n");
    fflush(stdout);
    return 0;
}

int handle_sec_fetch_site(struct header h, struct res_builder *builder)
{
    printf("processing sec-fetch-site\n");
    fflush(stdout);
    return 0;
}

int handle_sec_fetch_user(struct header h, struct res_builder *builder)
{
    printf("processing sec-fetch-user\n");
    fflush(stdout);
    return 0;
}

int handle_cache_control(struct header h, struct res_builder *builder)
{
    printf("processing cache-control\n");
    fflush(stdout);
    return 0;
}

int handle_if_modified_since(struct header h, struct res_builder *builder)
{
    printf("processing if-modified-since\n");
    fflush(stdout);
    return 0;
}

int handle_if_none_match(struct header h, struct res_builder *builder)
{
    printf("processing if-none-match\n");
    fflush(stdout);
    return 0;
}

int handle_if_match(struct header h, struct res_builder *builder)
{
    printf("processing if-match\n");
    fflush(stdout);
    return 0;
}

int handle_if_unmodified_since(struct header h, struct res_builder *builder)
{
    printf("processing if-unmodified-since\n");
    fflush(stdout);
    return 0;
}

int handle_if_range(struct header h, struct res_builder *builder)
{
    printf("processing if-range\n");
    fflush(stdout);
    return 0;
}

int handle_etag(struct header h, struct res_builder *builder)
{
    printf("processing etag\n");
    fflush(stdout);
    return 0;
}

int handle_pragma(struct header h, struct res_builder *builder)
{
    printf("processing pragma\n");
    fflush(stdout);
    return 0;
}

int handle_authorization(struct header h, struct res_builder *builder)
{
    printf("processing authorization\n");
    fflush(stdout);
    return 0;
}

int handle_cookie(struct header h, struct res_builder *builder)
{
    printf("processing cookie\n");
    fflush(stdout);
    return 0;
}

int handle_set_cookie(struct header h, struct res_builder *builder)
{
    printf("processing set-cookie\n");
    fflush(stdout);
    return 0;
}

int handle_referer(struct header h, struct res_builder *builder)
{
    printf("processing referer\n");
    fflush(stdout);
    return 0;
}

int handle_dnt(struct header h, struct res_builder *builder)
{
    printf("processing dnt\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_ua(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-ua\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_ua_mobile(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-ua-mobile\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_ua_platform(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-ua-platform\n");
    fflush(stdout);
    return 0;
}

int handle_content_encoding(struct header h, struct res_builder *builder)
{
    printf("processing content-encoding\n");
    fflush(stdout);
    return 0;
}

int handle_transfer_encoding(struct header h, struct res_builder *builder)
{
    printf("processing transfer-encoding\n");
    fflush(stdout);
    return 0;
}

int handle_te(struct header h, struct res_builder *builder)
{
    printf("processing te\n");
    fflush(stdout);
    return 0;
}

int handle_accept_ranges(struct header h, struct res_builder *builder)
{
    printf("processing accept-ranges\n");
    fflush(stdout);
    return 0;
}

int handle_range(struct header h, struct res_builder *builder)
{
    printf("processing range\n");
    fflush(stdout);
    return 0;
}

int handle_last_modified(struct header h, struct res_builder *builder)
{
    printf("processing last-modified\n");
    fflush(stdout);
    return 0;
}

int handle_location(struct header h, struct res_builder *builder)
{
    printf("processing location\n");
    fflush(stdout);
    return 0;
}

int handle_server(struct header h, struct res_builder *builder)
{
    printf("processing server\n");
    fflush(stdout);
    return 0;
}

int handle_www_authenticate(struct header h, struct res_builder *builder)
{
    printf("processing www-authenticate\n");
    fflush(stdout);
    return 0;
}

int handle_proxy_authenticate(struct header h, struct res_builder *builder)
{
    printf("processing proxy-authenticate\n");
    fflush(stdout);
    return 0;
}

int handle_proxy_authorization(struct header h, struct res_builder *builder)
{
    printf("processing proxy-authorization\n");
    fflush(stdout);
    return 0;
}

int handle_keep_alive(struct header h, struct res_builder *builder)
{
    printf("processing keep-alive\n");
    fflush(stdout);
    return 0;
}

int handle_expect(struct header h, struct res_builder *builder)
{
    printf("processing expect\n");
    fflush(stdout);
    return 0;
}

int handle_max_forwards(struct header h, struct res_builder *builder)
{
    printf("processing max-forwards\n");
    fflush(stdout);
    return 0;
}

int handle_vary(struct header h, struct res_builder *builder)
{
    printf("processing vary\n");
    fflush(stdout);
    return 0;
}

int handle_retry_after(struct header h, struct res_builder *builder)
{
    printf("processing retry-after\n");
    fflush(stdout);
    return 0;
}

int handle_date(struct header h, struct res_builder *builder)
{
    printf("processing date\n");
    fflush(stdout);
    return 0;
}

int handle_strict_transport_security(struct header h, struct res_builder *builder)
{
    printf("processing strict-transport-security\n");
    fflush(stdout);
    return 0;
}

int handle_content_security_policy(struct header h, struct res_builder *builder)
{
    printf("processing content-security-policy\n");
    fflush(stdout);
    return 0;
}

int handle_x_frame_options(struct header h, struct res_builder *builder)
{
    printf("processing x-frame-options\n");
    fflush(stdout);
    return 0;
}

int handle_x_content_type_options(struct header h, struct res_builder *builder)
{
    printf("processing x-content-type-options\n");
    fflush(stdout);
    return 0;
}

int handle_x_xss_protection(struct header h, struct res_builder *builder)
{
    printf("processing x-xss-protection\n");
    fflush(stdout);
    return 0;
}

int handle_x_powered_by(struct header h, struct res_builder *builder)
{
    printf("processing x-powered-by\n");
    fflush(stdout);
    return 0;
}

int handle_x_requested_with(struct header h, struct res_builder *builder)
{
    printf("processing x-requested-with\n");
    fflush(stdout);
    return 0;
}

int handle_x_forwarded_for(struct header h, struct res_builder *builder)
{
    printf("processing x-forwarded-for\n");
    fflush(stdout);
    return 0;
}

int handle_x_forwarded_host(struct header h, struct res_builder *builder)
{
    printf("processing x-forwarded-host\n");
    fflush(stdout);
    return 0;
}

int handle_x_forwarded_proto(struct header h, struct res_builder *builder)
{
    printf("processing x-forwarded-proto\n");
    fflush(stdout);
    return 0;
}

int handle_x_csrf_token(struct header h, struct res_builder *builder)
{
    printf("processing x-csrf-token\n");
    fflush(stdout);
    return 0;
}

int handle_x_idempotency_key(struct header h, struct res_builder *builder)
{
    printf("processing x-idempotency-key\n");
    fflush(stdout);
    return 0;
}

int handle_x_rate_limit_limit(struct header h, struct res_builder *builder)
{
    printf("processing x-rate-limit-limit\n");
    fflush(stdout);
    return 0;
}

int handle_x_rate_limit_remaining(struct header h, struct res_builder *builder)
{
    printf("processing x-rate-limit-remaining\n");
    fflush(stdout);
    return 0;
}

int handle_x_rate_limit_reset(struct header h, struct res_builder *builder)
{
    printf("processing x-rate-limit-reset\n");
    fflush(stdout);
    return 0;
}

int handle_early_data(struct header h, struct res_builder *builder)
{
    printf("processing early-data\n");
    fflush(stdout);
    return 0;
}

int handle_sec_gpc(struct header h, struct res_builder *builder)
{
    printf("processing sec-gpc\n");
    fflush(stdout);
    return 0;
}

int handle_save_data(struct header h, struct res_builder *builder)
{
    printf("processing save-data\n");
    fflush(stdout);
    return 0;
}

int handle_viewport_width(struct header h, struct res_builder *builder)
{
    printf("processing viewport-width\n");
    fflush(stdout);
    return 0;
}

int handle_device_memory(struct header h, struct res_builder *builder)
{
    printf("processing device-memory\n");
    fflush(stdout);
    return 0;
}

int handle_downlink(struct header h, struct res_builder *builder)
{
    printf("processing downlink\n");
    fflush(stdout);
    return 0;
}

int handle_ect(struct header h, struct res_builder *builder)
{
    printf("processing ect\n");
    fflush(stdout);
    return 0;
}

int handle_rtt(struct header h, struct res_builder *builder)
{
    printf("processing rtt\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_prefers_color_scheme(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-prefers-color-scheme\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_prefers_reduced_motion(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-prefers-reduced-motion\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_prefers_reduced_data(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-prefers-reduced-data\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_ua_arch(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-ua-arch\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_ua_model(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-ua-model\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_ua_bitness(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-ua-bitness\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_ua_full_version(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-ua-full-version\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_ua_full_version_list(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-ua-full-version-list\n");
    fflush(stdout);
    return 0;
}

int handle_sec_ch_ua_wow64(struct header h, struct res_builder *builder)
{
    printf("processing sec-ch-ua-wow64\n");
    fflush(stdout);
    return 0;
}

int handle_x_client_data(struct header h, struct res_builder *builder)
{
    printf("processing x-client-data\n");
    fflush(stdout);
    return 0;
}

int handle_x_forwarded_port(struct header h, struct res_builder *builder)
{
    printf("processing x-forwarded-port\n");
    fflush(stdout);
    return 0;
}

int handle_x_original_forwarded_for(struct header h, struct res_builder *builder)
{
    printf("processing x-original-forwarded-for\n");
    fflush(stdout);
    return 0;
}

int handle_x_proxy_user_ip(struct header h, struct res_builder *builder)
{
    printf("processing x-proxy-user-ip\n");
    fflush(stdout);
    return 0;
}

int handle_x_real_ip(struct header h, struct res_builder *builder)
{
    printf("processing x-real-ip\n");
    fflush(stdout);
    return 0;
}

int handle_x_uid(struct header h, struct res_builder *builder)
{
    printf("processing x-uid\n");
    fflush(stdout);
    return 0;
}

int handle_x_wap_profile(struct header h, struct res_builder *builder)
{
    printf("processing x-wap-profile\n");
    fflush(stdout);
    return 0;
}

int handle_x_device_user_agent(struct header h, struct res_builder *builder)
{
    printf("processing x-device-user-agent\n");
    fflush(stdout);
    return 0;
}









char* toLowerS(char* s) {
    int len = strlen(s); 
    for(int i = 0; i < len; i++) {
        s[i] = tolower((unsigned char)s[i]); 
    }

    return s;
}

void process_header(struct pbuffer_chain *buffer_chain,  struct header *h, struct res_builder *builder) { 
    

        
    int (*f)();
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
    
    
    int r = f(h, builder);
    // if Race condition (a header dependent of X arrived AFTER x)
    if(r == -1) {
        printf("%s Race Condition.\n", htable_entries[n].d); 
        fflush(stdout);
        
        int dn = phhash_djb2(htable_entries[n].d); 
        htable_entries[dn].r = 1; 
        // used by that header handler to handle race condition 
    }
    
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
    
   /*
   printf("%s", handle_context->data);
   fflush(stdout);
   */

    insert(handle_context->client_fd);
     
    read(handle_context->client_fd, handle_context->data, 5000);

    /*
    printf("%s data:", handle_context->data);
    */
    
    // normalize(handle_context->data);
    
    
    struct request req;
    parse(handle_context->data, &req);
    
    struct res_builder builder; 
    
    for(int i = 0; i < req.header_n; i++) {
        process_header(&res_buffer_chain, &req.headers[i], &builder); 
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


