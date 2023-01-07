#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct ISoftware {
    unsigned int    structLength;
    unsigned int    nameLength;
    unsigned int    versionLength;
    char            blob[0];
};

struct ISoftware* createSoftwareStruct(char name[], char version[]) {
    int goalSize = sizeof(int) * 3 + sizeof(char) * (strlen(name) + strlen(version));
    struct ISoftware* s = malloc(goalSize);
    s->nameLength = strlen(name);
    s->versionLength = strlen(version);
    strcpy(s->blob, name);
    strcat(s->blob, version);

    s->structLength = goalSize;
    return s;
}

int main()
{
    struct ISoftware *s;
 
    s = createSoftwareStruct("LitLaunch Library API", "0.1.0+build.1");
 
    printf("%u\n", s->nameLength);
    printf("%u\n", s->versionLength);
    printf("%u\n", s->structLength);
    printf("%s\n", s->blob);
    
    free(s);
    return 0;
}