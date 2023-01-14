#pragma once

#include "litlaunch-library-api.h"
#include "uthash/utstring.h"

struct VersionStruct
{
    ResourceLocation *id;
    ResourceLocation *versionValidFunc;
    UT_string *version;
};

struct DependencyStruct
{
    ResourceLocation *id;
    DependencyRequirement *dependencyRequirement;
};

