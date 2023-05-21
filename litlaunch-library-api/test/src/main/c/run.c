#include "litlaunch/location.h"
#include "litlaunch/dependencies.h"
#include "litlaunch/litlaunch-library-api.h"

int main()
{
    printf("COMPATIBLE: %i\n", COMPATIBLE);
    printf("REQUIRED: %i\n", REQUIRED);
    printf("EMBEDDED: %i\n", EMBEDDED);

    Module* apiModule = initLibraryApi();
    
    const char* libApiImplLocStr = resourceLocationToString(apiModule->id);

    printf("LitLaunch Library API Implementation:\n");
    printf("\tResource Location: %s\n", libApiImplLocStr);
    
    free(libApiImplLocStr);
    freeResourceLocation(apiModule->id);
    freeModule(apiModule);
    return 0;
}