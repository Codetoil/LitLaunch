#include "litlaunch/litlaunch-library-api.h"
#include "litlaunch/dependencies.h"
#include "litlaunch/feature.h"
#include "litlaunch/library.h"
#include "litlaunch/location.h"

int main()
{
    printf("INCOMPATIBLE: %i\n", INCOMPATIBLE);
    printf("COMPATIBLE: %i\n", COMPATIBLE);
    printf("REQUIRED: %i\n", REQUIRED);

    printf("OLDER: %i\n", OLDER);
    printf("SAME: %i\n", SAME);
    printf("NEWER: %i\n", NEWER);

    LibraryImpl* libApiImpl = initLibraryApi();
    ResourceLocation* libApiImplLoc = getLibraryImplResourceLocation(libApiImpl);

    const char* libApiImplLocStr = resourceLocationToString(libApiImplLoc);
    const char* libApiImplVersion = getLibraryImplVersion(libApiImpl);

    printf("LitLaunch Library API Implementation:\n");
    printf("\tResourceLocation: %s\n", libApiImplLocStr);
    printf("\tVersion: %s\n", libApiImplVersion);
    
    free(libApiImplLocStr);
    freeLibraryImplVersion(libApiImpl);
    freeResourceLocation(libApiImplLoc);
    free(libApiImpl);
    return 0;
}