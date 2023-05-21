#include <stdlib.h>
#include "litlaunch/litlaunch-library-api.h"
#include "litlaunch/dependencies.h"

Module *moduleRegistry = NULL;

Module *initLibraryApi(void)
{
    ResourceLocation *location;
#ifndef _LITLAUNCH_SLIM_
    location = newResourceLocation("litlaunch", "litlaunch_library_api");
#else
    location = (ResourceLocation*) malloc(sizeof(*location));
    location->_namespace = 0x0001; // 0x0001 is the litlaunch namespace
    location->_path = 0x0000; // 0x00010000 is the resource location of the litlaunch library api
#endif
    return newModule(location, NULL, NULL);
}

Module *newModule(ResourceLocation* id, Version* version, DependencyDict* dependencyDict)
{
    Module* module = (Module*) malloc(sizeof(*module));
    module->id = id;
    module->version = version;
    module->dependencyDict = dependencyDict;
    HASH_ADD_KEYPTR(hh, moduleRegistry, id, sizeof(*id), module);
    return module;
}

void freeModule(Module* ptr)
{
    HASH_DEL(moduleRegistry, ptr);
    free(ptr);
}

ResourceLocation *newResourceLocation(const char* _namespace, const char* _path)
{
    ResourceLocation* ptr = (ResourceLocation*) malloc(sizeof(*ptr));

    utstring_new(ptr->_namespace);
    utstring_new(ptr->_path);
    utstring_printf(ptr->_namespace, "%s", _namespace);
    utstring_printf(ptr->_path, "%s", _path);
    return ptr;
}

void freeResourceLocation(ResourceLocation *ptr)
{
#ifndef _LITLAUNCH_SLIM_
    utstring_free(ptr->_namespace);
    utstring_free(ptr->_path);
#endif
    free(ptr);
}

const char* getResourceLocationNamespace(ResourceLocation *ptr)
{
#ifndef _LITLAUNCH_SLIM_
    return utstring_body(ptr->_namespace);
#endif
}

size_t getResourceLocationNamespaceLength(ResourceLocation *ptr)
{
#ifndef _LITLAUNCH_SLIM_
    return utstring_len(ptr->_namespace);
#endif
}

const char* getResourceLocationPath(ResourceLocation *ptr)
{
#ifndef _LITLAUNCH_SLIM_
    return utstring_body(ptr->_path);
#endif
}

size_t getResourceLocationPathLength(ResourceLocation *ptr)
{
#ifndef _LITLAUNCH_SLIM_
    return utstring_len(ptr->_path);
#endif
}

const char* resourceLocationToString(ResourceLocation *ptr)
{
    const char* _namespace = getResourceLocationNamespace(ptr);
    const char* _path = getResourceLocationPath(ptr);
    char* result = malloc(getResourceLocationNamespaceLength(ptr) 
        + sizeof(char) + getResourceLocationPathLength(ptr));
    strcpy(result, _namespace);
    strcat(result, ":");
    strcat(result, _path);
    return result;
}