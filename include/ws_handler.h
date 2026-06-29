
extern "C" {    
    int ws_handler(struct hnd_context *handle_context, struct pbuffer_chain *buffer_chain, int len);
}

struct ws_frame_context {
    int opcode;
    int len;
    void* data;
};