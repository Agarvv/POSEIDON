#include<vector> 

extern "C" {    
    int ws_handler(struct hnd_context *handle_context, struct pbuffer_chain *buffer_chain, int len);
}

struct ws_frame_data {
    int len; 
    unsigned char* ptr; 
};

struct ws_frame_context {
    int opcode;
    int len;
    std::vector<ws_frame_data> ptrs;
}; 