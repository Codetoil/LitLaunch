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

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "litlaunch/litlaunch-library-api.h"
#include "litlaunch/location.h"
#include "litlaunch/dependencies.h"

// New entries are added to the top of the list
Module *moduleRegistryTop = NULL;
Module *moduleRegistryBottom = NULL;

const char* litlaunchNamespace = "litlaunch";

Module *initLibraryApi(void)
{
    ResourceLocation *versionLocation = newResourceLocation(litlaunchNamespace, 10,
        "litlaunch_library_api_version", 30,
        "litlaunch:litlaunch_library_api_version", 40);
    Version *version = newVersion(versionLocation, "0.2.1+build.3", 6);
    ResourceLocation *moduleLocation = newResourceLocation(litlaunchNamespace, 10,
        "litlaunch_library_api", 22,
        "litlaunch:litlaunch_library_api",32);
    ResourceLocation *dependencyDictLocation = newResourceLocation(litlaunchNamespace, 10,
        "litlaunch_library_api_dependency_dict", 38,
        "litlaunch:litlaunch_library_api_dependency_dict", 48);
    DependencyDict *dependencyDict = newDependencyDict(dependencyDictLocation);
    return newModule(moduleLocation, version, dependencyDict);
}

Version *newVersion(ResourceLocation* id, VersionValue version, VersionValueLength versionLength)
{
    Version* versionStruct = malloc(sizeof(*versionStruct) + versionLength);
    versionStruct->id = id;
    versionStruct->versionValue = version;
    versionStruct->versionValueLength = versionLength;
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


ResourceLocation *newResourceLocation(ResourceLocationNamespace _namespace, ResourceLocationNamespaceLength _namespaceLength,
    ResourceLocationPath _path, ResourceLocationPathLength _pathLength, ResourceLocationTotal _total,
    ResourceLocationTotalLength _totalLength)
{
    ResourceLocation* ptr = malloc(sizeof(*ptr) + (_namespaceLength + _pathLength + _totalLength) * sizeof(char));

    ptr->_namespace = _namespace;
    ptr->_namespaceLength = _namespaceLength;
    ptr->_path = _path;
    ptr->_pathLength = _pathLength;
    ptr->_total = _total;
    ptr->_totalLength = _totalLength;
    return ptr;
}

void freeResourceLocation(ResourceLocation *ptr)
{
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