#include <string.h>

#ifndef main_h__
#define main_h__

struct ISoftware {
    unsigned int    structLength;
    unsigned int    nameLength;
    unsigned int    versionLength;
    char            blob[0];
};

extern ISoftware* createSoftwareStruct(ISoftware* s, char name[], char version[]);
 
#endif  // main_h__