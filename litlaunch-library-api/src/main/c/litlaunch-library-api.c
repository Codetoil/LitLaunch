#include "litlaunch-library-api.h"
#include "libraries.h"
#include "dependencies.h"

LibraryImpl *initLibraryApi(void)
{
    LibraryTemplate *litlaunchLibraryApiTemplate = createLibraryTemplate();
    ResourceLocation *location = createResourceLocation("litlaunch", LITLAUNCH_LIBRARY_API_NAME);

    LibraryImpl *result = createLibraryImpl(location,
                                            LITLAUNCH_LIBRARY_API_VERSION,
                                            litlaunchLibraryApiTemplate);
    return result;
}