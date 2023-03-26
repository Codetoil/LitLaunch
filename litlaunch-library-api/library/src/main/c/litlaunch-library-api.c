#include <stdlib.h>
#include "litlaunch-library-api.h"
#include "library.h"
#include "dependencies.h"

LibraryImpl *initLibraryApi(void)
{
    LibraryTemplate *litlaunchLibraryApiTemplate = NULL; //createLibraryTemplate();
    ResourceLocation *location = createResourceLocation("litlaunch", "litlaunch_library_api");

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

ResourceLocation *createResourceLocation(ResourceLocationNamespace _namespace, ResourceLocationPath _path)
{
    ResourceLocation* loc = malloc(sizeof(*loc));
#ifndef _LITLAUNCH_SLIM_
    utstring_new(loc->_namespace);
    utstring_new(loc->_path);
    utstring_printf(loc->_namespace, _namespace);
    utstring_printf(loc->_path, _path);
#endif
    return loc;
}

const char* getResourceLocationNamespace(ResourceLocation *ptr)
{
#ifndef _LITLAUNCH_SLIM_
    return utstring_body(ptr->_namespace);
#endif
}

const char* getResourceLocationPath(ResourceLocation *ptr)
{
#ifndef _LITLAUNCH_SLIM_
    return utstring_body(ptr->_path);
#endif
}

const char* resourceLocationToString(ResourceLocation *ptr)
{
#ifndef _LITLAUNCH_SLIM_
    UT_string* combination;
    utstring_new(combination);
    utstring_printf(combination, "%s:%s", getResourceLocationNamespace(ptr), getResourceLocationPath(ptr));
    const char* body = utstring_body(combination);
    const char* result = malloc(sizeof(*body));
    strcpy(result, body);
    utstring_free(combination); // Make sure to free the temp string.
    return result;
#endif
}

void freeResourceLocation(ResourceLocation *ptr)
{
#ifndef _LITLAUNCH_SLIM_
    utstring_free(ptr->_namespace);
    utstring_free(ptr->_path);
#endif
    free(ptr);
}