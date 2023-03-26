#pragma once

#include "location.h"
#include "dependencies.h"

typedef struct LibraryTemplateStruct
{
    ResourceLocation *id;
    // Must be NULL initially
    DependencyRegistry *dependencyDict;
} LibraryTemplate;

typedef struct LibraryImplStruct
{
    ResourceLocation *implementationId;
    UT_string* implementationVersion;
    LibraryTemplate *libraryTemplate;
    FeatureRegistry *featureRegistry;
} LibraryImpl;

extern LibraryImpl *createLibraryImpl(ResourceLocation *id, const char* version, LibraryTemplate *_template);