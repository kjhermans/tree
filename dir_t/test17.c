#include <stdlib.h>
#include <stdio.h>
#include "td_private.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

static char* file = "/tmp/foo.db";

int main(int argc, char* argv[]) {

  srand(time(0));

  unsigned i;

//#ifdef DYNAMIC
  char** entries = NULL;
  unsigned nentries = 0;

  for (i=0; i < 26; i++) {
    unsigned j;
    char* entry = (char*)malloc(4);

    snprintf(entry, 4, "%c%c%c", ('a'+i), ('a'+i), ('a'+i));
    for (j=0; j < i + 1; j++) {
      if (nentries) {
        unsigned pos = (unsigned)(rand()) % (nentries);
        ++nentries;
        entries = (char**)realloc(entries, nentries * sizeof(char*));
        memmove(&(entries[ pos + 1 ]),
                &(entries[ pos ]),
                sizeof(char*) * (nentries - (pos + 1)));
        entries[ pos ] = entry;
      } else {
        entries = (char**)malloc(sizeof(char*));
        entries[ 0 ] = entry;
        nentries = 1;
      }
    }
  }
#if 0
//#else
  
  char* entries[] = {
    "lll",
    "yyy",
    "mmm",
    "qqq",
    "ppp",
    "mmm",
    "ttt",
    "lll",
    "jjj",
    "sss",
    "vvv",
    "zzz",
    "yyy",
    "qqq",
    "xxx",
    "ooo",
    "lll",
    "vvv",
    "uuu",
    "yyy",
    "uuu",
    "ttt",
    "ppp",
    "vvv",
    "www",
    "qqq",
    "ccc",
    "xxx",
    "yyy",
    "www",
    "lll",
    "ggg",
    "ttt",
    "zzz",
    "www",
    "lll",
    "www",
    "xxx",
    "zzz",
    "ooo",
    "zzz",
    "rrr",
    "uuu",
    "ttt",
    "hhh",
    "nnn",
    "rrr",
    "xxx",
    "yyy",
    "xxx",
    "uuu",
    "eee",
    "ttt",
    "kkk",
    "uuu",
    "iii",
    "yyy",
    "yyy",
    "kkk",
    "sss",
    "www",
    "qqq",
    "eee",
    "yyy",
    "uuu",
    "ggg",
    "zzz",
    "rrr",
    "yyy",
    "jjj",
    "eee",
    "kkk",
    "rrr",
    "mmm",
    "ppp",
    "www",
    "hhh",
    "mmm",
    "zzz",
    "ooo",
    "yyy",
    "nnn",
    "www",
    "zzz",
    "xxx",
    "uuu",
    "xxx",
    "yyy",
    "jjj",
    "iii",
    "ggg",
    "xxx",
    "xxx",
    "qqq",
    "ttt",
    "rrr",
    "iii",
    "sss",
    "ooo",
    "ttt",
    "rrr",
    "nnn",
    "zzz",
    "vvv",
    "uuu",
    "iii",
    "ooo",
    "jjj",
    "mmm",
    "ddd",
    "zzz",
    "lll",
    "rrr",
    "ooo",
    "iii",
    "yyy",
    "www",
    "kkk",
    "xxx",
    "nnn",
    "www",
    "fff",
    "www",
    "nnn",
    "ttt",
    "sss",
    "www",
    "vvv",
    "nnn",
    "sss",
    "vvv",
    "zzz",
    "qqq",
    "eee",
    "zzz",
    "uuu",
    "uuu",
    "ppp",
    "www",
    "ooo",
    "iii",
    "sss",
    "yyy",
    "uuu",
    "qqq",
    "lll",
    "vvv",
    "ccc",
    "rrr",
    "hhh",
    "ttt",
    "xxx",
    "sss",
    "vvv",
    "sss",
    "xxx",
    "uuu",
    "yyy",
    "mmm",
    "nnn",
    "ppp",
    "ppp",
    "vvv",
    "rrr",
    "yyy",
    "yyy",
    "zzz",
    "www",
    "ddd",
    "qqq",
    "lll",
    "mmm",
    "vvv",
    "ppp",
    "www",
    "qqq",
    "nnn",
    "yyy",
    "www",
    "ooo",
    "nnn",
    "sss",
    "xxx",
    "www",
    "www",
    "nnn",
    "qqq",
    "sss",
    "sss",
    "rrr",
    "ttt",
    "vvv",
    "fff",
    "kkk",
    "sss",
    "ttt",
    "zzz",
    "qqq",
    "mmm",
    "hhh",
    "www",
    "xxx",
    "www",
    "rrr",
    "jjj",
    "ttt",
    "ggg",
    "zzz",
    "ggg",
    "fff",
    "ooo",
    "kkk",
    "xxx",
    "rrr",
    "eee",
    "uuu",
    "ooo",
    "ppp",
    "vvv",
    "sss",
    "sss",
    "yyy",
    "xxx",
    "kkk",
    "xxx",
    "yyy",
    "zzz",
    "ggg",
    "ppp",
    "ttt",
    "ppp",
    "www",
    "vvv",
    "ttt",
    "ppp",
    "zzz",
    "lll",
    "hhh",
    "zzz",
    "vvv",
    "ttt",
    "jjj",
    "ttt",
    "iii",
    "uuu",
    "ooo",
    "www",
    "sss",
    "www",
    "fff",
    "zzz",
    "lll",
    "ttt",
    "ddd",
    "ddd",
    "ooo",
    "yyy",
    "bbb",
    "mmm",
    "zzz",
    "ppp",
    "ooo",
    "nnn",
    "yyy",
    "vvv",
    "mmm",
    "qqq",
    "iii",
    "xxx",
    "mmm",
    "yyy",
    "mmm",
    "rrr",
    "xxx",
    "kkk",
    "ttt",
    "kkk",
    "ccc",
    "jjj",
    "kkk",
    "rrr",
    "jjj",
    "qqq",
    "uuu",
    "ppp",
    "ttt",
    "sss",
    "jjj",
    "ooo",
    "xxx",
    "uuu",
    "zzz",
    "nnn",
    "iii",
    "sss",
    "yyy",
    "vvv",
    "lll",
    "vvv",
    "qqq",
    "hhh",
    "sss",
    "uuu",
    "zzz",
    "sss",
    "uuu",
    "vvv",
    "hhh",
    "yyy",
    "ooo",
    "uuu",
    "rrr",
    "bbb",
    "rrr",
    "ppp",
    "vvv",
    "ggg",
    "rrr",
    "hhh",
    "qqq",
    "uuu",
    "fff",
    "lll",
    "jjj",
    "zzz",
    "xxx",
    "qqq",
    "uuu",
    "fff",
    "zzz",
    "vvv",
    "nnn",
    "yyy",
    "mmm",
    "xxx",
    "kkk",
    "ppp",
    "ppp",
    "xxx",
    "zzz",
    "qqq",
    "xxx",
    "zzz",
    "nnn",
    "ttt",
    "zzz",
    "vvv",
    "rrr",
    "www",
    "vvv",
    "aaa",
    0
  };
  unsigned nentries=351;

#endif

  td_t td;

  if (td_open(&td, file, TDFLG_EXTEND, O_RDWR|O_CREAT|O_TRUNC, 0664)) {
    fprintf(stderr, "Could not open file '%s'.\n", file);
    return -1;
  }

  printf("char* entries[] = {\n");
  for (i=0; i < nentries; i++) {
    char* entry = entries[ i ];
    printf("  \"%s\",\n", entry);
  }
  printf("  0\n};\nunsigned nentries=%u;\n", nentries);
  
  for (i=0; i < nentries; i++) {
    char* entry = entries[ i ];
    tdt_t key = { entry, strlen(entry) };
    tdt_t val = { entry, strlen(entry) };
    fprintf(stderr, "Inserting %s -> %s\n", entry, entry);
    CHECK(td_put(&td, &key, &val, TDFLG_DUPLKEYS));
  }

  unsigned nletters = 26;

  for (i=0; i < nletters; i++) {
    unsigned j = i, n = i;
    char keystring[ 4 ];
    tdt_t searchkey;
    tdc_t cursor;

//    snprintf(keystring, 4, "%c%c%c", (i+'a'), (i+'a'), (i+'a'));
    snprintf(keystring, 4, "%c%c", (i+'a'), (i+'a'));
    searchkey = (tdt_t){ keystring, strlen(keystring) };
    CHECK(tdc_init(&td, &cursor));
    fprintf(stderr, " SEEK '%s'\n", keystring);
    CHECK(tdc_mov(&cursor, &searchkey, TDFLG_EXACT|TDFLG_PARTIAL));
    while (1) {
      int r;
      char findbuf[ 32 ];
      tdt_t findkey, findval;

      findkey = (tdt_t){ findbuf, 16 };
      findval = (tdt_t){ findbuf + 16, 16 };
      switch (r = tdc_nxt(&cursor, &findkey, &findval, 0)) {
      case 0:
        {
          char expect[ 4 ];
          snprintf(expect, 4, "%c%c%c", (j+'a'), (j+'a'), (j+'a'));
          if (n-- == 0) {
            if (++j == nletters) { goto ENDWHILE; }
            n = j;
          }
          fprintf(stderr, "  EXPECT %s", expect);
          fprintf(stderr, "  FOUND '%-.*s'\n", findkey.size, (char*)(findkey.data));
          if (memcmp(expect, findkey.data, 3)) {
            fprintf(stderr, "Bad value.\n");
            td_debug(&td);
            return ~0;
          }
        }
        break;
      case TDERR_NOTFOUND:
        fprintf(stderr, "  EOF\n");
        return ~0;
      default:
        return r;
      }
    }
ENDWHILE: ;
  }
  return 0;
}
