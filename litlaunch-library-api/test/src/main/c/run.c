#include "litlaunch-library-api.h"
#include "uthash/utstring.h"

int main()
{
    printf("INCOMPATIBLE: %i\n", INCOMPATIBLE);
    printf("COMPATIBLE: %i\n", COMPATIBLE);
    printf("REQUIRED: %i\n", REQUIRED);

    printf("TOO_OLD: %i\n", TOO_OLD);
    printf("OK_VER: %i\n", OK_VER);
    printf("TOO_NEW: %i\n", TOO_NEW);

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