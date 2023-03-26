#include <stdlib.h>
#include "litlaunch/litlaunch-library-api.h"
#include "litlaunch/library.h"
#include "litlaunch/dependencies.h"

LibraryImpl *initLibraryApi(void)
{
    LibraryTemplate *litlaunchLibraryApiTemplate = NULL; //createLibraryTemplate();

    ResourceLocation *location = newResourceLocation();
#ifndef _LITLAUNCH_SLIM_
    setResourceLocation(location, "litlaunch", "litlaunch_library_api");
#else
    location->_namespace = 0x0001; // 0x0001 is the litlaunch namespace
    location->_path = 0x0000; // 0x00010000 is the resource location of the litlaunch library api
#endif

    LibraryImpl *result = createLibraryImpl(location,
                                            LITLAUNCH_LIBRARY_API_VERSION,
                                            litlaunchLibraryApiTemplate);
    return result;
}

LibraryImpl *createLibraryImpl(ResourceLocation *id, const char* version, LibraryTemplate *_template)
{
    LibraryImpl* impl = malloc(sizeof(*impl));
    impl->implementationId = id;
    utstring_new(impl->implementationVersion);
    utstring_printf(impl->implementationVersion, "%s", version);
    impl->libraryTemplate = _template;

    return impl;
}

const char* getLibraryImplVersion(LibraryImpl* ptr)
{
    return utstring_body(ptr->implementationVersion);
}

ResourceLocation *getLibraryImplResourceLocation(LibraryImpl *ptr)
{
    return ptr->implementationId;
}

void freeLibraryImplVersion(LibraryImpl *ptr)
{
    utstring_free(ptr->implementationVersion);
}

ResourceLocation *newResourceLocation()
{
    return (ResourceLocation*) malloc(sizeof(ResourceLocation));
}

void setResourceLocation(ResourceLocation* ptr, const char* _namespace, const char* _path)
{
    utstring_new(ptr->_namespace);
    utstring_new(ptr->_path);
    utstring_printf(ptr->_namespace, "%s", _namespace);
    utstring_printf(ptr->_path, "%s", _path);
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

void freeResourceLocation(ResourceLocation *ptr)
{
#ifndef _LITLAUNCH_SLIM_
    utstring_free(ptr->_namespace);
    utstring_free(ptr->_path);
#endif
    free(ptr);
}