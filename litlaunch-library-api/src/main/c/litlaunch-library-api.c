typedef struct SoftwareStruct ISoftware;

#include "litlaunch-library-api.h"

ISoftware* initLibraryAPI(void)
{
    ISoftware *s;
 
    s = createSoftwareStruct(NAME, VERSION);
 
    return s;
}