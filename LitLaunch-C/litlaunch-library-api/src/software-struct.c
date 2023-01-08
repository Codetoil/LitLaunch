typedef struct SoftwareStruct ISoftware;

#include "litlaunch-library-api.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ISoftware* createSoftwareStruct(const char name[], const char version[]) {
    int blobLength = sizeof(char) * (strlen(name) + strlen(version));
    char *blob = malloc(blobLength);
    strcpy(blob, name);
    strcat(blob, version);

    int goalSize = sizeof(ISoftware) + blobLength;
    ISoftware* s = malloc(goalSize);
    s->nameLength = strlen(name);
    s->versionLength = strlen(version);

    strcpy(s->blob, blob);
    free(blob);

    s->structLength = goalSize;
    return s;
}

static void print_buf(const char *title, const unsigned char *buf, size_t buf_len)
{
    size_t i = 0;
    fprintf(stdout, "%s\n", title);
    for(i = 0; i < buf_len; ++i)
    fprintf(stdout, "%02X%s", buf[i],
             ( i + 1 ) % 16 == 0 ? "\n" : " " );
    printf("\n");

}

int main()
{
    ISoftware *s;
 
    s = createSoftwareStruct("LitLaunch Library API", "0.1.0+build.1");
 
    printf("%u\n", s->nameLength);
    printf("%u\n", s->versionLength);
    printf("%u\n", s->structLength);
    printf("%s\n", s->blob);

    print_buf("Software Struct", (const unsigned char*) s, s->structLength / sizeof(char));

    free(s);
    return 0;
}