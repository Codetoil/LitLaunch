#pragma once

#include "location.h"
#include "dependencies.h"

typedef struct LibraryTemplateStruct
{
    ResourceLocation *id;
    // Must be NULL initially
    DependencyRegistry *dependencyDict;
} LibraryTemplate;

typedef struct FeatureRegistryStruct FeatureRegistry;

typedef struct LibraryImplStruct
{
    ResourceLocation *implementationId;
    UT_string* implementationVersion;
    LibraryTemplate *libraryTemplate;
    FeatureRegistry *featureRegistry;
} LibraryImpl;

extern LibraryImpl *createLibraryImpl(ResourceLocation *id, const char* version, LibraryTemplate *_template);
extern const char* getLibraryImplVersion(LibraryImpl* ptr);
extern ResourceLocation *getLibraryImplResourceLocation(LibraryImpl *ptr);
extern void freeLibraryImplVersion(LibraryImpl *ptr);