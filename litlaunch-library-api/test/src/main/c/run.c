#include "litlaunch/location.h"
#include "litlaunch/dependencies.h"
#include "litlaunch/litlaunch-library-api.h"

int main()
{
    printf("COMPATIBLE_DEP: %i\n", COMPATIBLE_DEP);
    printf("REQUIRED_DEP: %i\n", REQUIRED_DEP);
    printf("EMBEDDED_DEP: %i\n", EMBEDDED_DEP);

    Module* apiModule = initLibraryApi();
    
    const char* libApiImplLocStr = resourceLocationToString(apiModule->id);

    printf("LitLaunch Library API Implementation:\n");
    printf("\tResource Location: %s\n", libApiImplLocStr);
    
    free(libApiImplLocStr);
    freeResourceLocation(apiModule->id);
    freeModule(apiModule);
    return 0;
}