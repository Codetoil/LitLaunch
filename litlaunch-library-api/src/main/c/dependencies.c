//
// Created by codetoil on 5/19/25.
//


#include "litlaunch/dependencies.h"

#include <stdlib.h>

// New entries are added to the top of the list
Module *moduleRegistryTop = NULL;
Module *moduleRegistryBottom = NULL;

Version *newVersion(ResourceLocation* id, VersionValue versionValue, VersionValueLength versionValueLength)
{
    Version* versionStruct = malloc(sizeof(*versionStruct) + versionValueLength);
    versionStruct->id = id;
    versionStruct->versionValue = versionValue;
    versionStruct->versionValueLength = versionValueLength;
    return versionStruct;
}

void freeVersion(Version* ptr)
{
    free(ptr);
}

Module *newModule(ResourceLocation* id, Version* version, DependencyDict* dependencyDict)
{
    Module* module = malloc(sizeof(*module));
    module->id = id;
    module->version = version;
    module->dependencyDict = dependencyDict;
    module->next = NULL;
    module->prev = moduleRegistryTop;
    if (!moduleRegistryBottom)
    {
        moduleRegistryBottom = module;
    }
    if (moduleRegistryTop)
    {
        moduleRegistryTop->next = module;
    }
    moduleRegistryTop = module;
    return module;
}

void freeModule(Module* ptr)
{
    Module* next = ptr->next;
    Module* prev = ptr->prev;
    if (next)
    {
        next->prev=prev;
    }
    if (prev)
    {
        prev->next=next;
    }
    if (ptr == moduleRegistryBottom)
    {
        moduleRegistryBottom = next;
    }
    if (ptr == moduleRegistryTop)
    {
        moduleRegistryTop = prev;
    }
    free(ptr);
}

DependencyDict *newDependencyDict(ResourceLocation* id)
{
    DependencyDict* dependencyDict = malloc(sizeof(*dependencyDict));
    dependencyDict->id = id;
    dependencyDict->dependencyDictBottom = NULL;
    dependencyDict->dependencyDictTop = NULL;
    return dependencyDict;
}

DependencyDictElement *addToDependencyDict(DependencyDict* dependencyDict,
    ResourceLocation* id, Module* module, VersionComparator* versionComparator, u_int8_t flags)
{
    DependencyDictElement* dependencyDictElement = malloc(sizeof(*dependencyDictElement));
    dependencyDictElement->id = id;
    dependencyDictElement->dependency = module;
    dependencyDictElement->versionComparator = versionComparator;
    dependencyDictElement->flags = flags;
    dependencyDictElement->next = NULL;
    dependencyDictElement->prev = dependencyDict->dependencyDictTop;
    if (!dependencyDict->dependencyDictBottom)
    {
        dependencyDict->dependencyDictBottom = dependencyDictElement;
    }
    if (dependencyDict->dependencyDictTop)
    {
        dependencyDict->dependencyDictTop->next = dependencyDictElement;
    }
    dependencyDict->dependencyDictTop = dependencyDictElement;
    return dependencyDictElement;
}

void removeFromDependencyDictAndFree(DependencyDict* dependencyDict, DependencyDictElement* ptr)
{
    DependencyDictElement* next = ptr->next;
    DependencyDictElement* prev = ptr->prev;
    if (next)
    {
        next->prev=prev;
    }
    if (prev)
    {
        prev->next=next;
    }
    if (ptr == dependencyDict->dependencyDictBottom)
    {
        dependencyDict->dependencyDictBottom = next;
    }
    if (ptr == dependencyDict->dependencyDictTop)
    {
        dependencyDict->dependencyDictTop = prev;
    }
    free(ptr);
}

void freeDependencyDict(DependencyDict* ptr)
{
    free(ptr);
}