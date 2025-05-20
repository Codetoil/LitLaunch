//
// Created by codetoil on 5/19/25.
//


#include "litlaunch/location.h"
#include "litlaunch/dependencies.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t MAX_LENGTH_NUMBER = (CHAR_BIT * sizeof(int) - 1) / 3 + 2;
const size_t LENGTH_NEWLINE = strlen("\n");
const size_t LENGTH_TAB = strlen("\t");

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

char* internalModuleToString(const Module* ptr, const char* tabs)
{
    const size_t LENGTH_TABS = strlen(tabs);
    char* subTab = malloc((LENGTH_TABS + LENGTH_TAB) * sizeof(char));
    snprintf(subTab, LENGTH_TABS + LENGTH_TAB + 1, "%s\t", tabs);

    char* idString = resourceLocationToString(ptr->id);
    char* versionString = internalVersionToString(ptr->version, subTab);
    char* dependencyDictString = internalDependencyDictToString(ptr->dependencyDict, subTab);

    const size_t length = LENGTH_NEWLINE +
        LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE +
        LENGTH_TABS + 9 + strlen(versionString) + LENGTH_NEWLINE +
        LENGTH_TABS + 17 * strlen(dependencyDictString) + LENGTH_NEWLINE;

    char* result = malloc(length * sizeof(char));
    snprintf(result, length,
        "\n"
        "%sResource Location: %s\n"
        "%sVersion: %s\n"
        "%sDependency Dict: %s\n",
        tabs, idString,
        tabs, versionString,
        tabs, dependencyDictString);
    free(idString);
    free(versionString);
    free(dependencyDictString);
    free(subTab);
    return result;
}

char* moduleToString(const Module* ptr) {
    return internalModuleToString(ptr, "");
}

void freeModule(Module* ptr)
{
    Module* next = (Module*) ptr->next;
    Module* prev = (Module*) ptr->prev;
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
    const Version version = {id, versionValue};
    Version* ptr = malloc(sizeof(*ptr) + versionValueLength * sizeof(char));
    memcpy(ptr, &version, sizeof(Version));
    return ptr;
}

char* internalVersionToString(const Version* ptr, const char* tab)
{
    const size_t LENGTH_TABS = strlen(tab);

    char* idString = resourceLocationToString(ptr->id);

    const size_t length = LENGTH_NEWLINE +
        LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE +
            LENGTH_TABS + 14 + strlen(ptr->versionValue) + LENGTH_NEWLINE;
    char* result = malloc(length * sizeof(char));
    snprintf(result, length,
        "\n"
        "%sResource Location: %s\n"
        "%sVersionValue: %s\n",
        tab, resourceLocationToString(ptr->id),
        tab, ptr->versionValue);
    free(idString);
    return result;
}

char* versionToString(const Version* ptr) {
    return internalVersionToString(ptr, "");
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

char* internalVersionComparatorToString(const VersionComparator* ptr, const char* tab)
{
    const size_t LENGTH_TABS = strlen(tab);

    char* idString = resourceLocationToString(ptr->id);

    const size_t length = LENGTH_NEWLINE +
        LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE;

    char* result = malloc(length * sizeof(char));
    snprintf(result, length,
        "\n"
        "%sResource Location: %s\n",
        tab, idString);
    free(idString);
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
        dependencyDict->dependencyDictTop->nextElement = ptr;
    }
    dependencyDict->dependencyDictTop = ptr;
    return ptr;
}

void removeFromDependencyDictAndFree(DependencyDict* dependencyDict, DependencyDictElement* ptr)
{
    DependencyDictElement* next = ptr->nextElement;
    DependencyDictElement* prev = ptr->previousElement;
    if (next)
    {
        next->previousElement=prev;
    }
    if (prev)
    {
        prev->nextElement=next;
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

char* internalDependencyDictToString(const DependencyDict* ptr, const char* tab)
{
    const size_t LENGTH_TABS = strlen(tab);
    char* subTab = malloc((LENGTH_TABS + LENGTH_TAB) * sizeof(char));
    snprintf(subTab, LENGTH_TABS + LENGTH_TAB + 1, "%s\t", tab);

    char* idString = resourceLocationToString(ptr->id);

    const bool dependencyDictBottomNull = ptr->dependencyDictBottom == NULL;
    char* dependencyDictBottomString =
         dependencyDictBottomNull ? "NULL" :
            internalDependencyDictElementToString(ptr->dependencyDictBottom, subTab);
    const bool dependencyDictTopNull = ptr->dependencyDictTop == NULL;
    char* dependencyDictTopString =
         dependencyDictTopNull ? "NULL" :
            internalDependencyDictElementToString(ptr->dependencyDictTop, subTab);

    const size_t length = LENGTH_NEWLINE +
        LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE +
        LENGTH_TABS + 24 + strlen(dependencyDictBottomString) + LENGTH_NEWLINE +
        LENGTH_TABS + 21 + strlen(dependencyDictTopString) + LENGTH_NEWLINE;

    char* result = malloc(length * sizeof(char));
    snprintf(result, length,
        "\n"
        "%sResource Location: %s\n"
        "%sDependency Dict Bottom: %s\n"
        "%sDependency Dict Top: %s\n",
        tab, idString,
        tab, dependencyDictBottomString,
        tab, dependencyDictTopString
        );
    free(idString);
    if (!dependencyDictBottomNull)
        free(dependencyDictBottomString);
    if (!dependencyDictTopNull)
        free(dependencyDictTopString);
    free(subTab);
    return result;
}

char* dependencyDictToString(const DependencyDict* ptr)
{
    return internalDependencyDictToString(ptr, "");
}

char* internalDependencyDictElementToString(const DependencyDictElement* ptr, const char* tab)
{
    const size_t LENGTH_TABS = strlen(tab);
    char* subTab = malloc((LENGTH_TABS + LENGTH_TAB) * sizeof(char));
    snprintf(subTab, LENGTH_TABS + LENGTH_TAB + 1, "%s\t", tab);

    char* idString = resourceLocationToString(ptr->id);
    char* dependencyString = internalModuleToString(ptr->dependency, subTab);
    char* versionComparatorString = internalVersionComparatorToString(ptr->versionComparator, subTab);
    const bool nextElementNull = ptr->nextElement == NULL;
    char* nextElementString = nextElementNull ? "NULL" :
    internalDependencyDictElementToString(ptr->nextElement, subTab);
    const bool previousElementNull = ptr->previousElement == NULL;
    char* previousElementString = previousElementNull ? "NULL" :
    internalDependencyDictElementToString(ptr->previousElement, subTab);

    const size_t length = LENGTH_NEWLINE +
        LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE +
        LENGTH_TABS + 12 + strlen(dependencyString) + LENGTH_NEWLINE +
        LENGTH_TABS + 20 + strlen(versionComparatorString) + LENGTH_NEWLINE +
        LENGTH_TABS + 7 + MAX_LENGTH_NUMBER + LENGTH_NEWLINE +
        LENGTH_TABS + 14 + strlen(nextElementString) + LENGTH_NEWLINE +
        LENGTH_TABS + 18 + strlen(previousElementString) + LENGTH_NEWLINE;

    char* result = malloc(length * sizeof(char));
    snprintf(result, length,
        "\n"
        "%sResource Location: %s\n"
        "%sDependency: %s\n"
        "%sVersion Comparator: %s\n"
        "%sFlags: %i\n"
        "%sNext Element: %s\n"
        "%sPrevious Element: %s\n",
        tab, idString,
        tab, dependencyString,
        tab, versionComparatorString,
        tab, ptr->flags,
        tab, nextElementString,
        tab, previousElementString
        );
    free(idString);
    free(dependencyString);
    free(versionComparatorString);
    if (!nextElementNull)
        free(nextElementString);
    if (!previousElementNull)
        free(previousElementString);
    free(subTab);
    return result;
}

char* dependencyDictElementToString(const DependencyDictElement* ptr)
{
    return internalDependencyDictElementToString(ptr, "");
}

void freeDependencyDict(DependencyDict* ptr)
{
    free(ptr);
}