#pragma once

#include "location.h"
#include "library.h"

typedef struct FeatureStruct
{
    ResourceLocation *id;
    LibraryTemplate *parentLibrary;
} Feature;

typedef struct FeatureRegistryStruct
{
    ResourceLocation *id;
    Feature *feature;
    UT_hash_handle hh;
} FeatureRegistry;
