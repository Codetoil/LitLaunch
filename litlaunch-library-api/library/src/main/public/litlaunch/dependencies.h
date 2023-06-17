#pragma once

#include "location.h"
#include "uthash/utstring.h"
#include "uthash/uthash.h"

typedef enum EnumDependencyRequirement
{
    COMPATIBLE_DEP = 0,
    REQUIRED_DEP = 1,
    EMBEDDED_DEP = 2
} DependencyRequirement;

typedef enum EnumVersionComparatorResult
{
    TOO_OLD = -1,
    JUST_RIGHT = 0,
    TOO_NEW = 1
} VersionComparatorResult;

typedef struct VersionStruct Version;

typedef VersionComparatorResult (*VersionComparator)(const struct Version*);

typedef struct VersionSchemaStruct
{
    ResourceLocation *id;
    VersionComparator* withinBounds;
    UT_hash_handle hh;
} VersionSchema;

typedef struct VersionStruct
{
    ResourceLocation *id;
#ifndef _LITLAUNCH_SLIM_
    UT_string* version;
#else
    char version;
#endif
} Version;

typedef struct DependencyDictStruct DependencyDict;

typedef struct ModuleStruct
{
    ResourceLocation *id;
    Version *version;
    DependencyDict *dependencyDict;
    UT_hash_handle hh;
} Module;

typedef struct DependencyDictStruct
{
    ResourceLocation *id;
    Module *dependency;
    Version *versionRequired;
    DependencyRequirement *dependencyRequirement;
    UT_hash_handle hh;
} DependencyDict;

extern Module *newModule(ResourceLocation* id, Version* version, DependencyDict* dependencyDict);
extern void freeModule(Module* ptr);

#ifndef _LITLAUNCH_SLIM
extern Version *newVersion(ResourceLocation* id, const char* version);
extern const char* getVersionString(Version *ptr);
extern size_t getVersionLength(Version *ptr);
#else
extern Version *newVersion(ResourceLocation* id, char version);
#endif
extern void freeVersion(Version* ptr);

extern VersionSchema *newVersionSchema(ResourceLocation* id, VersionComparator* withinBounds);
extern void freeVersionSchema(VersionSchema* ptr);