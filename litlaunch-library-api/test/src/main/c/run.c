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
    return 0;
}