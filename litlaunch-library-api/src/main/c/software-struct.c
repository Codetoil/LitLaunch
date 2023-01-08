typedef struct SoftwareStruct ISoftware;

#include "litlaunch-library-api.h"

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