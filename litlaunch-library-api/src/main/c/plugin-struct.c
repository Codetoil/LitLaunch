typedef struct SoftwareStruct ISoftware;
typedef struct LibraryStruct ILibrary;
typedef struct PluginStruct IPlugin;

#include "litlaunch-library-api.h"

IPlugin* createPluginStruct(const char name[], const char version[], ILibrary* requiredLibrary) {
    ISoftware* info = createSoftwareStruct(name, version);

    int size = sizeof(IPlugin);

    IPlugin* p = malloc(size);
    p->info = info;
    p->requiredLibrary = requiredLibrary;
    p->size = size;

    return p;
}