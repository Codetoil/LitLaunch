#include "litlaunch-library-api.h"
#include <stdlib.h>
#include "location.h"
#include "modules.h"
#include "dependencies.h"

ModuleImpl *initLibraryApi(void)
{
    ModuleTemplate *litlaunchLibraryApiModuleTemplate = NULL; //createLibraryTemplate();
    ResourceLocation *location = createResourceLocation("litlaunch", LITLAUNCH_LIBRARY_API_NAME);

    ModuleImpl *result = createModuleImpl(location,
                                            LITLAUNCH_LIBRARY_API_VERSION,
                                            litlaunchLibraryApiModuleTemplate);
    return result;
}

ModuleImpl *createModuleImpl(ResourceLocation *id, const char version[], ModuleTemplate *_template)
{
    ModuleImpl* impl = malloc(sizeof(*impl));
    impl->implementationId = id;
    utstring_new(impl->implementationVersion);
    utstring_printf(impl->implementationVersion, version);
    impl->implementationTemplate = _template;

    return impl;
}

const char* getModuleImplVersion(ModuleImpl* ptr)
{
    return utstring_body(ptr->implementationVersion);
}

ResourceLocation *getModuleImplResourceLocation(ModuleImpl *ptr)
{
    return ptr->implementationId;
}

void freeModuleImplVersion(ModuleImpl *ptr)
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