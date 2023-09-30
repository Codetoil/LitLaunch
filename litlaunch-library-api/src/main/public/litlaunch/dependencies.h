#pragma once

#include "location.h"

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

typedef VersionComparatorResult (*VersionComparator)(const Version*);

typedef struct VersionSchemaStruct VersionSchema;

typedef struct VersionSchemaStruct
{
    ResourceLocation *id;
    VersionComparator* withinBounds;
    VersionSchema* next;
} VersionSchema;


typedef const char* VersionValue;
typedef unsigned int VersionValueLength;

typedef struct VersionStruct
{
    ResourceLocation *id;
    VersionValue versionValue;
    VersionValueLength versionValueLength;
} Version;

typedef struct DependencyDictStruct DependencyDict;

typedef struct ModuleStruct Module;

typedef struct ModuleStruct
{
    ResourceLocation *id;
    Version *version;
    DependencyDict *dependencyDict;
    Module* next;
    Module* prev;
} Module;

typedef struct DependencyDictStruct DependencyDict;

typedef struct DependencyDictStruct
{
    ResourceLocation *id;
    Module *dependency;
    Version *versionRequired;
    DependencyRequirement *dependencyRequirement;
    DependencyDict* next;
    DependencyDict* prev;
} DependencyDict;

extern Module *newModule(ResourceLocation* id, Version* version, DependencyDict* dependencyDict);
extern void freeModule(Module* ptr);

extern Version *newVersion(ResourceLocation* id, VersionValue versionValue, VersionValueLength versionValueLength);
extern VersionValue getVersionValue(Version *ptr);
extern VersionValueLength getVersionValueLength(Version *ptr);
extern void freeVersion(Version* ptr);

extern VersionSchema *newVersionSchema(ResourceLocation* id, VersionComparator* withinBounds); // Unimplemented
extern void freeVersionSchema(VersionSchema* ptr); // Unimplemented