#pragma once

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

typedef struct ModuleImplRegistryStruct ModuleImplRegistry;
typedef struct ModuleTemplateRegistryStruct ModuleTemplateRegistry;
typedef struct DependencyRegistryStruct DependencyRegistry;

typedef struct DependencyStruct Dependency;

typedef struct ModuleTemplateStruct ModuleTemplate;

typedef struct ModuleImplStruct ModuleImpl;

#define LITLAUNCH_LIBRARY_API_NAME "LitLaunch Library API"
#define LITLAUNCH_LIBRARY_API_VERSION "0.1.0+build.3"

extern ModuleImpl *initLibraryApi(void);

extern ModuleImpl *createModuleImpl(ResourceLocation *id, const char version[], ModuleTemplate *_template);
extern const char* getModuleImplVersion(ModuleImpl* ptr);
extern ResourceLocation *getModuleImplResourceLocation(ModuleImpl *ptr);
extern void freeModuleImplVersion(ModuleImpl *ptr);

extern ResourceLocation *createResourceLocation(const char _namespace[], const char _path[]);
extern const char* getResourceLocationNamespace(ResourceLocation *ptr);
extern const char* getResourceLocationPath(ResourceLocation *ptr);
extern void freeResourceLocationNamespace(ResourceLocation *ptr);
extern void freeResourceLocationPath(ResourceLocation *ptr);
