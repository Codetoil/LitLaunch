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

    ModuleImpl* libApiImpl = initLibraryApi();
    ResourceLocation* libApiImplLoc = getModuleImplResourceLocation(libApiImpl);
    const char* libApiImplVersion = getModuleImplVersion(libApiImpl);
    const char* libApiImplNamespace = getResourceLocationNamespace(libApiImpl);
    const char* libApiImplPath = getResourceLocationPath(libApiImpl);

    printf("LitLaunch Library API Module Implementation: \n");
    printf("\t", libApiImplNamespace, ":", libApiImplPath, "\n");
    printf("\t", libApiImplVersion, "\n");

    freeModuleImplVersion(libApiImpl);
    freeResourceLocationNamespace(libApiImplLoc);
    freeResourceLocationPath(libApiImplLoc);
    free(libApiImplLoc);
    free(libApiImpl);
    
    return 0;
}