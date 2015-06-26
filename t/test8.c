#include <stdio.h>
#include "td_private.h"

void debug_mem
  (void* _mem, unsigned int size);

#define MEMSIZE (1024 * 1024)

static
char area[ MEMSIZE ];

static
char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, char* argv[]) {
  fprintf(stderr, "\n\nTesting rehash\n\n");
  td_t td;
  tdt_t key, value;
  memset(area, 0, MEMSIZE);
  td_init_mem(&td, 0, (void*)area, MEMSIZE);
  int i=0; for (; i<30; i++) {
    char keymem[3], valmem[3];
    keymem[0] = alphabet[i % 7];
    keymem[1] = alphabet[i % 13];
    keymem[2] = alphabet[i % 23];
    valmem[0] = alphabet[25 - (i % 7)];
    valmem[1] = alphabet[25 - (i % 13)];
    valmem[2] = alphabet[25 - (i % 23)];
    key = (tdt_t){ keymem, 3 };
    value = (tdt_t){ valmem, 3 };
    fprintf(stderr, "\nPutting %-.*s -> %-.*s\n", 3, keymem, 3, valmem);
    CHECK(td_put(&td, &key, &value, 0));
    td_debug(&td);
  }
  td_debug(&td);
  debug_mem(area, 1024);
  return 0;
}
