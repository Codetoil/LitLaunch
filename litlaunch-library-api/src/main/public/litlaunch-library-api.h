#pragma once

#include <string.h>
#include <stdlib.h>

typedef struct SoftwareStruct {
    unsigned int    size;
    void*           name;       //UT_string
    void*           version;    //UT_string
} ISoftware;

typedef struct LibraryStruct ILibrary;

typedef struct LibraryStruct {
    unsigned int    size;
    ISoftware*      info;
    ILibrary*       parentLibrary;
} ILibrary;

/* typedef struct ComponentStruct {
    unsigned int    size;
    unsigned int    nameLength;
    ILibrary*       componentLibrary;
    char            blob[0];
} IComponent; */

extern ISoftware* createSoftwareStruct(const char name[], const char version[]);
extern ILibrary* createLibraryStruct(const char name[], const char version[], ILibrary* parentLibrary);
extern void freeSoftwareStruct(ISoftware* software);
extern void freeLibraryStruct(ILibrary* library);

// extern IComponent* createComponentStruct(const char name[], ILibrary* componentLibrary);

extern ISoftware* initLibraryAPI(void);

#define NAME "LitLaunch Library API"
#define VERSION "0.1.0+build.2"