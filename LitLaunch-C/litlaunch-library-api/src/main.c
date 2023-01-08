typedef struct SoftwareStruct ISoftware;

#include "litlaunch-library-api.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ISoftware* createSoftwareStruct(char name[], char version[]) {
    int goalSize = sizeof(int) * 3 + sizeof(char) * (strlen(name) + strlen(version));
    ISoftware* s = malloc(goalSize);
    s->nameLength = strlen(name);
    s->versionLength = strlen(version);
    strcpy(s->blob, name);
    strcat(s->blob, version);

    s->structLength = goalSize;
    return s;
}

int main()
{
    ISoftware *s;
 
    s = createSoftwareStruct("LitLaunch Library API", "0.1.0+build.1");
 
    printf("%u\n", s->nameLength);
    printf("%u\n", s->versionLength);
    printf("%u\n", s->structLength);
    printf("%s\n", s->blob);

    free(s);
    return 0;
}