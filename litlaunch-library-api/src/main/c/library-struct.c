typedef struct SoftwareStruct ISoftware;
typedef struct LibraryStruct ILibrary;

#include "litlaunch-library-api.h"

ILibrary* createLibraryStruct(const char name[], const char version[]) {
    ISoftware* s = createSoftwareStruct(name, version);

    int size = sizeof(ILibrary);

    ILibrary* l = malloc(size);
    l->info = s;
    l->size = size;

    return l;
}