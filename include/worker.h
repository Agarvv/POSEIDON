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



void handle_connection();
void handle_content_length();
void handle_accept();
void handle_accept_encoding();
void handle_accept_language();
void handle_accept_charset();
void handle_authorization();
void handle_cache_control();
void handle_cookie();
void handle_host();
void handle_origin();
void handle_referer();
void handle_user_agent();
void handle_upgrade();
void handle_via();
void handle_x_forwarded_for();
void handle_x_requested_with();
void handle_if_modified_since();
void handle_if_none_match();
void handle_range();
void handle_te();
void handle_content_type();
void handle_content_encoding();
void handle_transfer_encoding();
void handle_keep_alive();
void handle_expect();
void handle_pragma();
void handle_warning();
void handle_age();
void handle_etag();
void handle_location();
void handle_server();
void handle_set_cookie();
void handle_x_powered_by();
void handle_x_frame_options();
void handle_x_content_type_options();
void handle_x_xss_protection();
void handle_strict_transport_security();
void handle_content_security_policy();
void handle_access_control_allow_origin();
void handle_access_control_allow_methods();
void handle_access_control_allow_headers();
void handle_access_control_max_age();
void handle_access_control_allow_credentials();
void handle_dnt();
void handle_sec_ch_ua();
void handle_sec_ch_ua_mobile();
void handle_sec_ch_ua_platform();
void handle_sec_fetch_dest();
void handle_sec_fetch_mode();
void handle_sec_fetch_site();
void handle_sec_fetch_user();
void handle_last_modified();
void handle_if_match();
void handle_if_range();
void handle_if_unmodified_since();
void handle_accept_patch();
void handle_accept_ranges();
void handle_allow();
void handle_alt_svc();
void handle_date();
void handle_retry_after();
void handle_vary();
void handle_www_authenticate();
void handle_proxy_authenticate();
void handle_proxy_authorization();
void handle_from();
void handle_max_forwards();
void handle_priority();
void handle_tk();
void handle_x_cache();
void handle_x_cache_hits();
void handle_x_ua_compatible();
void handle_x_csrf_token();
void handle_x_idempotency_key();
void handle_x_rate_limit_limit();
void handle_x_rate_limit_remaining();
void handle_x_rate_limit_reset();
void handle_x_total_count();
void handle_clear_site_data();
void handle_cross_origin_embedder_policy();
void handle_cross_origin_opener_policy();
void handle_cross_origin_resource_policy();
void handle_expect_ct();
void handle_feature_policy();
void handle_nela();
void handle_report_to();
void handle_sourcemap();
void handle_x_dns_prefetch_control();
void handle_x_download_options();
void handle_x_permitted_cross_domain_policies();
void handle_x_redirect_by();
void handle_x_request_id();
void handle_x_runtime();
void handle_x_version();
void handle_x_backend_server();
void handle_x_forwarded_host();
void handle_x_forwarded_proto();
char* toLowerS(char* s);


#endif