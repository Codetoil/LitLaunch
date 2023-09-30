#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "litlaunch/location.h"
#include "litlaunch/dependencies.h"
#include "litlaunch/litlaunch-library-api.h"

int main()
{
    printf("COMPATIBLE_DEP: %i\n", COMPATIBLE_DEP);
    printf("REQUIRED_DEP: %i\n", REQUIRED_DEP);
    printf("EMBEDDED_DEP: %i\n", EMBEDDED_DEP);

    Module* apiModule = initLibraryApi();

    const char* libApiModuleLocStr = getResourceLocationTotal(apiModule->id);
    const char* libApiModuleVersionLocStr = getResourceLocationTotal(apiModule->version->id);
    const char* libApiModuleVersionValue = getVersionValue(apiModule->version);

    printf("LitLaunch Library API Implementation:\n");
    printf("\tResource Location: %s\n", libApiModuleLocStr);
    printf("\tVersion:\n");
    printf("\t\tResource Location: %s\n", libApiModuleVersionLocStr);
    printf("\t\tValue: %s\n", libApiModuleVersionValue);
    printf("\tDependencies:\n");
    printf("\n");
    
    freeResourceLocation(apiModule->version->id);
    freeVersion(apiModule->version);
    freeResourceLocation(apiModule->id);
    freeModule(apiModule);
    return 0;
}
