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

int main(void)
{
    ISoftware *s = init_library_api();
 
    printf("%u\n", s->nameLength);
    printf("%u\n", s->versionLength);
    printf("%u\n", s->structLength);
    printf("%s\n", s->blob);

    print_buf("Software Struct", (const unsigned char*) s, s->structLength / sizeof(char));

    free(s);
    return 0;
}