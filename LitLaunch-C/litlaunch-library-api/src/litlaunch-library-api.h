#include <string.h>

#ifndef main_h__
#define main_h__

typedef struct SoftwareStruct {
    unsigned int    structLength;
    unsigned int    nameLength;
    unsigned int    versionLength;
    char            blob[0];
} ISoftware;

extern ISoftware* createSoftwareStruct(char name[], char version[]);
 
#endif  // main_h__