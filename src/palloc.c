#include <stddef.h>
#include<palloc.h>
#include <sys/mman.h>  
#include <unistd.h>    
#include <sys/types.h> 



void pinit(struct parena *arena) {
    char* m = mmap(NULL, 1024 * 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); 
    arena->start = m;
    arena->size = 1024 * 1024;
    arena->current = m;
}

void* palloc(size_t size, struct parena *arena) {
    arena->current = arena->current + size; 
    
    return arena->current - size; 
}

/*void pfree(void* p, struct parena *arena) {
    arena->current = arena->start - size; 
}*/