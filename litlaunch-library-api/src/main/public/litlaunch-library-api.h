#pragma once

#include <string.h>
#include <stdlib.h>

typedef enum EnumDependencyRequirement
{
    INCOMPATIBLE = -1,
    COMPATIBLE = 0,
    REQUIRED = 1
} DependencyRequirement;

typedef enum EnumVersionRequirement
{
    TOO_OLD = -1,
    OK_VER = 0,
    TOO_NEW = 1
} VersionRequirement;

typedef struct VersionValidFuncRegistryStruct VersionValidFuncRegistry;
typedef struct VersionStruct Version;

typedef struct ResourceLocationStruct ResourceLocation;

typedef struct ComponentImplRegistryStruct ComponentImplRegistry;
typedef struct ComponentTemplateRegistryStruct ComponentTemplateRegistry;
typedef struct DependencyRegistryStruct DependencyRegistry;

typedef struct DependencyStruct Dependency;

typedef struct ComponentTemplateStruct ComponentTemplate;
typedef struct LibraryTemplateStruct LibraryTemplate;

typedef struct ComponentImplStruct ComponentImpl;
typedef struct LibraryImplStruct LibraryImpl;

#define LITLAUNCH_LIBRARY_API_NAME "LitLaunch Library API"
#define LITLAUNCH_LIBRARY_API_VERSION "0.1.0+build.3"

extern LibraryImpl *initLibraryApi(void);

extern LibraryImpl *createLibraryImpl(ResourceLocation *id, const char version[], LibraryTemplate *template);
extern void freeLibraryImpl(LibraryImpl *ptr);

extern ResourceLocation *createResourceLocation(const char _namespace[], const char _path[]);
extern void freeResourceLocation(ResourceLocation *ptr);
