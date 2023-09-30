#pragma once

#include <stddef.h>

typedef const char* ResourceLocationNamespace;
typedef unsigned int ResourceLocationNamespaceLength;
typedef const char* ResourceLocationPath;
typedef unsigned int ResourceLocationPathLength;
typedef const char* ResourceLocationTotal;
typedef unsigned int ResourceLocationTotalLength;

typedef struct ResourceLocationStruct
{
    ResourceLocationNamespace _namespace;
    ResourceLocationNamespaceLength _namespaceLength;
    ResourceLocationPath _path;
    ResourceLocationPathLength _pathLength;
    ResourceLocationTotal _total;
    ResourceLocationTotalLength _totalLength;
} ResourceLocation;

extern ResourceLocation *newResourceLocation(ResourceLocationNamespace _namespace, ResourceLocationNamespaceLength _namespaceLength,
    ResourceLocationPath _path, ResourceLocationPathLength _pathLength, ResourceLocationTotal _total, ResourceLocationTotalLength _totalLength);
extern ResourceLocationNamespace getResourceLocationNamespace(ResourceLocation *ptr);
extern ResourceLocationNamespaceLength getResourceLocationNamespaceLength(ResourceLocation *ptr);
extern ResourceLocationPath getResourceLocationPath(ResourceLocation *ptr);
extern ResourceLocationPathLength getResourceLocationPathLength(ResourceLocation *ptr);
extern ResourceLocationTotal getResourceLocationTotal(ResourceLocation *ptr);
extern ResourceLocationTotalLength getResourceLocationTotalLength(ResourceLocation *ptr);
extern void freeResourceLocation(ResourceLocation *ptr);