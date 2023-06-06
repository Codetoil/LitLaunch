#pragma once

#include "uthash/uthash.h"
#include "uthash/utstring.h"
#include "litlaunch-library-api.h"

struct ResourceLocationStruct
{
    UT_string *_namespace;
    UT_string *_path;
};