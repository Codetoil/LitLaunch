#include "litlaunch-library-api.h"
#include "uthash/utstring.h"

int main()
{
    ISoftware* s = initLibraryAPI();
    printf("%s\n", utstring_body((UT_string*) (s->name)));
    printf("%s\n", utstring_body((UT_string*) (s->version)));
    printf("%x\n", s->size);
    freeSoftwareStruct(s);
    return 0;
}