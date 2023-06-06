#pragma once

#include "uthash/utstring.h"
#include "litlaunch-library-api.h"

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

