/* #ifndef WS_HANDLER_H
#define WS_HANDLER_H

#ifdef __cplusplus
#include <vector>

extern "C" {
#endif


int ws_handler(struct hnd_context *handle_context, struct pbuffer_chain *buffer_chain, int len);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

struct ws_frame_data {
    int len; 
    unsigned char* ptr; 
};

struct ws_frame_context {
    int opcode;
    int len;
    std::vector<ws_frame_data> ptrs;
};
#endif

#endif*/