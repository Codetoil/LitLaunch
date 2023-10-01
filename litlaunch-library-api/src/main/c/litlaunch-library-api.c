#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "litlaunch/litlaunch-library-api.h"
#include "litlaunch/location.h"
#include "litlaunch/dependencies.h"

// New entries are added to the top of the list
Module *moduleRegistryTop = NULL;
Module *moduleRegistryBottom = NULL;

const char* litlaunchNamespace = "litlaunch";

Module *initLibraryApi(void)
{
    ResourceLocation *versionLocation = newResourceLocation(litlaunchNamespace, 10, "litlaunch_library_api_version", 30, "litlaunch:litlaunch_library_api_version", 40);
    Version *version = newVersion(versionLocation, "0.2.1", 6);
    ResourceLocation *moduleLocation = newResourceLocation(litlaunchNamespace, 10, "litlaunch_library_api", 22, "litlaunch:litlaunch_library_api", 32);
    return newModule(moduleLocation, version, NULL);
}

Version *newVersion(ResourceLocation* id, VersionValue version, VersionValueLength versionLength)
{
    Version* versionStruct = (Version*) malloc(sizeof(*versionStruct) + versionLength);
    versionStruct->id = id;
    versionStruct->versionValue = version;
    versionStruct->versionValueLength = versionLength;
    return versionStruct;
}

VersionValue getVersionValue(Version *ptr)
{
    return ptr->versionValue;
}

VersionValueLength getVersionValueLength(Version *ptr)
{
    return ptr->versionValueLength;
}

void freeVersion(Version* ptr)
{
    free(ptr);
}


Module *newModule(ResourceLocation* id, Version* version, DependencyDict* dependencyDict)
{
    Module* module = (Module*) malloc(sizeof(*module));
    module->id = id;
    module->version = version;
    module->dependencyDict = dependencyDict;
    module->next = NULL;
    module->prev = moduleRegistryTop;
    if (!moduleRegistryBottom)
    {
        moduleRegistryBottom = module;
    }
    if (moduleRegistryTop)
    {
        moduleRegistryTop->next = module;
    }
    moduleRegistryTop = module;
    return module;
}

void freeModule(Module* ptr)
{
    Module* next = ptr->next;
    Module* prev = ptr->prev;
    if (next)
    {
        next->prev=prev;
    }
    if (prev)
    {
        prev->next=next;
    }
    free(ptr);
}


void freeResourceLocation(ResourceLocation *ptr)
{
    free(ptr);
}

ResourceLocation *newResourceLocation(ResourceLocationNamespace _namespace, ResourceLocationNamespaceLength _namespaceLength,
    ResourceLocationPath _path, ResourceLocationPathLength _pathLength, ResourceLocationTotal _total, ResourceLocationTotalLength _totalLength)
{
    ResourceLocation* ptr = (ResourceLocation*) malloc(sizeof(*ptr) + (_namespaceLength + _pathLength + _totalLength) * sizeof(char));

    ptr->_namespace = _namespace;
    ptr->_namespaceLength = _namespaceLength;
    ptr->_path = _path;
    ptr->_pathLength = _pathLength;
    ptr->_total = _total;
    ptr->_totalLength = _totalLength;
    return ptr;
}

ResourceLocationNamespace getResourceLocationNamespace(ResourceLocation *ptr)
{
    return ptr->_namespace;
}

ResourceLocationNamespaceLength getResourceLocationNamespaceLength(ResourceLocation *ptr)
{
    return ptr->_namespaceLength;
}

ResourceLocationPath getResourceLocationPath(ResourceLocation *ptr)
{
    return ptr->_path;
}

ResourceLocationPathLength getResourceLocationPathLength(ResourceLocation *ptr)
{
    return ptr->_pathLength;
}

ResourceLocationNamespace getResourceLocationTotal(ResourceLocation *ptr)
{
    return ptr->_total;
}

ResourceLocationNamespaceLength getResourceLocationTotalLength(ResourceLocation *ptr)
{
    return ptr->_totalLength;
}