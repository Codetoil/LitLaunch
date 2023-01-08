typedef struct SoftwareStruct ISoftware;
typedef struct LibraryStruct ILibrary;
typedef struct ComponentStruct IComponent;

#include "litlaunch-library-api.h"

IComponent* createComponentStruct(const char name[], ILibrary* componentLibrary) {
    int blobSize = sizeof(char) * strlen(name);
    char *blob = malloc(blobSize);
    strcpy(blob, name);

    int size = sizeof(IComponent);

    IComponent* c = malloc(size);
    c->componentLibrary = componentLibrary;

    strcpy(c->blob, blob);
    free(blob);
    
    c->size = size;

    return c;
}