#pragma once

#include "litlaunch-library-api.h"

struct ComponentTemplateStruct
{
    ResourceLocation *id;
    LibraryTemplate *parentLibrary;
};

struct ComponentImplStruct
{
    ResourceLocation *id;
    ComponentTemplate *componentTemplate;
};