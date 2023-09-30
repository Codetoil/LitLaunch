#pragma once

#ifndef _LITLAUNCH_SLIM_
#include "uthash/utstring.h"

typedef UT_string* ResourceLocationNamespace;
typedef UT_string* ResourceLocationPath;
#else
typedef char ResourceLocationNamespace; // 2 bytes each to make 4 bytes total
typedef char ResourceLocationPath;
#endif

typedef struct ResourceLocationStruct
{
    ResourceLocationNamespace _namespace;
    ResourceLocationPath _path;
} ResourceLocation;

#ifndef _LITLAUNCH_SLIM_
extern ResourceLocation *newResourceLocation(const char* _namespace, const char* _path);

extern const char* getResourceLocationNamespace(ResourceLocation *ptr);
extern size_t getResourceLocationNamespaceLength(ResourceLocation *ptr);

extern const char* getResourceLocationPath(ResourceLocation *ptr);
extern size_t getResourceLocationPathLength(ResourceLocation *ptr);

extern const char* resourceLocationToString(ResourceLocation *ptr);
#else
extern ResourceLocation *newResourceLocation(char _namespace, char _path);

extern char getResourceLocationNamespace(ResourceLocation *ptr);

extern char getResourceLocationPath(ResourceLocation *ptr);
#endif
extern void freeResourceLocation(ResourceLocation *ptr);