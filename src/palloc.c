#include <stddef.h>
#include<palloc.h>
#include <sys/mman.h>  
#include <unistd.h>    
#include <sys/types.h> 



void pinit(struct parena *arena) {
    char* m = mmap(NULL, 1024 * 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); 
    arena->start = m;
    arena->size = 1024 * 1024;
}

void* palloc(size_t size, struct parena *arena) {
    arena->start = arena->start + size; 
}

void* pfree(void* p, struct parena *arena) {
    arena->start = arena->start - size; 
}