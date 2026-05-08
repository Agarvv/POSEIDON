#include <stddef.h>

struct parena {
    void* start;
    void* current;
    size_t size; 
};

void* palloc(size_t size, struct parena *arena);
void pfree(void* p, struct parena *arena);
void pinit(struct parena *arena);

