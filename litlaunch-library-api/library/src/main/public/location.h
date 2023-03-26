#pragma once

#include "uthash/utstring.h"

#ifndef _LITLAUNCH_SLIM_
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

extern ResourceLocation *createResourceLocation(ResourceLocationNamespace _namespace, ResourceLocationPath _path);
extern const char* resourceLocationToString(ResourceLocation *ptr);
extern int resourceLocationSize(ResourceLocation *ptr);