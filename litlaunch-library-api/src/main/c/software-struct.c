typedef struct SoftwareStruct ISoftware;

#include "litlaunch-library-api.h"

ISoftware* createSoftwareStruct(const char name[], const char version[]) {
    ISoftware* s = malloc(sizeof(*s));
    utstring_new(s->name);
    utstring_new(s->version);
    utstring_printf(s->name, name);
    utstring_printf(s->version, version);

    s->size = sizeof(*s);
    return s;
}

void freeSoftwareStruct(ISoftware* software) {
    utstring_free(software->name);
    utstring_free(software->version);
    free(software);
}