/*
#include<iostream>
#include<stdio.h>
#include<worker.h>
#include<main.h>
#include<ws_handler.h>

extern "C" {
    
int ws_handler(struct hnd_context *handle_context, struct pbuffer_chain *buffer_chain, int len) {
     
    unsigned char* ptr = static_cast<unsigned char*>(buffer_chain->head->p);
    
    bool mask = (ptr[1] & 0x80);
     if(!mask) {
         std::cout << "No Mask From Client. Closing Connection." << std::endl;
     }
    
    std::unordered_map<int, ws_frame_context> contexts; 
     
     struct ws_frame_context context; 
    
    
    unsigned char tb = ptr[1]; 
    bool mask = (tb & 0x80);
    int l = (tb & 0x7F); 
    
    switch(127 - l) {
    case 1: {
        std::cout << "Len Is 126." << std::endl; 
        unsigned char trb = ptr[2]; 
        unsigned char fb = ptr[3]; 
        
        l = l + (trb + fb);
        
        break;
    }
    case 0: {
        std::cout << "Len Is 127." << std::endl; 
        unsigned char trb = ptr[2]; 
        unsigned char fb = ptr[3]; 
        unsigned char ffb = ptr[4]; 
        unsigned char sb = ptr[5]; 
        unsigned char eb = ptr[5]; 
        unsigned char bb = ptr[6]; 
        unsigned char tb = ptr[7]; 
        
        l = l + (trb + fb + ffb + sb + eb + bb + tb);
        break;
    }
    default: 
        std::cout << "Not Exceptional Length." << std::endl; 
        break;
    }   
    
    printf("Final Len: %d\n", l);
    
    int opcode = (ptr[0] & 0x0F);
    context.opcode = opcode; 
    
    
    int length = 0; 
    int flen = ptr[1] & 0x7F;
    unsigned char* data; 
    
    if(flen == 126) {
        length = flen + ptr[2] + ptr[3]; 
        std::cout << "Exceptional Length" << std::endl; 
        context.len = length; 
        *data = ptr[7]; 
    } else if (flen == 127) {
        length = flen + ptr[2] + ptr[3]+ ptr[4] + ptr[5] + ptr[6] + ptr[7] + ptr[8] + ptr[9]; 
        *data = ptr[13]; 
        context.len = length; 
        
        std::cout << "Exceptional Length" << std::endl; 
    }
    
    std::cout << "Not Exceptional Length" << std::endl; 
    context.len = flen; 
    
    
    *data = ptr[5]; 
    
    
    switch(opcode) {
        case 0x01:
             std::cout << "TEXT" << std::endl;
             
             break;
        default:
             std::cout << "NONE" << std::endl;
    }
    
    
    
    contexts.emplace(handle_context->client_fd, std::move(context));
    
    
    // if Not FIN
    if(!(ptr[0] & 0x80)) {
        context.ptrs.push_back({ flen, data });
    }
    
    std::cout << "End of Frames." << std::endl;
    
    
    
    return 0;
}

}
*/