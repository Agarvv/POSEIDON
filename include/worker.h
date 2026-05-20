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

#endif