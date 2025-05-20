/*
* Copyright (C) 2019-2025 Anthony Michalek
 * Contact me on Discord: @codetoil, or by Email: ianthisawesomee@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "c_semver.h"

#include "litlaunch/location.h"
#include "litlaunch/dependencies.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t MAX_LENGTH_NUMBER = (CHAR_BIT * sizeof(int) - 1) / 3 + 2;
const size_t LENGTH_NEWLINE = strlen("\n");
const size_t LENGTH_TAB = strlen("\t");

ResourceLocation* SEMVER2_0_0_LOCATION;
VersionComparator* SEMVER2_0_0_COMPARATOR;

// New entries are added to the top of the list
Module *moduleRegistryTop = NULL;
Module *moduleRegistryBottom = NULL;

VersionComparatorResult comparePrereleases(const char* inputPrerelease, const char* comparisonPrerelease,
    const size_t inputPrereleaseLength, const size_t comparisonPrereleaseLength) {
    VersionComparatorResult result = VERSION_INVALID;
    size_t i;
    for (i = 0;
        i < (inputPrereleaseLength < comparisonPrereleaseLength ?
            inputPrereleaseLength : comparisonPrereleaseLength); i++) {
        const char inputPrereleaseChar = inputPrerelease[i];
        const char comparisonPrereleaseChar = comparisonPrerelease[i];
        if (inputPrereleaseChar < comparisonPrereleaseChar) {
            result = VERSION_TOO_OLD;
        } else if (inputPrereleaseChar > comparisonPrereleaseChar) {
            result = VERSION_TOO_NEW;
        }
    }
    if (result == VERSION_INVALID) {
        if (inputPrereleaseLength < comparisonPrereleaseLength) {
            result = VERSION_TOO_OLD;
        } else if (inputPrereleaseLength > comparisonPrereleaseLength) {
            result = VERSION_TOO_NEW;
        } else {
            result = VERSION_MATCH;
        }
    }
    return result;
}

const VersionComparatorResult semver2_0_0Apply(const Version* input, const Version* comparison) {
    struct semver_context contextInput;
    struct semver_context contextComparison;
    VersionComparatorResult result;
    semver_init(&contextInput, input->versionValue);
    semver_init(&contextComparison, comparison->versionValue);
    if (semver_parse(&contextInput) != SEMVER_PARSE_OK || semver_parse(&contextComparison) != SEMVER_PARSE_OK) {
        result = VERSION_INVALID;
    } else {
        if (contextInput.major < contextComparison.major) {
            result = VERSION_TOO_OLD;
        } else if (contextInput.major > contextComparison.major) {
            result = VERSION_TOO_NEW;
        } else {
            if (contextInput.minor < contextComparison.minor) {
                result = VERSION_TOO_OLD;
            } else if (contextInput.minor > contextComparison.minor) {
                result = VERSION_TOO_NEW;
            } else {
                if (contextInput.patch < contextComparison.patch) {
                    result = VERSION_TOO_OLD;
                } else if (contextInput.patch > contextComparison.patch) {
                    result = VERSION_TOO_NEW;
                } else {
                    if (contextInput.is_prerelease) {
                        if (contextComparison.is_prerelease) {
                            result = comparePrereleases(contextInput.prerelease,
                                contextComparison.prerelease,
                                contextInput.prerelease_size,
                                contextComparison.prerelease_size);
                        } else {
                            result = VERSION_TOO_OLD;
                        }
                    } else {
                        if (contextComparison.is_prerelease) {
                            result = VERSION_TOO_NEW;
                        } else {
                            result = VERSION_MATCH;
                        }
                    }
                }
            }
        }
    }
    semver_free(&contextInput);
    semver_free(&contextComparison);
    return result;
}

const VersionComparator* getSemver2_0_0Comparator() {
    return SEMVER2_0_0_COMPARATOR;
}

void initVersionComparators() {
    SEMVER2_0_0_LOCATION = (ResourceLocation*) newResourceLocation(litlaunchNamespace, "semver2_0_0_location");
    SEMVER2_0_0_COMPARATOR = newVersionComparator(SEMVER2_0_0_LOCATION, &semver2_0_0Apply);
}

void freeVersionComparators() {
    freeResourceLocation(SEMVER2_0_0_LOCATION);
    freeVersionComparator(SEMVER2_0_0_COMPARATOR);
}

bool pointerInPointerArray(const void* val, const void **arr, const size_t size) {
    if (arr == NULL) return false;
    size_t i;
    for(i = 0; i < size / sizeof(*arr); i++) {
        if(arr[i] == val)
            return true;
    }
    return false;
}

Module *newModule(const ResourceLocation* id, const Version* version, const DependencyDict* dependencyDict)
{
    assert(!!id); // ID for Module is NULL ;
    assert(!!id->_namespace && !!id->_path && !!id->_total); // ID for Module is Broken
    assert(!!version); // Version for Module is NULL
    assert(!!version->id && !!version->versionValue); // Version for Module is Broken
    assert(!!version->id->_namespace && !!version->id->_path && !!version->id->_total); // ID for Version for Module is Broken
    assert(!!dependencyDict); // Dependency Dict for Module is NULL
    assert(!!dependencyDict->id); // Dependency Dict for Module is Broken  id->_total);
    assert(!!dependencyDict->id->_namespace && !!dependencyDict->id->_path && !!dependencyDict->id->_total); // ID for Dependency Dict for Module is Broken
    const Module module = {id, version, dependencyDict, NULL, moduleRegistryTop};
    Module* ptr = malloc(sizeof(*ptr));
    if (!ptr) {
        return NULL;
    }
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

char* internalModuleToString(const Module* ptr, const char* tabs,
    const void** ignored, const size_t ignoredLength)
{
    assert(!!ptr); // Module is NULL
    assert(!!ptr->id); // Module ID is NULL
    assert(!!ptr->id->_namespace && !!ptr->id->_path && !!ptr->id->_total); // Module ID is Broken
    assert(!!tabs); // Tabs for Module is NULL
    const size_t LENGTH_TABS = strlen(tabs);
    char* subTab = malloc((LENGTH_TABS + LENGTH_TAB) * sizeof(char));
    if (!subTab) {
        return NULL;
    }
    snprintf(subTab, LENGTH_TABS + LENGTH_TAB + 1, "%s\t", tabs);

    char* idString = resourceLocationToString(ptr->id);
    if (!idString) {
        free(subTab);
        return NULL;
    }
    if (pointerInPointerArray(ptr, ignored, ignoredLength)) {
        const size_t length = LENGTH_NEWLINE +
            LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE;

        char* result = malloc(length * sizeof(char));
        if (!result) {
            free(subTab);
            free(idString);
            return NULL;
        }
        snprintf(result, length,
            "\n"
            "%sResource Location: %s\n",
            tabs, idString);
        free(idString);
        free(subTab);
        return result;
    }
    const size_t newIgnoredLength = ignoredLength + 1;
    const void** newIgnored = malloc(newIgnoredLength * sizeof(const void*));
    if (!newIgnored) {
        free(subTab);
        free(idString);
        return NULL;
    }
    memcpy(newIgnored, ignored, ignoredLength * sizeof(const void*));
    newIgnored[ignoredLength] = ptr;
    char* versionString = internalVersionToString(ptr->version, subTab);
    if (!versionString) {
        free(subTab);
        free(idString);
        free(newIgnored);
        return NULL;
    }
    char* dependencyDictString = internalDependencyDictToString(ptr->dependencyDict, subTab,
                                                                newIgnored, newIgnoredLength);
    if (!dependencyDictString) {
        free(subTab);
        free(idString);
        free(newIgnored);
        free(versionString);
        return NULL;
    }

    const size_t length = LENGTH_NEWLINE +
                          LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE +
                          LENGTH_TABS + 9 + strlen(versionString) + LENGTH_NEWLINE +
                          LENGTH_TABS + 17 * strlen(dependencyDictString) + LENGTH_NEWLINE;

    char* result = malloc(length * sizeof(char));
    if (!result) {
        free(subTab);
        free(idString);
        free(newIgnored);
        free(versionString);
        free(dependencyDictString);
        return NULL;
    }
    snprintf(result, length,
             "\n"
             "%sResource Location: %s\n"
             "%sVersion: %s\n"
             "%sDependency Dict: %s\n",
             tabs, idString,
             tabs, versionString,
             tabs, dependencyDictString);
    free(subTab);
    free(idString);
    free(newIgnored);
    free(versionString);
    free(dependencyDictString);
    return result;
}

char* moduleToString(const Module* ptr) {
    return internalModuleToString(ptr, "", NULL, 0);
}

void freeModule(Module* ptr)
{
    assert(!!ptr); // Module is NULL
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
    assert(!!id); // ID for Version is NULL
    assert(!!id->_namespace && !!id->_path && !!id->_total); // ID for Version is Broken
    assert(!!versionValue); // VersionValue for Version is NULL
    const size_t versionValueLength = strlen(versionValue);
    const Version version = {id, versionValue};
    Version* ptr = malloc(sizeof(*ptr) + versionValueLength * sizeof(char));
    if (!ptr) {
        return NULL;
    }
    memcpy(ptr, &version, sizeof(Version));
    return ptr;
}

char* internalVersionToString(const Version* ptr, const char* tabs)
{
    assert(!!ptr); // Version is NULL
    assert(!!ptr->id); // Version ID is NULL
    assert(!!ptr->id->_namespace && !!ptr->id->_path && !!ptr->id->_total); // Version ID is Broken
    assert(!!ptr->versionValue); // VersionValue for Version is NULL
    assert(!!tabs); // Tabs for Version is NULL
    const size_t LENGTH_TABS = strlen(tabs);

    char* idString = resourceLocationToString(ptr->id);
    if (!idString) {
        return NULL;
    }

    const size_t length = LENGTH_NEWLINE +
        LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE +
            LENGTH_TABS + 14 + strlen(ptr->versionValue) + LENGTH_NEWLINE;
    char* result = malloc(length * sizeof(char));
    if (!result) {
        free(idString);
        return NULL;
    }
    snprintf(result, length,
        "\n"
        "%sResource Location: %s\n"
        "%sVersionValue: %s\n",
        tabs, resourceLocationToString(ptr->id),
        tabs, ptr->versionValue);
    free(idString);
    return result;
}

char* versionToString(const Version* ptr) {
    return internalVersionToString(ptr, "");
}

void freeVersion(Version* ptr)
{
    assert(!!ptr); // Version is NULL
    free(ptr);
}

VersionComparator *newVersionComparator(const ResourceLocation* id,
    const VersionComparatorResult (apply)(const Version*, const Version*))
{
    assert(!!id); // ID for Version Comparator is NULL
    assert(!!id->_namespace && !!id->_path && !!id->_total); // ID for Version Comparator is Broken
    assert(!!apply); // No comparison function for Version Comparator
    const VersionComparator versionComparator = {id, apply};
    VersionComparator* ptr = malloc(sizeof(*ptr));
    if (!ptr) return NULL;
    memcpy(ptr, &versionComparator, sizeof(VersionComparator));
    return ptr;
}

char* internalVersionComparatorToString(const VersionComparator* ptr, const char* tabs)
{
    assert(!!ptr); // Version Comparator is NULL
    assert(!!ptr->id); // Version Comparator ID is NULL
    assert(!!ptr->id->_namespace && !!ptr->id->_path && !!ptr->id->_total); // Version Comparator ID is Broken
    assert(!!ptr->apply); // No comparison function for Version Comparator
    assert(!!tabs); // Tabs for Version Comparator is NULL
    const size_t LENGTH_TABS = strlen(tabs);

    char* idString = resourceLocationToString(ptr->id);
    if (!idString) {
        return NULL;
    }

    const size_t length = LENGTH_NEWLINE +
        LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE;

    char* result = malloc(length * sizeof(char));
    if (!result) {
        free(idString);
        return NULL;
    }
    snprintf(result, length,
        "\n"
        "%sResource Location: %s\n",
        tabs, idString);
    free(idString);
    return result;
}

char* versionComparatorToString(const VersionComparator* ptr) {
    return internalVersionComparatorToString(ptr, "");
}

void freeVersionComparator(VersionComparator* ptr)
{
    assert(!!ptr); // Version Comparator is NULL
    free(ptr);
}

DependencyDict *newDependencyDict(const ResourceLocation* id)
{
    assert(!!id); // ID for Dependency Dict is NULL
    assert(!!id->_namespace && !!id->_path && !!id->_total); // ID for Dependency Dict is Broken
    const DependencyDict dependencyDict = {id, NULL, NULL};
    DependencyDict* ptr = malloc(sizeof(*ptr));
    if (!ptr) {
        return NULL;
    }
    memcpy(ptr, &dependencyDict, sizeof(DependencyDict));
    return ptr;
}

DependencyDictElement *addToDependencyDict(DependencyDict* dependencyDict, const ResourceLocation* id,
    const Module* module, const VersionComparator* versionComparator, const u_int8_t flags)
{
    assert(!!dependencyDict); // Dependency Dict is NULL
    assert(!!dependencyDict->id); // ID for Dependency Dict is NULL
    assert(!!dependencyDict->id->_namespace && !!dependencyDict->id->_path && !!dependencyDict->id->_total); // ID for Dependency Dict is Broken );
    assert(!!id); // ID for Dependency Dict Element of Dependency Dict is NULL
    assert(!!id->_namespace && !!id->_path && !!id->_total); // ID for Dependency Dict Element of Dependency Dict is Broken
    assert(!!module); // Module for Dependency Dict Element of Dependency Dict is NULL
    assert(!!module->id); // ID for Module for Dependency Dict Element of Dependency Dict is NULL
    assert(!!module->id->_namespace && !!module->id->_path && !!module->id->_total); // ID for Module for Dependency Dict Element of Dependency Dict is Broken
    assert(!!module->dependencyDict); // Dependency Dict listed in Module for Dependency Dict Element of Dependency Dict is NULL
    assert(!!module->version); // Version listed in Module for Dependency Dict Element of Dependency Dict is NULL
    assert(!!module->version->id); // ID for Version listed in Module for Dependency Dict Element of Dependency Dict is NULL
    assert(!!module->version->id->_namespace && !!module->version->id->_path && !!module->version->id->_total); // ID for Version listed in Module for Dependency Dict Element of Dependency Dict is Broken
    assert(!!module->version->versionValue); // VersionValue for Version listed in Module for Dependency Dict Element of Dependency Dict is Broken
    assert(!!versionComparator); // Version Comparator for Dependency Dict Element of Dependency Dict is NULL
    assert(!!versionComparator->id); // ID for Version Comparator for Dependency Dict Element of Dependency Dict is NULL
    assert(!!versionComparator->id->_namespace && !!versionComparator->id->_path && !!versionComparator->id->_total); // ID for Version Comparator for Dependency Dict Element of Dependency Dict is Broken
    assert(!!versionComparator->apply); // No comparison function for Version Comparator for Dependency Dict Element of Dependency Dict
    const DependencyDictElement dependencyDictElement =
        {id, module, versionComparator, flags, NULL, dependencyDict->dependencyDictTop};
    DependencyDictElement* ptr = malloc(sizeof(*ptr));
    if (!ptr) {
        return NULL;
    }
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
    assert(!!dependencyDict); // Dependency Dict is NULL
    assert(!!dependencyDict->id); // ID of Dependency Dict is NULL
    assert(!!dependencyDict->id->_namespace && !!dependencyDict->id->_path && !!dependencyDict->id->_total); // ID of Dependency Dict is Broken
    assert(!!ptr); // Dependency Dict Element to Remove is NULL
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

char* internalDependencyDictToString(const DependencyDict* ptr, const char* tabs,
    const void** ignored, const size_t ignoredLength)
{
    assert(!!ptr); // Dependency Dict is NULL
    assert(!!ptr->id); // Dependency Dict ID is NULL
    assert(!!ptr->id->_total); // Dependency Dict ID is Broken
    assert(!!tabs); // Tabs for Dependency Dict is NULL
    const size_t LENGTH_TABS = strlen(tabs);
    char* subTab = malloc((LENGTH_TABS + LENGTH_TAB) * sizeof(char));
    if (!subTab) return NULL;
    snprintf(subTab, LENGTH_TABS + LENGTH_TAB + 1, "%s\t", tabs);

    char* idString = resourceLocationToString(ptr->id);
    if (!idString) {
        free(subTab);
        return NULL;
    }
    if (pointerInPointerArray(ptr, ignored, ignoredLength)) {
        const size_t length = LENGTH_NEWLINE +
        LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE;

        char* result = malloc(length * sizeof(char));
        if (!result) {
            free(subTab);
            free(idString);
            return NULL;
        }
        snprintf(result, length,
            "\n"
            "%sResource Location: %s\n",
            tabs, idString
            );
        free(idString);
        free(subTab);
        return result;
    }
    const size_t newIgnoredLength = ignoredLength + 1;
    const void** newIgnored = malloc(newIgnoredLength * sizeof(const void*));
    if (!newIgnored) {
        free(subTab);
        free(idString);
        return NULL;
    }
    memcpy(newIgnored, ignored, ignoredLength * sizeof(const void*));
    newIgnored[ignoredLength] = ptr;

    const bool dependencyDictBottomNull = ptr->dependencyDictBottom == NULL;
    char* dependencyDictBottomString =
         dependencyDictBottomNull ? "NULL" :
            internalDependencyDictElementToString(ptr->dependencyDictBottom, subTab, newIgnored, newIgnoredLength);
    if (!dependencyDictBottomString) {
        free(subTab);
        free(idString);
        free(newIgnored);
        return NULL;
    }
    const bool dependencyDictTopNull = ptr->dependencyDictTop == NULL;
    char* dependencyDictTopString =
         dependencyDictTopNull ? "NULL" :
            internalDependencyDictElementToString(ptr->dependencyDictTop, subTab, newIgnored, newIgnoredLength);
    if (!dependencyDictTopString) {
        free(subTab);
        free(idString);
        free(newIgnored);
        free(dependencyDictBottomString);
        return NULL;
    }

    const size_t length = LENGTH_NEWLINE +
        LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE +
        LENGTH_TABS + 24 + strlen(dependencyDictBottomString) + LENGTH_NEWLINE +
        LENGTH_TABS + 21 + strlen(dependencyDictTopString) + LENGTH_NEWLINE;

    char* result = malloc(length * sizeof(char));
    if (!result) {
        free(subTab);
        free(idString);
        free(newIgnored);
        free(dependencyDictBottomString);
        free(dependencyDictTopString);
        return NULL;
    }
    snprintf(result, length,
        "\n"
        "%sResource Location: %s\n"
        "%sDependency Dict Bottom: %s\n"
        "%sDependency Dict Top: %s\n",
        tabs, idString,
        tabs, dependencyDictBottomString,
        tabs, dependencyDictTopString
        );
    free(subTab);
    free(idString);
    free(newIgnored);
    if (!dependencyDictBottomNull)
        free(dependencyDictBottomString);
    if (!dependencyDictTopNull)
        free(dependencyDictTopString);
    return result;
}

char* dependencyDictToString(const DependencyDict* ptr)
{
    return internalDependencyDictToString(ptr, "", NULL, 0);
}

char* internalDependencyDictElementToString(const DependencyDictElement* ptr, const char* tabs,
    const void** ignored, const size_t ignoredLength)
{
    assert(!!ptr); // Dependency Dict Element is NULL
    assert(!!ptr->id); // Dependency Dict Element ID is NULL
    assert(!!ptr->id->_namespace && !!ptr->id->_path && !!ptr->id->_total); // Dependency Dict Element ID is Broken
    assert(!!ptr->dependency); // Module for Dependency Dict Element is NULL
    assert(!!ptr->dependency->id); // ID for Module for Dependency Dict Element is NULL
    assert(!!ptr->dependency->id->_namespace && !!ptr->dependency->id->_path && !!ptr->dependency->id->_total); // ID for Module for Dependency Dict Element is Broken
    assert(!!ptr->dependency->dependencyDict); // Dependency Dict listed in Module for Dependency Dict Element is NULL
    assert(!!ptr->dependency->version); // Version listed in Module for Dependency Dict Element is NULL
    assert(!!ptr->dependency->version->id); // ID for Version listed in Module for Dependency Dict Element is NULL
    assert(!!ptr->dependency->version->id->_namespace && !!ptr->dependency->version->id->_path
        && !!ptr->dependency->version->id->_total); // ID for Version listed in Module for Dependency Dict Element is Broken
    assert(!!ptr->dependency->version->versionValue); // VersionValue for Version listed in Module for Dependency Dict Element is Broken
    assert(!!ptr->versionComparator); // Version Comparator for Dependency Dict Element is NULL
    assert(!!ptr->versionComparator->id); // ID for Version Comparator for Dependency Dict Element is NULL
    assert(!!ptr->versionComparator->id->_namespace && !!ptr->versionComparator->id->_path
        && !!ptr->versionComparator->id->_total); // ID for Version Comparator for Dependency Dict Element is Broken
    assert(!!ptr->versionComparator->id->_namespace && !!ptr->versionComparator->id->_path
        && !!ptr->versionComparator->id->_total); // No comparison function for Version Comparator for Dependency Dict Element
    assert(!!tabs); // Tabs for Dependency Dict Element is NULL
    const size_t LENGTH_TABS = strlen(tabs);
    char* subTab = malloc((LENGTH_TABS + LENGTH_TAB) * sizeof(char));
    if (!subTab) {
        return NULL;
    }
    snprintf(subTab, LENGTH_TABS + LENGTH_TAB + 1, "%s\t", tabs);

    if (pointerInPointerArray(ptr, ignored, ignoredLength)) {
        char* idString = resourceLocationToString(ptr->id);
        if (!idString) {
            free(subTab);
            return NULL;
        }
        const size_t length = LENGTH_NEWLINE +
        LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE;

        char* result = malloc(length * sizeof(char));
        if (!result) {
            free(subTab);
            free(idString);
            return NULL;
        }
        snprintf(result, length,
            "\n"
            "%sResource Location: %s\n",
            tabs, idString
            );
        free(idString);
        free(subTab);
        return result;
    }
    char* idString = resourceLocationToString(ptr->id);
    if (!idString) {
        free(subTab);
        return NULL;
    }

    const size_t newIgnoredLength = ignoredLength + 1;
    const void** newIgnored = malloc(newIgnoredLength * sizeof(const void*));
    if (!newIgnored) {
        free(subTab);
        free(idString);
        return NULL;
    }
    memcpy(newIgnored, ignored, ignoredLength * sizeof(const void*));
    newIgnored[ignoredLength] = ptr;

    char* dependencyString = internalModuleToString(ptr->dependency, subTab, newIgnored, newIgnoredLength);
    if (!dependencyString) {
        free(subTab);
        free(newIgnored);
        free(idString);
        return NULL;
    }
    char* versionComparatorString = internalVersionComparatorToString(ptr->versionComparator, subTab);
    if (!versionComparatorString) {
        free(subTab);
        free(newIgnored);
        free(idString);
        free(dependencyString);
        return NULL;
    }
    const bool nextElementNull = ptr->nextElement == NULL;
    char* nextElementString = nextElementNull ? "NULL" :
    internalDependencyDictElementToString(ptr->nextElement, subTab, newIgnored, newIgnoredLength);
    if (!nextElementString) {
        free(subTab);
        free(newIgnored);
        free(idString);
        free(dependencyString);
        free(versionComparatorString);
        return NULL;
    }
    const bool previousElementNull = ptr->previousElement == NULL;
    char* previousElementString = previousElementNull ? "NULL" :
    internalDependencyDictElementToString(ptr->previousElement, subTab, newIgnored, newIgnoredLength);
    if (!previousElementString) {
        free(subTab);
        free(idString);
        free(newIgnored);
        free(dependencyString);
        free(versionComparatorString);
        free(nextElementString);
        return NULL;
    }

    const size_t length = LENGTH_NEWLINE +
        LENGTH_TABS + 19 + strlen(idString) + LENGTH_NEWLINE +
        LENGTH_TABS + 12 + strlen(dependencyString) + LENGTH_NEWLINE +
        LENGTH_TABS + 20 + strlen(versionComparatorString) + LENGTH_NEWLINE +
        LENGTH_TABS + 7 + MAX_LENGTH_NUMBER + LENGTH_NEWLINE +
        LENGTH_TABS + 14 + strlen(nextElementString) + LENGTH_NEWLINE +
        LENGTH_TABS + 18 + strlen(previousElementString) + LENGTH_NEWLINE;

    char* result = malloc(length * sizeof(char));
    if (!result) {
        free(subTab);
        free(idString);
        free(newIgnored);
        free(dependencyString);
        free(versionComparatorString);
        free(nextElementString);
        free(previousElementString);
        return NULL;
    }
    snprintf(result, length,
        "\n"
        "%sResource Location: %s\n"
        "%sDependency: %s\n"
        "%sVersion Comparator: %s\n"
        "%sFlags: %i\n"
        "%sNext Element: %s\n"
        "%sPrevious Element: %s\n",
        tabs, idString,
        tabs, dependencyString,
        tabs, versionComparatorString,
        tabs, ptr->flags,
        tabs, nextElementString,
        tabs, previousElementString
        );
    free(subTab);
    free(idString);
    free(newIgnored);
    free(dependencyString);
    free(versionComparatorString);
    if (!nextElementNull)
        free(nextElementString);
    if (!previousElementNull)
        free(previousElementString);
    return result;
}

char* dependencyDictElementToString(const DependencyDictElement* ptr)
{
    return internalDependencyDictElementToString(ptr, "", NULL, 0);
}

void freeDependencyDict(DependencyDict* ptr)
{
    assert(ptr); // Dependency Dict is NULL
    free(ptr);
}