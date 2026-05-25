#ifndef WORKER_H
#define WORKER_H

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

void handle(void* args);
void process_header(struct pbuffer_chain *buffer_chain, struct header *h);




void handle_host();
void handle_connection();
void handle_content_length();
void handle_content_type();
void handle_user_agent();
void handle_accept();
void handle_accept_encoding();
void handle_accept_language();
void handle_accept_charset();
void handle_upgrade();
void handle_upgrade_insecure_requests();
void handle_websocket_key();
void handle_websocket_version();
void handle_websocket_protocol();
void handle_websocket_extensions();
void handle_origin();
void handle_access_control_allow_origin();
void handle_access_control_allow_methods();
void handle_access_control_allow_headers();
void handle_access_control_max_age();
void handle_access_control_allow_credentials();
void handle_cors_preflight();
void handle_sec_fetch_dest();
void handle_sec_fetch_mode();
void handle_sec_fetch_site();
void handle_sec_fetch_user();
void handle_cache_control();
void handle_if_modified_since();
void handle_if_none_match();
void handle_if_match();
void handle_if_unmodified_since();
void handle_if_range();
void handle_etag();
void handle_pragma();
void handle_authorization();
void handle_cookie();
void handle_set_cookie();
void handle_referer();
void handle_dnt();
void handle_sec_ch_ua();
void handle_sec_ch_ua_mobile();
void handle_sec_ch_ua_platform();
void handle_content_encoding();
void handle_transfer_encoding();
void handle_te();
void handle_accept_ranges();
void handle_range();
void handle_last_modified();
void handle_location();
void handle_server();
void handle_www_authenticate();
void handle_proxy_authenticate();
void handle_proxy_authorization();
void handle_keep_alive();
void handle_expect();
void handle_max_forwards();
void handle_vary();
void handle_retry_after();
void handle_date();
void handle_strict_transport_security();
void handle_content_security_policy();
void handle_x_frame_options();
void handle_x_content_type_options();
void handle_x_xss_protection();
void handle_x_powered_by();
void handle_x_requested_with();
void handle_x_forwarded_for();
void handle_x_forwarded_host();
void handle_x_forwarded_proto();
void handle_x_csrf_token();
void handle_x_idempotency_key();
void handle_x_rate_limit_limit();
void handle_x_rate_limit_remaining();
void handle_x_rate_limit_reset();
void handle_early_data();
void handle_sec_gpc();
void handle_save_data();
void handle_viewport_width();
void handle_device_memory();
void handle_downlink();
void handle_ect();
void handle_rtt();
void handle_sec_ch_prefers_color_scheme();
void handle_sec_ch_prefers_reduced_motion();
void handle_sec_ch_prefers_reduced_data();
void handle_sec_ch_ua_arch();
void handle_sec_ch_ua_model();
void handle_sec_ch_ua_bitness();
void handle_sec_ch_ua_full_version();
void handle_sec_ch_ua_full_version_list();
void handle_sec_ch_ua_wow64();
void handle_x_client_data();
void handle_x_forwarded_port();
void handle_x_original_forwarded_for();
void handle_x_proxy_user_ip();
void handle_x_real_ip();
void handle_x_uid();
void handle_x_wap_profile();
void handle_x_device_user_agent();
char* toLowerS(char* s);


#endif