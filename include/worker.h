#ifndef WORKER_H
#define WORKER_H
#define PMETHOD_GET 1 
#define PMETHOD_HEAD 2 

#define PCONNECTION_UPGRADE 1 
#define PCONNECTION_KEEP_ALIVE 2
#define PCONNECTION_CLOSE 3

#define PCONNECTION_UPGRADE_WS 1

#include "parse.h" 

enum dispatch_table {
    CONENCTION,
    HOST
};

struct patricia_tree_node {
    void(*handler)();
    struct pbuffer_chain_node *children;
};

struct patricia_tree {
    struct patricia_tree_node *root;
};

// POSEIDON Buffer Chain Node.
struct pbuffer_chain_node {
    int size;
    int fsize;
    void* p; 
    struct pbuffer_chain_node *next; 
};

// POSEIDON Buffer Chain 
struct pbuffer_chain {
    struct pbuffer_chain_node *head; 
    struct pbuffer_chain_node *tail; 
    int len; 
    struct parena *arena;
};

void* pbuffer_chain_w(struct pbuffer_chain *buffer_chain, struct pbuffer_chain_node *node, int q, void* c);

struct res_builder {
    int method; 
    int connection; 
    int upgrade; 
    char* ws_key;
    int err; // 1 when header processing error occurrs
};

struct res {
    
};

void handle(void* args);

void process_header(struct pbuffer_chain *buffer_chain, struct header *h, struct res_builder *builder, struct hnd_context* handle_context);


char* handle_host(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_connection(struct header *h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_content_length(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_content_type(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_user_agent(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_accept(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_accept_encoding(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_accept_language(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_accept_charset(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_upgrade(struct header *h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_upgrade_insecure_requests(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_websocket_key(struct header *h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_websocket_version(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_websocket_protocol(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_websocket_extensions(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_origin(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_access_control_allow_origin(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_access_control_allow_methods(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_access_control_allow_headers(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_access_control_max_age(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_access_control_allow_credentials(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_cors_preflight(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_fetch_dest(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_fetch_mode(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_fetch_site(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_fetch_user(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_cache_control(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_if_modified_since(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_if_none_match(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_if_match(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_if_unmodified_since(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_if_range(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_etag(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_pragma(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_authorization(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_cookie(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_set_cookie(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_referer(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_dnt(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_ua(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_ua_mobile(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_ua_platform(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_content_encoding(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_transfer_encoding(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_te(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_accept_ranges(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_range(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_last_modified(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_location(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_server(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_www_authenticate(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_proxy_authenticate(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_proxy_authorization(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_keep_alive(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_expect(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_max_forwards(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_vary(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_retry_after(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_date(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_strict_transport_security(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_content_security_policy(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_frame_options(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_content_type_options(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_xss_protection(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_powered_by(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_requested_with(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_forwarded_for(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_forwarded_host(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_forwarded_proto(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_csrf_token(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_idempotency_key(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_rate_limit_limit(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_rate_limit_remaining(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_rate_limit_reset(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_early_data(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_gpc(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_save_data(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_viewport_width(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_device_memory(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_downlink(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_ect(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_rtt(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_prefers_color_scheme(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_prefers_reduced_motion(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_prefers_reduced_data(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_ua_arch(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_ua_model(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_ua_bitness(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_ua_full_version(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_ua_full_version_list(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_sec_ch_ua_wow64(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_client_data(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_forwarded_port(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_original_forwarded_for(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_proxy_user_ip(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_real_ip(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_uid(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_wap_profile(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);
char* handle_x_device_user_agent(struct header h, struct res_builder *builder, int r, char* dv, struct hnd_context* handle_context);




int handle_req_line(char* method, char* path, char* version, char* body, struct res_builder *builder);

struct pbuffer_chain* res(struct res_builder *builder, struct hnd_context* handle_context);

void pbuffer_chain_write(struct pbuffer_chain *buffer_chain, char* c);

char* toLowerS(char* s);

void handle_ws(void* args);



#endif