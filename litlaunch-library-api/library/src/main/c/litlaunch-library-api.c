#include "litlaunch-library-api.h"
#include <stdlib.h>
#include "libraries.h"
#include "dependencies.h"

LibraryImpl *initLibraryApi(void)
{
    LibraryTemplate *litlaunchLibraryApiTemplate = NULL; //createLibraryTemplate();
    ResourceLocation *location = createResourceLocation("litlaunch", LITLAUNCH_LIBRARY_API_NAME);

    LibraryImpl *result = createLibraryImpl(location,
                                            LITLAUNCH_LIBRARY_API_VERSION,
                                            litlaunchLibraryApiTemplate);
    return result;
}

LibraryImpl *createLibraryImpl(ResourceLocation *id, const char version[], LibraryTemplate *_template)
{
    LibraryImpl* impl = malloc(sizeof(*impl));
    impl->implementationId = id;
    utstring_new(impl->implementationVersion);
    utstring_printf(impl->implementationVersion, version);
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

ResourceLocation *createResourceLocation(const char _namespace[], const char _path[])
{
    ResourceLocation* loc = malloc(sizeof(*loc));
    utstring_new(loc->_namespace);
    utstring_new(loc->_path);
    utstring_printf(loc->_namespace, _namespace);
    utstring_printf(loc->_path, _path);

    return loc;
}

const char* getResourceLocationNamespace(ResourceLocation *ptr)
{
    return utstring_body(ptr->_namespace);
}

const char* getResourceLocationPath(ResourceLocation *ptr)
{
    return utstring_body(ptr->_path);
}


void freeResourceLocationNamespace(ResourceLocation *ptr)
{
    utstring_free(ptr->_namespace);
}

void freeResourceLocationPath(ResourceLocation *ptr)
{
    utstring_free(ptr->_path);
}