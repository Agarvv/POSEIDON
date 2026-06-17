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



void* pbuffer_chain_w(struct pbuffer_chain *buffer_chain, struct pbuffer_chain_node *node, int q, void* c) {
    /*
    node->fsize = node->fsize - q; 
    node->p[(node->size - node->fsize)] = c;
    
    return &(node->p[node->size - node->fsize]); 
    */
}

int handle_req_line(char* method, char* version, char* path, char* body, struct res_builder *builder) {
    int gh = phhash_djb2("GET"); 
    int hh = phhash_djb2("HEAD"); 
    
    int mh = phhash_djb2(method); 
    if(mh == gh) {
        builder->method = PMETHOD_GET;
        printf("GET MY D-");
        fflush(stdout);
        // get page.
    } else if(mh == hh) {
        builder->method = PMETHOD_HEAD;
        printf("HEAD MY D-");
        fflush(stdout);
    } else {
        builder->method = -1; 
    }

}


char* handle_host(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing host\n");
    fflush(stdout);
    return NULL;
}

char* handle_connection(struct header *h, struct res_builder *builder, int r, char* dv)
{
    printf("Processing Connection\n");
    fflush(stdout); 
    
    static int ch, uh, kh = 0; 
    
    ch = phhash_djb2("Close");
    uh = phhash_djb2("Upgrade");
    kh = phhash_djb2("Keep-alive");
    
    int dh = phhash_djb2(h->value); 
    
    
    printf("%d\n", "Upgrade");
    fflush(stdout);
    
    
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
    
    if(dv != NULL) {
        printf("race.\n");
        fflush(stdout); 
        struct header h;
        h.key = "upgrade";
        h.value = dv; 
        handle_upgrade(&h, builder, 0, NULL); 
    }
    
    return NULL;
}

char* handle_content_length(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing content-length\n");
    fflush(stdout);
    return NULL;
}

char* handle_content_type(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing content-type\n");
    fflush(stdout);
    return NULL;
}

char* handle_user_agent(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing user-agent\n");
    fflush(stdout);
    return NULL;
}

char* handle_accept(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing accept\n");
    fflush(stdout);
    return NULL;
}

char* handle_accept_encoding(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing accept-encoding\n");
    fflush(stdout);
    return NULL;
}

char* handle_accept_language(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing accept-language\n");
    fflush(stdout);
    return NULL;
}

char* handle_accept_charset(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing accept-charset\n");
    fflush(stdout);
    return NULL;
}

char* handle_upgrade(struct header *h, struct res_builder *builder, int r, char* dv)
{
    
    printf("processing upgrade\n");
    fflush(stdout);
    
    
    // if Race Condition...
    if(builder->connection != PCONNECTION_UPGRADE) {
        return h->value;
    }
    
    
    
    int oh = phhash_djb2(h->value); 
    int wh = phhash_djb2("websocket"); 
    
    if(oh == wh) {
        builder->upgrade = PCONNECTION_UPGRADE_WS; 
        printf("Upgrade Protocol...\n"); 
        fflush(stdout);
    } else {
        builder->upgrade == -1; 
        printf("Not Suported Upgrade Protocol...\n"); 
        fflush(stdout);
    }
    
    // else, 
    // continue upgrade header processing 
    return NULL;

}

char* handle_upgrade_insecure_requests(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing upgrade-insecure-requests\n");
    fflush(stdout);
    return NULL;
}

char* handle_websocket_key(struct header *h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-websocket-key\n");
    fflush(stdout);
    
    if(builder->upgrade == PCONNECTION_UPGRADE_WS) {
    printf("Handling WS Handshake.\n");
    fflush(stdout);
    char* ws_key = ws_handshake(h->value);
    builder->ws_key = ws_key;
    }
    
    return NULL;
}

char* handle_websocket_version(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-websocket-version\n");
    fflush(stdout);
    return NULL;
}

char* handle_websocket_protocol(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-websocket-protocol\n");
    fflush(stdout);
    return NULL;
}

char* handle_websocket_extensions(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-websocket-extensions\n");
    fflush(stdout);
    return NULL;
}

char* handle_origin(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing origin\n");
    fflush(stdout);
    return NULL;
}

char* handle_access_control_allow_origin(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing access-control-allow-origin\n");
    fflush(stdout);
    return NULL;
}

char* handle_access_control_allow_methods(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing access-control-allow-methods\n");
    fflush(stdout);
    return NULL;
}

char* handle_access_control_allow_headers(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing access-control-allow-headers\n");
    fflush(stdout);
    return NULL;
}

char* handle_access_control_max_age(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing access-control-max-age\n");
    fflush(stdout);
    return NULL;
}

char* handle_access_control_allow_credentials(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing access-control-allow-credentials\n");
    fflush(stdout);
    return NULL;
}

char* handle_cors_preflight(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing cors-preflight\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_fetch_dest(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-fetch-dest\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_fetch_mode(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-fetch-mode\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_fetch_site(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-fetch-site\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_fetch_user(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-fetch-user\n");
    fflush(stdout);
    return NULL;
}

char* handle_cache_control(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing cache-control\n");
    fflush(stdout);
    return NULL;
}

char* handle_if_modified_since(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing if-modified-since\n");
    fflush(stdout);
    return NULL;
}

char* handle_if_none_match(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing if-none-match\n");
    fflush(stdout);
    return NULL;
}

char* handle_if_match(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing if-match\n");
    fflush(stdout);
    return NULL;
}

char* handle_if_unmodified_since(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing if-unmodified-since\n");
    fflush(stdout);
    return NULL;
}

char* handle_if_range(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing if-range\n");
    fflush(stdout);
    return NULL;
}

char* handle_etag(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing etag\n");
    fflush(stdout);
    return NULL;
}

char* handle_pragma(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing pragma\n");
    fflush(stdout);
    return NULL;
}

char* handle_authorization(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing authorization\n");
    fflush(stdout);
    return NULL;
}

char* handle_cookie(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing cookie\n");
    fflush(stdout);
    return NULL;
}

char* handle_set_cookie(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing set-cookie\n");
    fflush(stdout);
    return NULL;
}

char* handle_referer(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing referer\n");
    fflush(stdout);
    return NULL;
}

char* handle_dnt(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing dnt\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-ua\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_mobile(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-ua-mobile\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_platform(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-ua-platform\n");
    fflush(stdout);
    return NULL;
}

char* handle_content_encoding(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing content-encoding\n");
    fflush(stdout);
    return NULL;
}

char* handle_transfer_encoding(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing transfer-encoding\n");
    fflush(stdout);
    return NULL;
}

char* handle_te(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing te\n");
    fflush(stdout);
    return NULL;
}

char* handle_accept_ranges(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing accept-ranges\n");
    fflush(stdout);
    return NULL;
}

char* handle_range(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing range\n");
    fflush(stdout);
    return NULL;
}

char* handle_last_modified(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing last-modified\n");
    fflush(stdout);
    return NULL;
}

char* handle_location(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing location\n");
    fflush(stdout);
    return NULL;
}

char* handle_server(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing server\n");
    fflush(stdout);
    return NULL;
}

char* handle_www_authenticate(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing www-authenticate\n");
    fflush(stdout);
    return NULL;
}

char* handle_proxy_authenticate(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing proxy-authenticate\n");
    fflush(stdout);
    return NULL;
}

char* handle_proxy_authorization(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing proxy-authorization\n");
    fflush(stdout);
    return NULL;
}

char* handle_keep_alive(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing keep-alive\n");
    fflush(stdout);
    return NULL;
}

char* handle_expect(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing expect\n");
    fflush(stdout);
    return NULL;
}

char* handle_max_forwards(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing max-forwards\n");
    fflush(stdout);
    return NULL;
}

char* handle_vary(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing vary\n");
    fflush(stdout);
    return NULL;
}

char* handle_retry_after(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing retry-after\n");
    fflush(stdout);
    return NULL;
}

char* handle_date(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing date\n");
    fflush(stdout);
    return NULL;
}

char* handle_strict_transport_security(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing strict-transport-security\n");
    fflush(stdout);
    return NULL;
}

char* handle_content_security_policy(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing content-security-policy\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_frame_options(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-frame-options\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_content_type_options(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-content-type-options\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_xss_protection(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-xss-protection\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_powered_by(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-powered-by\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_requested_with(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-requested-with\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_forwarded_for(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-forwarded-for\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_forwarded_host(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-forwarded-host\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_forwarded_proto(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-forwarded-proto\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_csrf_token(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-csrf-token\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_idempotency_key(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-idempotency-key\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_rate_limit_limit(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-rate-limit-limit\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_rate_limit_remaining(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-rate-limit-remaining\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_rate_limit_reset(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-rate-limit-reset\n");
    fflush(stdout);
    return NULL;
}

char* handle_early_data(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing early-data\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_gpc(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-gpc\n");
    fflush(stdout);
    return NULL;
}

char* handle_save_data(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing save-data\n");
    fflush(stdout);
    return NULL;
}

char* handle_viewport_width(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing viewport-width\n");
    fflush(stdout);
    return NULL;
}

char* handle_device_memory(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing device-memory\n");
    fflush(stdout);
    return NULL;
}

char* handle_downlink(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing downlink\n");
    fflush(stdout);
    return NULL;
}

char* handle_ect(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing ect\n");
    fflush(stdout);
    return NULL;
}

char* handle_rtt(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing rtt\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_prefers_color_scheme(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-prefers-color-scheme\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_prefers_reduced_motion(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-prefers-reduced-motion\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_prefers_reduced_data(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-prefers-reduced-data\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_arch(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-ua-arch\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_model(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-ua-model\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_bitness(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-ua-bitness\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_full_version(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-ua-full-version\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_full_version_list(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-ua-full-version-list\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_wow64(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing sec-ch-ua-wow64\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_client_data(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-client-data\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_forwarded_port(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-forwarded-port\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_original_forwarded_for(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-original-forwarded-for\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_proxy_user_ip(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-proxy-user-ip\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_real_ip(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-real-ip\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_uid(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-uid\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_wap_profile(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-wap-profile\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_device_user_agent(struct header h, struct res_builder *builder, int r, char* dv)
{
    printf("processing x-device-user-agent\n");
    fflush(stdout);
    return NULL;
}






char* toLowerS(char* s) {
    int len = strlen(s); 
    for(int i = 0; i < len; i++) {
        s[i] = tolower((unsigned char)s[i]); 
    }

    return s;
}

void process_header(struct pbuffer_chain *buffer_chain,  struct header *h, struct res_builder *builder) { 
    
        
    char* (*f)();
    
    
    char* l = toLowerS(h->key);

    
    
    int n = phhash_djb2(l);

    
    int len = strlen(l); 
     
    while(strncmp(l, htable_entries[n].hname, len) != 0) {
        
        n++;
        
        if(n >= 200) {
            n = 0;
        }
    }
    

    
    
    
    f = htable_entries[n].f;
    
    char* r = f(h, builder, htable_entries[n].r);
    

    if(r != NULL) {
        printf("%s Race Condition.\n", r); 
        fflush(stdout);
        int dn = phhash_djb2(htable_entries[n].d);

        htable_entries[dn].r = 1; 
        htable_entries[dn].dv = r; 
    
    }
    
}


void handle(void* args) {
    struct parena *arena; 
    pinit(arena); 
    // char* data = palloc(5000, arena); 

    int upgrade = 0;
    char* sec_ws_key;
    struct pbuffer_chain res_buffer_chain;
    struct pbuffer_chain_node node; 
    node.size = 5000;
    node.fsize = 5000;
    
    node.p = palloc(5000, arena); 
    node.next = NULL;
    
    res_buffer_chain.head = &node;
    res_buffer_chain.len = 5000;

    struct hnd_context *handle_context = (struct hnd_context*)args;
    handle_context->data = node.p; 
    
   
   printf("%s", handle_context->data);
   fflush(stdout);
   

    insert(handle_context->client_fd);
    int b = 0; 
    
    
    read(handle_context->client_fd, handle_context->data, 5000);
    

    /*
    printf("%s data:", handle_context->data);
    */
    
    // normalize(handle_context->data);
    
    
    struct request req;
    parse(handle_context->data, &req);
    
    struct res_builder builder; 
    
    handle_req_line(req.method, req.path, req.version, req.body, &builder);
    
    for(int i = 0; i < req.header_n; i++) {
        process_header(&res_buffer_chain, &req.headers[i], &builder); 
    }

    
    }

