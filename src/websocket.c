#include<stdio.h> 
#include <openssl/sha.h>
#include <openssl/evp.h>

#include<websocket.h> 

#include <string.h>
#include <ctype.h>

void trim(char *s) {
    char *start = s;
    char *end;


    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    if (*start == 0) {
        *s = 0;
        return;
    }

    end = start + strlen(start) - 1;

   
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';


    memmove(s, start, end - start + 2);
}

char* ws_handshake(char* swk) {
    trim(swk); 
    char* ws_sec_key = malloc(
        (strlen(swk) + strlen("258EAFA5-E914-47DA-95CA-C5AB0DC85B11")) + 1
        ); 
     
    memcpy(ws_sec_key, swk, strlen(swk) + 1);
    
    
    strcat(ws_sec_key, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"); 
    
   
   
   
   char* hash = malloc(20);
    
    SHA1(ws_sec_key, strlen(ws_sec_key), hash);
    
       
    printf("%s", "polla\n");
   

   printf("%s ", ws_sec_key); 
   fflush(stdout);
   while(1);
   
    
    char* base64 = malloc(
        4 * ((strlen(hash) + 2) / 3) + 1
    );

    
    EVP_EncodeBlock(base64, hash, strlen(hash)); 
    
        
    printf("\n %s \n", base64); 
   fflush(stdout);
   

    
    return base64;
}