#pragma once

#include "litlaunch-library-api.h"
#include "uthash/utstring.h"
#include "uthash/uthash.h"
#include "uthash/utarray.h"

typedef struct ResourceLocationStruct {
    UT_string*              namespace;
    UT_string*              path;
} ResourceLocation;

typedef struct ComponentTemplateStruct ComponentTemplate;
typedef struct DependencyStruct Dependency;

typedef struct ComponentTemplateDictStruct {
    ResourceLocation*           id;
    ComponentTemplate*          componentTemplate;
    UT_hash_handle              hh;
} ComponentTemplateDict;

typedef struct DependencyDictStruct {
    ResourceLocation*           id;
    Dependency*                 dependency;
    UT_hash_handle              hh;
} DependencyDict;

typedef struct DependencyStruct {
    ResourceLocation*           id;
    VersionValidFunc            versionValidFunc;
    DependencyRequirement*      DependencyRequirement;
} Dependency;

typedef struct ComponentTemplateStruct {
    ResourceLocation*           id;
    LibraryTemplate*            parentLibrary;
} ComponentTemplate;

typedef struct LibraryTemplateStruct {
    ResourceLocation*           id;
    // Must be NULL initially
    DependencyDict*             dependencyDict;
    // Must be NULL initially
    ComponentTemplateDict*      componentTemplateDict;
} LibraryTemplate;

typedef struct ComponentImplStruct {
    ResourceLocation*           id;
    ComponentTemplate*          template;
} ComponentImpl;

typedef struct LibraryImplStruct {
    ResourceLocation*           implementationId;
    UT_string*                  implementationVersion;
    LibraryTemplate*            template;
} LibraryImpl;