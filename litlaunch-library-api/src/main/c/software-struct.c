typedef struct SoftwareStruct ISoftware;

#include "litlaunch-library-api.h"

ISoftware* createSoftwareStruct(const char name[], const char version[]) {
    int blobSize = sizeof(char) * (strlen(name) + strlen(version));
    char *blob = malloc(blobSize);
    strcpy(blob, name);
    strcat(blob, version);

    int size = sizeof(ISoftware) + blobSize;
    ISoftware* s = malloc(size);
    s->nameLength = strlen(name);
    s->versionLength = strlen(version);

    strcpy(s->blob, blob);
    free(blob);

    s->size = size;
    return s;
}