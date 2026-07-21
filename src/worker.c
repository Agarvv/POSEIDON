#include<main.h>
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
#include<websocket.h>
#include<palloc.h>
#include<ctype.h>
#include<normalize.h> 
#include <sys/uio.h>
#include<ws_handler.h>

struct ws_context websocket_context;

// this returns a buffer chain with one node of chunk_size capacity.
struct pbuffer_chain* init_buffer_chain(int chunk_size) {
    struct parena arena; 
    pinit(&arena); 
    
    struct pbuffer_chain_node* bchain_node = palloc(sizeof(struct pbuffer_chain_node), &arena);
    
    bchain_node->size = chunk_size;
    bchain_node->fsize = chunk_size; 
    bchain_node->p = palloc(chunk_size, &arena); 
    bchain_node->next = NULL; 
    
    struct pbuffer_chain* bchain = palloc(sizeof(struct pbuffer_chain), &arena); 
    
    bchain->head = bchain_node; 
    bchain->tail = bchain_node; 
    bchain->len = chunk_size;
    bchain->arena = &arena;
    // bchain.arena = &arena;
    
    return bchain; 
}

void pbuffer_chain_write(struct pbuffer_chain *buffer_chain, char* c) {
    int clen = strlen(c); 
    
    
    if((buffer_chain->tail->fsize - clen) < 0) {
        
    
        struct pbuffer_chain_node bchain_node;
    
    int bsize = buffer_chain->len; 
    
    bchain_node.size = bsize;
    bchain_node.fsize = bsize; 
    bchain_node.p = palloc(buffer_chain->len, buffer_chain->arena); 
    buffer_chain->tail = &bchain_node;
    }
    
    int findex = (buffer_chain->tail->size - buffer_chain->tail->fsize); 
    
    
    strncpy(&(buffer_chain->tail->p[findex]), c, clen);
    
    buffer_chain->tail->fsize = buffer_chain->tail->fsize - clen;
    
}



void* pbuffer_chain_w(struct pbuffer_chain *buffer_chain, struct pbuffer_chain_node *node, int q, void* c) {
    /*
    node->fsize = node->fsize - q; 
    node->p[(node->size - node->fsize)] = c;
    
    return &(node->p[node->size - node->fsize]); 
    */
}

void pbuffer_chain_wn(struct pbuffer_chain *buffer_chain, int n, void* data) {
   if((buffer_chain->tail->fsize - n) < 0) {
        
    
        struct pbuffer_chain_node bchain_node;
    
    int bsize = buffer_chain->len; 
    
    bchain_node.size = bsize;
    bchain_node.fsize = bsize; 
    bchain_node.p = palloc(buffer_chain->len, buffer_chain->arena); 
    buffer_chain->tail = &bchain_node;
    }
    
    int findex = (buffer_chain->tail->size - buffer_chain->tail->fsize); 
    
    
    memcpy(buffer_chain->tail->p, data, n); 
    
    buffer_chain->tail->fsize = buffer_chain->tail->fsize - n;
}

void* pbuffer_chain_insert(struct pbuffer_chain *buffer_chain, void* data, int data_size) {
    if((buffer_chain->tail->fsize - data_size) < 0) {
        
    
        struct pbuffer_chain_node bchain_node;
    
    int bsize = buffer_chain->len; 
    
    bchain_node.size = bsize;
    bchain_node.fsize = bsize; 
    bchain_node.p = palloc(buffer_chain->len, buffer_chain->arena); 
    buffer_chain->tail = &bchain_node;
    }
    
    int findex = (buffer_chain->tail->size - buffer_chain->tail->fsize); 
    
    
    ((void**)buffer_chain->tail->p)[findex] = data; 
    
    buffer_chain->tail->fsize = buffer_chain->tail->fsize - data_size;
}

int handle_req_line(char* method, char* version, char* path, char* body, struct res_builder *builder) {
    int gh = phhash_djb2("GET"); 
    int hh = phhash_djb2("HEAD"); 
    
    int mh = phhash_djb2(method); 
    if(mh == gh) {
        builder->method = PMETHOD_GET;
        printf("GET MY D-\n");
        fflush(stdout);
        // get page.
    } else if(mh == hh) {
        builder->method = PMETHOD_HEAD;
        printf("HEAD MY D-\n");
        fflush(stdout);
    } else {
        printf("ZZZ MY D-\n");
        builder->method = -1; 
        builder->err = 1;
    }

}


char* handle_host(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing host\n");
    fflush(stdout);
    return NULL;
}

char* handle_connection(struct header *h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("Processing Connection\n");
    fflush(stdout); 
    
    static int ch, uh, kh = 0; 
    
    ch = phhash_djb2("Close");
    uh = phhash_djb2("Upgrade");
    kh = phhash_djb2("keep-alive");
    
    int dh = phhash_djb2(h->value); 
    
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
        builder->err = 1;
    }
    
    if(dv != NULL && r == 1) {
        printf("race.\n");
        fflush(stdout); 
        struct header h;
        h.key = "upgrade";
        h.value = dv; 
        handle_upgrade(&h, builder, 0, NULL, handle_context); 
    }
    
    return NULL;
}

char* handle_content_length(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing content-length\n");
    fflush(stdout);
    return NULL;
}

char* handle_content_type(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing content-type\n");
    fflush(stdout);
    return NULL;
}

char* handle_user_agent(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing user-agent\n");
    fflush(stdout);
    return NULL;
}

char* handle_accept(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing accept\n");
    fflush(stdout);
    return NULL;
}

char* handle_accept_encoding(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing accept-encoding\n");
    fflush(stdout);
    return NULL;
}

char* handle_accept_language(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing accept-language\n");
    fflush(stdout);
    return NULL;
}

char* handle_accept_charset(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing accept-charset\n");
    fflush(stdout);
    return NULL;
}

char* handle_upgrade(struct header *h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing upgrade\n");
    
    printf("Se c9menyo el pene \n");
    
    // if Race Condition...
    if(builder->connection != PCONNECTION_UPGRADE) {
        printf("Holaaajdkskekdk\n");
        
        return h->value;
    }
    
    int oh = phhash_djb2(h->value); 
    printf("POLLA 2 upgrade\n");
    
    int wh = phhash_djb2("websocket"); 
    
    if(oh == wh) {
        builder->upgrade = PCONNECTION_UPGRADE_WS; 
        
    //    handle_context->cl->protocol = PPROTOCOL_WS;
    
        printf("Upgrade Protocol...\n"); 
        
    } else {
        builder->upgrade = -1; 
        builder->err = 1;
        printf("Not Suported Upgrade Protocol...\n"); 
        
    }
    
    printf("Se acabo el pene\n");
    // else, 
    // continue upgrade header processing 
    return NULL;
}

char* handle_upgrade_insecure_requests(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing upgrade-insecure-requests\n");
    fflush(stdout);
    return NULL;
}

char* handle_websocket_key(struct header *h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
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

char* handle_websocket_version(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-websocket-version\n");
    fflush(stdout);
    return NULL;
}

char* handle_websocket_protocol(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-websocket-protocol\n");
    fflush(stdout);
    return NULL;
}

char* handle_websocket_extensions(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-websocket-extensions\n");
    fflush(stdout);
    return NULL;
}

char* handle_origin(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing origin\n");
    fflush(stdout);
    return NULL;
}

char* handle_access_control_allow_origin(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing access-control-allow-origin\n");
    fflush(stdout);
    return NULL;
}

char* handle_access_control_allow_methods(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing access-control-allow-methods\n");
    fflush(stdout);
    return NULL;
}

char* handle_access_control_allow_headers(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing access-control-allow-headers\n");
    fflush(stdout);
    return NULL;
}

char* handle_access_control_max_age(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing access-control-max-age\n");
    fflush(stdout);
    return NULL;
}

char* handle_access_control_allow_credentials(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing access-control-allow-credentials\n");
    fflush(stdout);
    return NULL;
}

char* handle_cors_preflight(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing cors-preflight\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_fetch_dest(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-fetch-dest\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_fetch_mode(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-fetch-mode\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_fetch_site(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-fetch-site\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_fetch_user(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-fetch-user\n");
    fflush(stdout);
    return NULL;
}

char* handle_cache_control(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing cache-control\n");
    fflush(stdout);
    return NULL;
}

char* handle_if_modified_since(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing if-modified-since\n");
    fflush(stdout);
    return NULL;
}

char* handle_if_none_match(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing if-none-match\n");
    fflush(stdout);
    return NULL;
}

char* handle_if_match(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing if-match\n");
    fflush(stdout);
    return NULL;
}

char* handle_if_unmodified_since(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing if-unmodified-since\n");
    fflush(stdout);
    return NULL;
}

char* handle_if_range(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing if-range\n");
    fflush(stdout);
    return NULL;
}

char* handle_etag(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing etag\n");
    fflush(stdout);
    return NULL;
}

char* handle_pragma(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing pragma\n");
    fflush(stdout);
    return NULL;
}

char* handle_authorization(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing authorization\n");
    fflush(stdout);
    return NULL;
}

char* handle_cookie(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing cookie\n");
    fflush(stdout);
    return NULL;
}

char* handle_set_cookie(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing set-cookie\n");
    fflush(stdout);
    return NULL;
}

char* handle_referer(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing referer\n");
    fflush(stdout);
    return NULL;
}

char* handle_dnt(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing dnt\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-ua\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_mobile(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-ua-mobile\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_platform(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-ua-platform\n");
    fflush(stdout);
    return NULL;
}

char* handle_content_encoding(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing content-encoding\n");
    fflush(stdout);
    return NULL;
}

char* handle_transfer_encoding(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing transfer-encoding\n");
    fflush(stdout);
    return NULL;
}

char* handle_te(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing te\n");
    fflush(stdout);
    return NULL;
}

char* handle_accept_ranges(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing accept-ranges\n");
    fflush(stdout);
    return NULL;
}

char* handle_range(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing range\n");
    fflush(stdout);
    return NULL;
}

char* handle_last_modified(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing last-modified\n");
    fflush(stdout);
    return NULL;
}

char* handle_location(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing location\n");
    fflush(stdout);
    return NULL;
}

char* handle_server(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing server\n");
    fflush(stdout);
    return NULL;
}

char* handle_www_authenticate(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing www-authenticate\n");
    fflush(stdout);
    return NULL;
}

char* handle_proxy_authenticate(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing proxy-authenticate\n");
    fflush(stdout);
    return NULL;
}

char* handle_proxy_authorization(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing proxy-authorization\n");
    fflush(stdout);
    return NULL;
}

char* handle_keep_alive(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing keep-alive\n");
    fflush(stdout);
    return NULL;
}

char* handle_expect(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing expect\n");
    fflush(stdout);
    return NULL;
}

char* handle_max_forwards(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing max-forwards\n");
    fflush(stdout);
    return NULL;
}

char* handle_vary(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing vary\n");
    fflush(stdout);
    return NULL;
}

char* handle_retry_after(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing retry-after\n");
    fflush(stdout);
    return NULL;
}

char* handle_date(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing date\n");
    fflush(stdout);
    return NULL;
}

char* handle_strict_transport_security(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing strict-transport-security\n");
    fflush(stdout);
    return NULL;
}

char* handle_content_security_policy(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing content-security-policy\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_frame_options(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-frame-options\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_content_type_options(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-content-type-options\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_xss_protection(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-xss-protection\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_powered_by(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-powered-by\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_requested_with(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-requested-with\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_forwarded_for(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-forwarded-for\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_forwarded_host(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-forwarded-host\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_forwarded_proto(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-forwarded-proto\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_csrf_token(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-csrf-token\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_idempotency_key(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-idempotency-key\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_rate_limit_limit(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-rate-limit-limit\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_rate_limit_remaining(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-rate-limit-remaining\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_rate_limit_reset(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-rate-limit-reset\n");
    fflush(stdout);
    return NULL;
}

char* handle_early_data(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing early-data\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_gpc(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-gpc\n");
    fflush(stdout);
    return NULL;
}

char* handle_save_data(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing save-data\n");
    fflush(stdout);
    return NULL;
}

char* handle_viewport_width(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing viewport-width\n");
    fflush(stdout);
    return NULL;
}

char* handle_device_memory(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing device-memory\n");
    fflush(stdout);
    return NULL;
}

char* handle_downlink(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing downlink\n");
    fflush(stdout);
    return NULL;
}

char* handle_ect(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing ect\n");
    fflush(stdout);
    return NULL;
}

char* handle_rtt(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing rtt\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_prefers_color_scheme(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-prefers-color-scheme\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_prefers_reduced_motion(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-prefers-reduced-motion\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_prefers_reduced_data(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-prefers-reduced-data\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_arch(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-ua-arch\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_model(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-ua-model\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_bitness(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-ua-bitness\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_full_version(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-ua-full-version\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_full_version_list(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-ua-full-version-list\n");
    fflush(stdout);
    return NULL;
}

char* handle_sec_ch_ua_wow64(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing sec-ch-ua-wow64\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_client_data(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-client-data\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_forwarded_port(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-forwarded-port\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_original_forwarded_for(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-original-forwarded-for\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_proxy_user_ip(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-proxy-user-ip\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_real_ip(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-real-ip\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_uid(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-uid\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_wap_profile(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-wap-profile\n");
    fflush(stdout);
    return NULL;
}

char* handle_x_device_user_agent(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context)
{
    printf("processing x-device-user-agent\n");
    fflush(stdout);
    return NULL;
}


struct pbuffer_chain* res(struct res_builder *builder, struct hnd_context* handle_context) {
    struct pbuffer_chain *res_pbuffer_chain = init_buffer_chain(4096);
    
    
    if(builder->err == 1) {
        // pbuffer_chain_write(res_pbuffer_chain, "HTTP/1.1 400 Bad Request\r\n\r\n");
        strncpy(res_pbuffer_chain->head->p, "HTTP/1.1 400 Bad Request\r\n\r\n", 33);
        printf("%s sjdfjwjjr %d\n", res_pbuffer_chain->head->p, res_pbuffer_chain->len); 
        
        return res_pbuffer_chain;
    }

    
    
    switch(builder->method) {
        case PMETHOD_HEAD:
            pbuffer_chain_write(res_pbuffer_chain, "HTTP/1.1 204 No Content\r\n\r\n");
            return res_pbuffer_chain;

        case PMETHOD_GET:
            if(builder->connection == PCONNECTION_UPGRADE) {
                
                switch(builder->upgrade) {
                    case PCONNECTION_UPGRADE_WS:
                    
                        pbuffer_chain_write(res_pbuffer_chain, "HTTP/1.1 101 Switching Protocols\r\n");
                        pbuffer_chain_write(res_pbuffer_chain, "Connection: Upgrade\r\n");
                        pbuffer_chain_write(res_pbuffer_chain, "Upgrade: websocket\r\n");
                        pbuffer_chain_write(res_pbuffer_chain, "Sec-WebSocket-Accept: ");
                        pbuffer_chain_write(res_pbuffer_chain, builder->ws_key);
                        pbuffer_chain_write(res_pbuffer_chain, "\r\n\r\n");
                        
                        
                        handle_context->cl->protocol = PPROTOCOL_WS;
                        
                        
                        
                        
                        
                        

                    





                        return res_pbuffer_chain;


                    default:
                        printf("Error\n");
                        fflush(stdout);
                        return res_pbuffer_chain;
                }
            }

            pbuffer_chain_write(res_pbuffer_chain, 
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Length: 0\r\n"
                "Connection: close\r\n\r\n");
            return res_pbuffer_chain;
        
        default: 
             printf("Error\n");
             fflush(stdout);
             return res_pbuffer_chain;
    }
}





char* toLowerS(char* s) {
    int len = strlen(s); 
    for(int i = 0; i < len; i++) {
        s[i] = tolower((unsigned char)s[i]); 
    }

    return s;
}

void process_header(struct pbuffer_chain *buffer_chain,  struct header *h, struct res_builder *builder, struct hnd_context* handle_context) { 
    
        
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
    
    char* r = f(h, builder, htable_entries[n].r, handle_context);
    

    if(r != NULL) {
        printf("%s Race Condition.\n", r); 
        fflush(stdout);
        int dn = phhash_djb2(htable_entries[n].d);

        htable_entries[dn].r = 1; 
        htable_entries[dn].dv = r; 
    
    }
    
} 


struct pbuffer_chain* room_buffer_chain = NULL;

// BRTGP Application Protocol 
void ws_on_message(struct hnd_context* handle_context, struct ws_frame* frame, unsigned char* payload, int len) {
    
    if(room_buffer_chain == NULL) {
        room_buffer_chain = init_buffer_chain(4096);
        
        // room id counter
        *(int*)room_buffer_chain->head->p = 1;
        room_buffer_chain->head->fsize -= 4;
    }
    
    
    int offset = 0; 
    
    int event = payload[offset]; 
    offset += 1; 
    
    int fields = 0; 
    
    
    // receives user id and room id.
    // if room id create new room data structure, add user to it and mark user as owner
    // else if room id not zero, add user to room.
    // in first case, return message indicating that and user id, room id as payload
    // in second case, to joining user id, return message indicating sucess and all users in the room as payload
    // to other users already in the room, return message with event USER_JOIN and in payload, the joining user.
    switch(event) {
        // JOIN_ROOM 
        case 1: {
            struct btrgp_field fields[2];
                       
            int* room_id = (int*)payload[offset];
            
            // skip user id because its non relevant in this case 
            offset += 8;
            
            // means to create room
            if(room_id == 0) {
                int* payload_offset = 0; 
                unsigned char sig; 
                
                // Create Room
                
                
                sig = payload[offset];
                offset += 1;
                
                
                
                for(int i = 0; sig != 0xFF; i++) {
                    printf("Create Room %d\n", sig);
                    
                    int le = *(int*)(&payload[offset]); 
                    printf("Length djdj%d\n", le);
                    
                    offset += 4; 
                    

                    
                        unsigned char* d = &payload[offset]; 
                        offset += 4;
                        
                                            
                    printf("eieiei Room %d\n", payload[offset]);
                        
                        fields[i].data = d;
                        fields[i].len = le;
                        
                        sig = payload[offset];
                        offset += 1;
                        
                        
                        
                }  
                    
                
                for(int i = 0; i <  2; i ++) {
                    
                    for(int p = 0; p < fields[i].len; p++) {
                        printf("Data %d, Is %d\n", i, fields[i].data[p]); 
                    }
                }
            
            struct room r;
            r.player_id_c = 0; 
            
            struct player p;
            p.id = r.player_id_c; 
            p.username = fields[0].data; 
            p.pfp = fields[1].data; 
            p.fd = handle_context->client_fd; 
            
            r.id = *(int*)room_buffer_chain->head->p; 
            r.players[r.id] = p;
            r.player_id_c++; 
            r.team_id_c = 0;
            r.owner_id = p.id;

            // insert room to buffer chain
            pbuffer_chain_insert(room_buffer_chain, &r, sizeof(r));
            

            unsigned char response[] = 
            {
                0x00, // No Error
                r.id,
                r.players[r.id].id,
                
            };

            // write WS frame with inner BTRTGP indicating that
            // all is OK and return user and room id as BTRGP Payload
            

            printf("Response Sendt\n");
            
         } else {
            // search room by id and add user to room
            if(*(int*)room_buffer_chain->head->p < room_id) {
                // WS frame with inner BTRTGP indicating error.
                printf("No such Room\n");
            }
           
            struct player p; 
            p.id = ((struct room*)room_buffer_chain->tail->p)[*room_id].player_id_c;
            printf("Player ID %d\n", p.id);
            p.username = fields[0].data;
            p.pfp = fields[1].data;
            p.fd = handle_context->client_fd;
           
            // to joining player fd, send WS frame with inner BTRTGP indicating that all is OK 
            // and return users, user id and room id as BTRGP Payload

            // for other players, send WS frame with inner BTRTGP indicating that a new player has joined the room
            // and in the payload the user data.
         }

        
            
            break;
        }
        
    



        // message

        // receives room id, user id as S and a payload with the message data.
        // broadcast to all players in the team identified by f(S) the message data.
        case 3: {
            int room_id = *(int*)payload[offset];
            offset += 4;
            int user_id = *(int*)payload[offset];
            offset += 4;


            break;
        }

        // draw

        // receives room id, user id as S and a payload with the drawing data.
        // broadcast to all players in the team identified by f(S) the drawing data.
        case 4: {
            break;
        }

        // vote

        // receives room id and an user id as S identifying the team to vote for
        // get team by f(S) and increment team votes.
        case 5: {
            int* room_id = &payload[offset];
            offset += 4;
            
            int* user_id = &payload[offset];
            offset += 4;
            
            int* team_id = &payload[offset];
            offset += 4;
            
            struct room *r = &((struct room*)room_buffer_chain->tail->p)[*room_id];
            
            struct team *t = &r->teams[*team_id];
            
            t->votes++;
            
            // response
            break;
        }
        
        // start game

        // receives room id and user id, payload none.
        // gets room by id, if user is owner,
        // make teams and mark the game as started
        // return sucessfull BTRGP message to all plauyers.
        case 6: {
            
            int* room_id = &payload[offset];
            offset += 4;
            
            int* user_id = &payload[offset];
            printf("sididis %d \n", *user_id);
            offset += 4;
            
            

            struct room *r = &((struct room*)room_buffer_chain->tail->p)[*room_id];
            
            
          
          printf("s8ii %d\n", ((struct room*)room_buffer_chain->tail->p)[*room_id].owner_id); 
          
          if (((struct room*)room_buffer_chain->tail->p)[*room_id].owner_id == *user_id) {
                printf("Starting Game\n");
                
                /* 
                r->teams = init_buffer_chain(4096);

                *((int*)r->teams->tail->p) = 0;
                r->teams->tail->fsize -= 4;
                */
            

                // loop users and make teams 
                struct player pu[3];
                int cu = 0; 
                
                printf("sisiskenfkdk %d\n", r->player_id_c);
                if((r->player_id_c % 2) == 0) {
                    pu[2] = r->players[r->player_id_c];
                }
                
                while(cu != r->player_id_c) {
                    for(int i = 0; i < 2; i++) {
                        pu[cu] = r->players[cu]; 
                        cu++;
                    }
                    
                    struct team t;
                    t.id = r->team_id_c; 
                    r->team_id_c++;
                    t.players[0] = pu[cu - 1];
                    t.players[1] = pu[cu];
                    t.players[2] = pu[2];
                    t.votes = 0; 
                    r->teams[t.id] = t;
            
                
                }
                
                // write response.
                printf("OK \n");
                
          } else {
                printf("Not Owner\n");
          }


            break;
        }
        
        
        
        default: {
            printf("None\n");
            break; 
        }
    }
    
    for(int i = 0; i < len; i++) {
        printf("%d by \n", payload[i]);
    }
    
    
}

void handle_ws(void* args, struct ws_context *websocket_context) {
    printf("hojdjdla");
    struct hnd_context *handle_context = (struct hnd_context*)args;

    struct pbuffer_chain* buffer_chain = init_buffer_chain(4096);
    
    buffer_chain->tail->p = (unsigned char*)buffer_chain->tail->p;
    
    int tb = 0; 
    unsigned char bytes[127];
    int b = recv(handle_context->client_fd, bytes, 127, MSG_DONTWAIT);
    tb = tb + b;
    
    pbuffer_chain_wn(buffer_chain, 127, &bytes); 
    
    while(b > 0) {
                  b = recv(handle_context->client_fd, bytes, 127, MSG_DONTWAIT);
                  if(b != -1) {
                      tb = tb + b; 
                  }
                  pbuffer_chain_wn(buffer_chain, 127, &bytes); 
              }
    printf("Total Bytes: %d\n", tb);
    
    //parse 
    unsigned char* ptr = ((unsigned char*)buffer_chain->tail->p);
    
    int mask = (ptr[1] & 0x80); 
    if(!mask) {
        printf("No Mask. Closing Connection.\n");
    }
    
    
    
    int opcode = (ptr[0] & 0x0F);
    
    
    
    int length = 0; 
    int flen = ptr[1] & 0x7F;
    unsigned char* data; 
    unsigned char dmask[4];
    
    if(flen == 126) {
    length = flen + ptr[2] + ptr[3]; 
    printf("Exceptional Length.\n");
    *data = ptr[8];         
    memcpy(dmask, &ptr[4], 4); 
    
    } else if (flen == 127) {
    length = flen + ptr[2] + ptr[3] + ptr[4] + ptr[5] + ptr[6] + ptr[7] + ptr[8] + ptr[9]; 
    memcpy(dmask, &ptr[10], 4); 
    *data = ptr[14];            
    
    printf("Exceptional Length.\n");
    }
    
    memcpy(dmask, &ptr[2], 4);
    length = flen; 
    printf("NOT Exceptional Length. %d\n", length);
    
    
    data = &ptr[6];
    
    
    
    switch(opcode) {
        // continuation
        case 0x0: {
            struct ws_frame_data frame_data;
            frame_data.len = length;
            frame_data.ptr = data;
            
            pbuffer_chain_insert(websocket_context->frames[handle_context->client_fd - 3].frame_buffer_chain, &frame_data, sizeof(&frame_data)); 
            
            websocket_context->frames[handle_context->client_fd - 3].frames++;
            break;
        }
        // text
        case 0x1: {
            struct pbuffer_chain *frame_buffer_chain = init_buffer_chain(4096); 
            
            (struct ws_frame*)frame_buffer_chain->head->p;
            
            struct ws_frame frame;
            frame.opcode = opcode;
            frame.mask = dmask;
            frame.frame_buffer_chain = frame_buffer_chain;
            frame.frames = 1;
            
            struct ws_frame_data frame_data;
            frame_data.len = length;
            frame_data.ptr = data;
            
            pbuffer_chain_insert(frame_buffer_chain, &frame_data, sizeof(&frame_data)); 
            
            websocket_context->frames[handle_context->client_fd - 3] = frame;
            
            break;
        }
        // binary
        case 0x2: {
            struct pbuffer_chain *frame_buffer_chain = init_buffer_chain(4096); 
            
            (struct ws_frame*)frame_buffer_chain->head->p;
            
            struct ws_frame frame;
            frame.opcode = opcode;
            frame.mask = dmask;
            frame.frame_buffer_chain = frame_buffer_chain;
            frame.frames = 1;
            
            struct ws_frame_data frame_data;
            frame_data.len = length;
            frame_data.ptr = data;
            
            
            pbuffer_chain_insert(frame_buffer_chain, &frame_data, sizeof(&frame_data)); 
            
            websocket_context->frames[handle_context->client_fd - 3] = frame;
            
            break;
        }
        //close
        case 0x8: {
            break;
        }
        // ping
        case 0x9: {
            break;
        }
        //pong
        case 0xA: {
            break;
        }
    }
    
    if(ptr[0] & 0x80) {
        printf("End.\n");
        
        struct ws_frame_data** cast = (struct ws_frame_data**)(websocket_context->frames[handle_context->client_fd - 3].frame_buffer_chain->head->p);
        
        struct ws_frame_data* fdata = (struct ws_frame_data*)*(cast);
        
        struct pbuffer_chain_node* fr_node; 
        fr_node = websocket_context->frames[handle_context->client_fd - 3].frame_buffer_chain->head;
        
        int l = 0; 
       
       
       
        while(fr_node->fsize != 0) {
            printf("jsjjdjeje: %d\n", l);
            l = (fr_node->size - fr_node->fsize) / sizeof(struct ws_frame_data*); 
            
            printf("ele pene: %d\n", l);
            if(fr_node->next == NULL) {
                printf("Exit\n");
                break;
            }
            fr_node = fr_node->next;
        }
        
        int tl = 0; 
        printf(" fkkf: %d\n", l);
        
        for(int i = 0; i < l; i++) {
            tl = tl + fdata[i].len; 
        }
        
        printf("Total Len: %d\n", tl);
        
        
        unsigned char unmasked[fdata->len]; 
        
        
        
        for(int i = 0; i < websocket_context->frames[handle_context->client_fd - 3].frames; i++) {
            
        
        
        for(int i = 0; i < fdata->len; i++) {
            unmasked[i] = fdata->ptr[i] ^ websocket_context->frames[handle_context->client_fd - 3].mask[i % 4];
            
        }
         
    }
        ws_on_message(handle_context, &(websocket_context->frames[handle_context->client_fd - 3]), unmasked, tl);
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
    
    
    
   
   printf("Data: 1286713165 %s  \n", handle_context->data);
   fflush(stdout);
   

    //insert(handle_context->client_fd);
    int b = 0; 
    
    
    read(handle_context->client_fd, handle_context->data, 5000);
    

    /*
    printf("%s data:", handle_context->data);
    */
    
    // normalize(handle_context->data);
    
    
    struct request req;
    parse(handle_context->data, &req);
    
    struct res_builder builder; 
    builder.err = 0;
    
    handle_req_line(req.method, req.path, req.version, req.body, &builder);
    
    

    
    printf("antes djejdj\n");
    
    for(int i = 0; i < req.header_n; i++) {
        
        process_header(&res_buffer_chain, &req.headers[i], &builder, handle_context); 
    }
    
    struct pbuffer_chain *rbuffer_chain = res(&builder, handle_context); 
    
    
    // current node
    struct pbuffer_chain_node *in_node;
    struct pbuffer_chain_node *cnode;
    
    
    cnode = rbuffer_chain->head;
    in_node = rbuffer_chain->head;
    int bc = 0; 
    
    
    
    while(cnode->fsize > 0) {
    
        bc++;
        
        if(cnode->next == NULL) {
            break; 
        }
        
        cnode = cnode->next;
        
    }
    
    
    
    struct iovec iovc[bc]; 
    
    
    for(int i = 0; i < bc; i++) {
        
        iovc[i].iov_base = in_node->p; 
    
        iovc[i].iov_len = in_node->size - in_node->fsize;
        
        if(in_node-> next != NULL) {
        in_node = in_node->next; 
        }
    }

    
    
    
    printf("hola\n");
    printf("hsoek %s \n", iovc[0].iov_base);
    writev(handle_context->client_fd, iovc, bc);
    
    
    // close(handle_context->client_fd);
    
    }

