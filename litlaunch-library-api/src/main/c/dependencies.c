//
// Created by codetoil on 5/19/25.
//


#include "litlaunch/dependencies.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// New entries are added to the top of the list
Module *moduleRegistryTop = NULL;
Module *moduleRegistryBottom = NULL;

Module *newModule(const ResourceLocation* id, const Version* version, const DependencyDict* dependencyDict)
{
    const Module module = {id, version, dependencyDict, NULL, moduleRegistryTop};
    Module* ptr = malloc(sizeof(*ptr));
    memcpy(ptr, &module, sizeof(Module));
    if (!moduleRegistryBottom)
    {
        moduleRegistryBottom = ptr;
    }
    if (moduleRegistryTop)
    {
        moduleRegistryTop->next = ptr;
    }
    moduleRegistryTop = ptr;
    return ptr;
}

const char* moduleToString(const Module* ptr)
{
    char* result = malloc(1000 * sizeof(char));
    snprintf(result, 1000,
        "\tResource Location: %s\n"
        "\tVersion: %s\n"
        "\tDependency Dict: %s\n",
        resourceLocationToString(ptr->id), versionToString(ptr->version),
        dependencyDictToString(ptr->dependencyDict));
    return result;
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

Version *newVersion(const ResourceLocation* id, const VersionValue versionValue)
{
    const size_t versionValueLength = strlen(versionValue);
    const Version version = {id, versionValue, versionValueLength};
    Version* ptr = malloc(sizeof(*ptr) + versionValueLength);
    memcpy(ptr, &version, sizeof(Version));
    return ptr;
}

const char* versionToString(const Version* ptr)
{
    char* result = malloc(1000 * sizeof(char));
    snprintf(result, 1000,
        "\tResource Location: %s\n"
        "\tVersionValue: %s\n"
        "\tVersion Value Length: %lu\n",
        resourceLocationToString(ptr->id), ptr->versionValue, ptr->versionValueLength);
    return result;
}

void freeVersion(Version* ptr)
{
    free(ptr);
}

VersionComparator *newVersionComparator(const ResourceLocation* id,
    const VersionComparatorResult (*apply)(const Version*))
{
    const VersionComparator versionComparator = {id, apply};
    VersionComparator* ptr = malloc(sizeof(*ptr));
    memcpy(ptr, &versionComparator, sizeof(VersionComparator));
    return ptr;
}

const char* versionComparatorToString(const VersionComparator* ptr)
{
    char* result = malloc(1000 * sizeof(char));
    snprintf(result, 1000,
        "\tResource Location: %s\n",
        resourceLocationToString(ptr->id));
    return result;
}

void freeVersionComparator(VersionComparator* ptr)
{
    free(ptr);
}

DependencyDict *newDependencyDict(const ResourceLocation* id)
{
    const DependencyDict dependencyDict = {id, NULL, NULL};
    DependencyDict* ptr = malloc(sizeof(*ptr));
    memcpy(ptr, &dependencyDict, sizeof(DependencyDict));
    return ptr;
}

DependencyDictElement *addToDependencyDict(DependencyDict* dependencyDict, const ResourceLocation* id,
    const Module* module, const VersionComparator* versionComparator, const u_int8_t flags)
{
    const DependencyDictElement dependencyDictElement =
        {id, module, versionComparator, flags, NULL, dependencyDict->dependencyDictTop};
    DependencyDictElement* ptr = malloc(sizeof(*ptr));
    memcpy(ptr, &dependencyDictElement, sizeof(DependencyDictElement));
    if (!dependencyDict->dependencyDictBottom)
    {
        dependencyDict->dependencyDictBottom = ptr;
    }
    if (dependencyDict->dependencyDictTop)
    {
        dependencyDict->dependencyDictTop->next = ptr;
    }
    dependencyDict->dependencyDictTop = ptr;
    return ptr;
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

const char* dependencyDictToString(const DependencyDict* ptr)
{
    char* result = malloc(1000);
    snprintf(result, 1000,
        "\tResource Location: %s\n"
        "\tDependency Dict Bottom: %s\n"
        "\tDependency Dict Top: %s\n",
        resourceLocationToString(ptr->id),
        ptr->dependencyDictBottom == NULL ? "NULL" : dependencyDictElementToString(ptr->dependencyDictBottom),
        ptr->dependencyDictTop == NULL ? "NULL" : dependencyDictElementToString(ptr->dependencyDictTop)
        );
    return result;
}

const char* dependencyDictElementToString(const DependencyDictElement* ptr)
{
    char* result = malloc(1000);
    snprintf(result, 1000,
        "\tResource Location: %s\n"
        "\tDependency: %s\n"
        "\tVersion Comparitor: %s\n"
        "\tFlags: %i\n"
        "\tNext: %s\n"
        "\tPrevious: %s\n",
        resourceLocationToString(ptr->id),
        moduleToString(ptr->dependency),
        versionComparatorToString(ptr->versionComparator),
        ptr->flags,
        ptr->next == NULL ? "NULL" : dependencyDictElementToString(ptr->next),
        ptr->prev == NULL ? "NULL" : dependencyDictElementToString(ptr->prev)
        );
    return result;
}

void freeDependencyDict(DependencyDict* ptr)
{
    free(ptr);
}