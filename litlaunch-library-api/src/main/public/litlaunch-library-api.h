#pragma once

#include <string.h>
#include <stdlib.h>

typedef enum EnumDependencyRequirement {
    INCOMPATIBLE = -1,
    COMPATIBLE = 0,
    REQUIRED = 1
} DependencyRequirement;

typedef enum EnumVersionRequirement {
    TOO_OLD = -1,
    OK_VER = 0,
    TOO_NEW = 1
} VersionRequirement;

typedef struct ResourceLocationStruct ResourceLocation;
typedef VersionRequirement (*VersionValidFunc) (const char* input);

typedef struct ComponentTemplateDictStruct ComponentTemplateDict;
typedef struct DependencyDictStruct DependencyDict;

typedef struct DependencyStruct Dependency;

typedef struct ComponentTemplateStruct ComponentTemplate;
typedef struct LibraryTemplateStruct LibraryTemplate;

typedef struct ComponentImplStruct ComponentImpl;
typedef struct LibraryImplStruct LibraryImpl;

// extern ISoftware* initLibraryAPI(void);

#define NAME "LitLaunch Library API"
#define VERSION "0.1.0+build.2"