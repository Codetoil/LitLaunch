#pragma once

#include "uthash/uthash.h"
#include "litlaunch-library-api.h"
#include "location.h"

struct VersionValidFuncRegistryStruct
{
    ResourceLocation *id;
    VersionRequirement (*_func)(const char *input);
    UT_hash_handle hh;
};

struct ModuleTemplateRegistryStruct
{
    ResourceLocation *id;
    ModuleTemplate *moduleTemplate;
    UT_hash_handle hh;
};

struct ModuleImplRegistryStruct
{
    ResourceLocation *id;
    ModuleImpl *module;
    UT_hash_handle hh;
};

struct DependencyRegistryStruct
{
    ResourceLocation *id;
    Dependency *dependency;
    UT_hash_handle hh;
};