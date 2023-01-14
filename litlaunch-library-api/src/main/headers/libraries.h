#pragma once

#include "litlaunch-library-api.h"
#include "uthash/utstring.h"

struct LibraryTemplateStruct
{
    ResourceLocation *id;
    // Must be NULL initially
    DependencyRegistry *dependencyDict;
    // Must be NULL initially
    ComponentTemplateRegistry *componentTemplateDict;
};

struct LibraryImplStruct
{
    ResourceLocation *implementationId;
    UT_string *implementationVersion;
    LibraryTemplate *libraryTemplate;
    ComponentImplRegistry *componentDict;
};