#ifndef WORKER_H
#define WORKER_H
#define PMETHOD_GET 1 
#define PMETHOD_HEAD 2 

#define PCONNECTION_UPGRADE 1 
#define PCONNECTION_KEEP_ALIVE 2
#define PCONNECTION_CLOSE 3


#include "parse.h" 

enum dispatch_table {
    CONENCTION,
    HOST
};

// POSEIDON Buffer Chain Node.
struct pbuffer_chain_node {
    int size;
    char* p; 
    struct pbuffer_chain_node *next; 
};

// POSEIDON Buffer Chain 
struct pbuffer_chain {
    struct pbuffer_chain_node *head; 
    struct pbuffer_chain_node *tail; 
    int len; 
};

struct res_builder {
    int method; 
    int connection; 
};

struct res {
    
};

void handle(void* args);
void process_header(struct pbuffer_chain *buffer_chain, struct header *h, struct res_builder *builder);



int handle_host(struct header h, struct res_builder *builder);
int handle_connection(struct header *h, struct res_builder *builder);
int handle_content_length(struct header h, struct res_builder *builder);
int handle_content_type(struct header h, struct res_builder *builder);
int handle_user_agent(struct header h, struct res_builder *builder);
int handle_accept(struct header h, struct res_builder *builder);
int handle_accept_encoding(struct header h, struct res_builder *builder);
int handle_accept_language(struct header h, struct res_builder *builder);
int handle_accept_charset(struct header h, struct res_builder *builder);
int handle_upgrade(struct header h, struct res_builder *builder);
int handle_upgrade_insecure_requests(struct header h, struct res_builder *builder);
int handle_websocket_key(struct header h, struct res_builder *builder);
int handle_websocket_version(struct header h, struct res_builder *builder);
int handle_websocket_protocol(struct header h, struct res_builder *builder);
int handle_websocket_extensions(struct header h, struct res_builder *builder);
int handle_origin(struct header h, struct res_builder *builder);
int handle_access_control_allow_origin(struct header h, struct res_builder *builder);
int handle_access_control_allow_methods(struct header h, struct res_builder *builder);
int handle_access_control_allow_headers(struct header h, struct res_builder *builder);
int handle_access_control_max_age(struct header h, struct res_builder *builder);
int handle_access_control_allow_credentials(struct header h, struct res_builder *builder);
int handle_cors_preflight(struct header h, struct res_builder *builder);
int handle_sec_fetch_dest(struct header h, struct res_builder *builder);
int handle_sec_fetch_mode(struct header h, struct res_builder *builder);
int handle_sec_fetch_site(struct header h, struct res_builder *builder);
int handle_sec_fetch_user(struct header h, struct res_builder *builder);
int handle_cache_control(struct header h, struct res_builder *builder);
int handle_if_modified_since(struct header h, struct res_builder *builder);
int handle_if_none_match(struct header h, struct res_builder *builder);
int handle_if_match(struct header h, struct res_builder *builder);
int handle_if_unmodified_since(struct header h, struct res_builder *builder);
int handle_if_range(struct header h, struct res_builder *builder);
int handle_etag(struct header h, struct res_builder *builder);
int handle_pragma(struct header h, struct res_builder *builder);
int handle_authorization(struct header h, struct res_builder *builder);
int handle_cookie(struct header h, struct res_builder *builder);
int handle_set_cookie(struct header h, struct res_builder *builder);
int handle_referer(struct header h, struct res_builder *builder);
int handle_dnt(struct header h, struct res_builder *builder);
int handle_sec_ch_ua(struct header h, struct res_builder *builder);
int handle_sec_ch_ua_mobile(struct header h, struct res_builder *builder);
int handle_sec_ch_ua_platform(struct header h, struct res_builder *builder);
int handle_content_encoding(struct header h, struct res_builder *builder);
int handle_transfer_encoding(struct header h, struct res_builder *builder);
int handle_te(struct header h, struct res_builder *builder);
int handle_accept_ranges(struct header h, struct res_builder *builder);
int handle_range(struct header h, struct res_builder *builder);
int handle_last_modified(struct header h, struct res_builder *builder);
int handle_location(struct header h, struct res_builder *builder);
int handle_server(struct header h, struct res_builder *builder);
int handle_www_authenticate(struct header h, struct res_builder *builder);
int handle_proxy_authenticate(struct header h, struct res_builder *builder);
int handle_proxy_authorization(struct header h, struct res_builder *builder);
int handle_keep_alive(struct header h, struct res_builder *builder);
int handle_expect(struct header h, struct res_builder *builder);
int handle_max_forwards(struct header h, struct res_builder *builder);
int handle_vary(struct header h, struct res_builder *builder);
int handle_retry_after(struct header h, struct res_builder *builder);
int handle_date(struct header h, struct res_builder *builder);
int handle_strict_transport_security(struct header h, struct res_builder *builder);
int handle_content_security_policy(struct header h, struct res_builder *builder);
int handle_x_frame_options(struct header h, struct res_builder *builder);
int handle_x_content_type_options(struct header h, struct res_builder *builder);
int handle_x_xss_protection(struct header h, struct res_builder *builder);
int handle_x_powered_by(struct header h, struct res_builder *builder);
int handle_x_requested_with(struct header h, struct res_builder *builder);
int handle_x_forwarded_for(struct header h, struct res_builder *builder);
int handle_x_forwarded_host(struct header h, struct res_builder *builder);
int handle_x_forwarded_proto(struct header h, struct res_builder *builder);
int handle_x_csrf_token(struct header h, struct res_builder *builder);
int handle_x_idempotency_key(struct header h, struct res_builder *builder);
int handle_x_rate_limit_limit(struct header h, struct res_builder *builder);
int handle_x_rate_limit_remaining(struct header h, struct res_builder *builder);
int handle_x_rate_limit_reset(struct header h, struct res_builder *builder);
int handle_early_data(struct header h, struct res_builder *builder);
int handle_sec_gpc(struct header h, struct res_builder *builder);
int handle_save_data(struct header h, struct res_builder *builder);
int handle_viewport_width(struct header h, struct res_builder *builder);
int handle_device_memory(struct header h, struct res_builder *builder);
int handle_downlink(struct header h, struct res_builder *builder);
int handle_ect(struct header h, struct res_builder *builder);
int handle_rtt(struct header h, struct res_builder *builder);
int handle_sec_ch_prefers_color_scheme(struct header h, struct res_builder *builder);
int handle_sec_ch_prefers_reduced_motion(struct header h, struct res_builder *builder);
int handle_sec_ch_prefers_reduced_data(struct header h, struct res_builder *builder);
int handle_sec_ch_ua_arch(struct header h, struct res_builder *builder);
int handle_sec_ch_ua_model(struct header h, struct res_builder *builder);
int handle_sec_ch_ua_bitness(struct header h, struct res_builder *builder);
int handle_sec_ch_ua_full_version(struct header h, struct res_builder *builder);
int handle_sec_ch_ua_full_version_list(struct header h, struct res_builder *builder);
int handle_sec_ch_ua_wow64(struct header h, struct res_builder *builder);
int handle_x_client_data(struct header h, struct res_builder *builder);
int handle_x_forwarded_port(struct header h, struct res_builder *builder);
int handle_x_original_forwarded_for(struct header h, struct res_builder *builder);
int handle_x_proxy_user_ip(struct header h, struct res_builder *builder);
int handle_x_real_ip(struct header h, struct res_builder *builder);
int handle_x_uid(struct header h, struct res_builder *builder);
int handle_x_wap_profile(struct header h, struct res_builder *builder);
int handle_x_device_user_agent(struct header h, struct res_builder *builder);


char* toLowerS(char* s);


#endif