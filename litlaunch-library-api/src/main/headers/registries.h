#pragma once

#include "litlaunch-library-api.h"
#include "uthash/uthash.h"
#include "uthash/utstring.h"

struct ResourceLocationStruct
{
    UT_string *_namespace;
    UT_string *_path;
};

struct VersionValidFuncRegistryStruct
{
    ResourceLocation *id;
    VersionRequirement (*_func)(const char *input);
    UT_hash_handle hh;
};

struct ComponentTemplateRegistryStruct
{
    ResourceLocation *id;
    ComponentTemplate *componentTemplate;
    UT_hash_handle hh;
};

struct ComponentImplRegistryStruct
{
    ResourceLocation *id;
    ComponentImpl *component;
    UT_hash_handle hh;
};

struct DependencyRegistryStruct
{
    ResourceLocation *id;
    Dependency *dependency;
    UT_hash_handle hh;
};