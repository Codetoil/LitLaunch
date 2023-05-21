#pragma once

#include "location.h"
#include "uthash/uthash.h"

typedef enum EnumDependencyRequirement
{
    COMPATIBLE = 0,
    REQUIRED = 1,
    EMBEDDED = 2
} DependencyRequirement;

typedef struct VersionComparisonFunctionRegistryStruct VersionComparisonFunctionRegistry;

typedef struct VersionStruct
{
    ResourceLocation *id;
#ifndef _LITLAUNCH_SLIM_
    const char* version;
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
