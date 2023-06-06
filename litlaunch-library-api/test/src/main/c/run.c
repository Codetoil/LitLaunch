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

    ModuleImpl* libApiModuleImpl = initLibraryApi();
    printf("1\n");
    ResourceLocation* libApiModuleImplLoc = getModuleImplResourceLocation(libApiModuleImpl);
    printf("2\n");
    const char* libApiModuleImplVersion = getModuleImplVersion(libApiModuleImpl);
    printf("3\n");
    const char* libApiModuleImplNamespace = getResourceLocationNamespace(libApiModuleImpl);
    printf("4\n");
    const char* libApiModuleImplPath = getResourceLocationPath(libApiModuleImpl);

    printf("LitLaunch Library API Module Implementation: \n");
    printf("\t", libApiModuleImplNamespace, ":", libApiModuleImplPath, "\n");
    printf("\t", libApiModuleImplVersion, "\n");

    freeModuleImplVersion(libApiModuleImpl);
    freeResourceLocationNamespace(libApiModuleImplLoc);
    freeResourceLocationPath(libApiModuleImplLoc);
    free(libApiModuleImplLoc);
    free(libApiModuleImpl);
    
    return 0;
}