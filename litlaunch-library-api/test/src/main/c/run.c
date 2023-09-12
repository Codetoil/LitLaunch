#include "litlaunch/location.h"
#include "litlaunch/dependencies.h"
#include "litlaunch/litlaunch-library-api.h"

int main()
{
    printf("COMPATIBLE_DEP: %i\n", COMPATIBLE_DEP);
    printf("REQUIRED_DEP: %i\n", REQUIRED_DEP);
    printf("EMBEDDED_DEP: %i\n", EMBEDDED_DEP);

    Module* apiModule = initLibraryApi();

#ifndef _LITLAUNCH_SLIM_
    const char* libApiModuleLocStr = resourceLocationToString(apiModule->id);
    const char* libApiModuleVersionLocStr = resourceLocationToString(apiModule->version->id);
    const char* libApiModuleVersionValue = getVersionString(apiModule->version);
#else
    char libApiModuleLocNamespace = getResourceLocationNamespace(apiModule->id);
    char libApiModuleLocPath = getResourceLocationPath(apiModule->id);
    char libApiModuleVersionLocNamespace = getResourceLocationNamespace(apiModule->version->id);
    char libApiModuleVersionLocPath = getResourceLocationPath(apiModule->version->id);
    char libApiModuleVersionValue = apiModule->version->version;
#endif

    printf("LitLaunch Library API Implementation:\n");
#ifndef _LITLAUNCH_SLIM_
    printf("\tResource Location: %s\n", libApiModuleLocStr);
#else
    printf("\tResource Location: %x%x\n", libApiModuleLocNamespace, libApiModuleLocPath);
#endif
    printf("\tVersion:\n");
#ifndef _LITLAUNCH_SLIM_
    printf("\t\tResource Location: %s\n", libApiModuleVersionLocStr);
    printf("\t\tValue: %s\n", libApiModuleVersionValue);
#else
    printf("\t\tResource Location: %x%x\n", libApiModuleVersionLocNamespace, libApiModuleVersionLocPath);
    printf("\t\tValue: %x\n", libApiModuleVersionValue);
#endif
    printf("\tDependencies:\n");
    printf("\n");
    
    freeVersion(apiModule->version);
#ifndef _LITLAUNCH_SLIM_
    free(libApiModuleVersionLocStr);
    free(libApiModuleLocStr);
#endif
    freeResourceLocation(apiModule->id);
    freeModule(apiModule);
    return 0;
}
