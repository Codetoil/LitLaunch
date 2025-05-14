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

#pragma once

#include <stdbool.h>
#include "location.h"

typedef enum EnumDependencyType
{
    DYNAMIC_DEP = 0,
    STATIC_DEP = 1
} DependencyType;

typedef enum EnumDependencyRequirement
{
    OPTIONAL_DEP = 0,
    REQUIRED_DEP = 1
} DependencyRequirement;

typedef enum EnumVersionComparatorResult
{
    TOO_OLD = -1,
    JUST_RIGHT = 0,
    TOO_NEW = 1
} VersionComparatorResult;

typedef struct VersionStruct Version;

typedef VersionComparatorResult (*VersionComparator)(const Version*);

typedef const char* VersionValue;
typedef unsigned int VersionValueLength;

typedef struct VersionStruct
{
    ResourceLocation *id;
    VersionValue versionValue;
    VersionValueLength versionValueLength;
} Version;

typedef struct DependencyDictStruct DependencyDict;

typedef struct ModuleStruct Module;

typedef struct ModuleStruct
{
    ResourceLocation *id;
    Version *version;
    DependencyDict *dependencyDict;
    Module* next;
    Module* prev;
} Module;

typedef struct DependencyDictElementStruct DependencyDictElement;

typedef struct DependencyDictElementStruct
{
    ResourceLocation *id;
    Module *dependency;
    VersionComparator *versionComparator;
    u_int8_t flags;
    DependencyDictElement* next;
    DependencyDictElement* prev;
} DependencyDictElement;

typedef struct DependencyDictStruct
{
    ResourceLocation *id;
    DependencyDictElement *dependencyDictTop;
    DependencyDictElement *dependencyDictBottom;
} DependencyDict;

extern Module *newModule(ResourceLocation* id, Version* version, DependencyDict* dependencyDict);
extern void freeModule(Module* ptr);

extern Version *newVersion(ResourceLocation* id, VersionValue versionValue,
    VersionValueLength versionValueLength);
extern void freeVersion(Version* ptr);

extern DependencyDict *newDependencyDict(ResourceLocation* id);
extern DependencyDictElement *addToDependencyDict(DependencyDict* dict, ResourceLocation* id,
    Module* module, VersionComparator* versionComparator, u_int8_t flags);
extern void removeFromDependencyDictAndFree(DependencyDict* dict, DependencyDictElement* ptr);
extern void freeDependencyDict(DependencyDict* ptr);