#include <string.h>
#include <stdlib.h>

#ifndef litlaunch_library_api_h__
#define litlaunch_library_api_h__

typedef struct SoftwareStruct {
    unsigned int    size;
    unsigned int    nameLength;
    unsigned int    versionLength;
    char            blob[0];
} ISoftware;

typedef struct LibraryStruct {
    unsigned int    size;
    ISoftware*      info;
} ILibrary;

typedef struct PluginStruct {
    unsigned int    size;
    ISoftware*      info;
    ILibrary*       requiredLibrary;
} IPlugin;

typedef struct ComponentStruct {
    unsigned int    size;
    unsigned int    nameLength;
    ILibrary*       componentLibrary;
    char            blob[0];
} IComponent;

extern ISoftware* createSoftwareStruct(const char name[], const char version[]);
extern ILibrary* createLibraryStruct(const char name[], const char version[]);
extern IPlugin* createPluginStruct(const char name[], const char version[], ILibrary* requiredLibrary);
extern IComponent* createComponentStruct(const char name[], ILibrary* componentLibrary);
extern ISoftware* initLibraryAPI(void);

#define NAME "LitLaunch Library API"
#define VERSION "0.1.0+build.1"

#endif  // litlaunch_library_api_h__