typedef struct SoftwareStruct ISoftware;

#include "litlaunch-library-api.h"

ISoftware* init_library_api(void)
{
    ISoftware *s;
 
    s = createSoftwareStruct("LitLaunch Library API", "0.1.0+build.1");
 
    return s;
}