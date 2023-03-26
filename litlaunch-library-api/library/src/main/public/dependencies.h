#pragma once

#include "location.h"
#include "uthash/uthash.h"

typedef enum EnumDependencyRequirement
{
    INCOMPATIBLE = -1,
    COMPATIBLE = 0,
    REQUIRED = 1
} DependencyRequirement;

typedef enum EnumVersionComparisonResult
{
    OLDER = -1,
    SAME = 0,
    NEWER = 1
} VersionComparisonResult;

typedef struct VersionComparisonFunctionRegistryStruct VersionComparisonFunctionRegistry;

typedef struct VersionStruct
{
    ResourceLocation *id;
    VersionComparisonFunctionRegistry *versionValidFunc;
#ifndef _LITLAUNCH_SLIM_
    const char* version;
#else
    const char version;
#endif
} Version;

typedef struct DependencyStruct
{
    ResourceLocation *id;
    DependencyRequirement *dependencyRequirement;
} Dependency;

typedef struct DependencyRegistryStruct
{
    ResourceLocation *id;
    Dependency *dependency;
    UT_hash_handle hh;
} DependencyRegistry;

typedef struct VersionComparisonFunctionRegistryStruct
{
    ResourceLocation *id;
    VersionComparisonResult (*_func)(Version* requiredVersion, Version* inputVersion);
    UT_hash_handle hh;
} VersionComparisonFunctionRegistry;