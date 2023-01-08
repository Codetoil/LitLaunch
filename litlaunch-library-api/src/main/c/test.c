typedef struct SoftwareStruct ISoftware;

#include "litlaunch-library-api.h"
#include <stdio.h>

static void print_buf(const char *title, const unsigned char *buf, size_t buf_len)
{
    size_t i = 0;
    printf("%s\n", title);
    for(i = 0; i < buf_len; ++i)
    printf("%02X%s", buf[i],
             ( i + 1 ) % 16 == 0 ? "\n" : " " );
    printf("\n");

}

ISoftware *s;

int main(void)
{
    s = init_library_api();

    print_buf("LitLaunch Library API Software Struct", (const unsigned char*) s, s->structLength / sizeof(char));

    free(s);
    return 0;
}