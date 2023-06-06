#pragma once

#include "uthash/utstring.h"
#include "litlaunch-library-api.h"
#include "location.h"
#include "registries.h"

struct ModuleTemplateStruct
{
    ResourceLocation *id;
    // Must be NULL initially
    DependencyRegistry *dependencyDict;
    // Must be NULL initially
    ModuleImpl *parentModule;
    // Must be NULL initially
    ModuleTemplateRegistry *moduleTemplateDict;
};

struct ModuleImplStruct
{
    ResourceLocation *implementationId;
    UT_string *implementationVersion;
    ModuleTemplate *implementationTemplate;
    ModuleImplRegistry *submoduleDict;
};