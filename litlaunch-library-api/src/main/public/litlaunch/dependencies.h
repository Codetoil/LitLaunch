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

#include <sys/types.h>

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
    VERSION_TOO_OLD = -1,
    VERSION_MATCH = 0,
    VERSION_TOO_NEW = 1,
    VERSION_INVALID = 2
} VersionComparatorResult;

typedef struct VersionStruct Version;

typedef struct VersionComparatorStruct {
    const ResourceLocation *id;
    const VersionComparatorResult (*apply)(const Version*, const Version*);
} VersionComparator;

typedef const char* VersionValue;

typedef struct VersionStruct
{
    const ResourceLocation *id;
    const VersionValue versionValue;
} Version;

typedef struct DependencyDictStruct DependencyDict;

typedef struct ModuleStruct Module;

typedef struct ModuleStruct
{
    const ResourceLocation *id;
    const Version *version;
    const DependencyDict *dependencyDict;
    const Module* next;
    const Module* prev;
} Module;

typedef struct DependencyDictElementStruct DependencyDictElement;

typedef struct DependencyDictElementStruct
{
    const ResourceLocation *id;
    const Module *dependency;
    const VersionComparator *versionComparator;
    const u_int8_t flags;
    DependencyDictElement* nextElement;
    DependencyDictElement* previousElement;
} DependencyDictElement;

typedef struct DependencyDictStruct
{
    const ResourceLocation *id;
    DependencyDictElement *dependencyDictTop;
    DependencyDictElement *dependencyDictBottom;
} DependencyDict;

VersionComparatorResult comparePrereleases(const char* inputPrerelease, const char* comparisonPrerelease,
    size_t inputPrereleaseLength, size_t comparisonPrereleaseLength);
VersionComparatorResult semver2_0_0Apply(const Version* input, const Version* comparison);
extern const VersionComparator* getSemver2_0_0Comparator();
void initVersionComparators();
void freeVersionComparators();

extern Module *newModule(const ResourceLocation* id, const Version* version, const DependencyDict* dependencyDict);
extern char* moduleToString(const Module* ptr);
char* internalModuleToString(const Module* ptr, const char* tabs,
    const void** ignored, size_t ignoredLength);
extern void freeModule(Module* ptr);

extern Version *newVersion(const ResourceLocation* id, VersionValue versionValue);
extern char* versionToString(const Version* ptr);
char* internalVersionToString(const Version* ptr, const char* tabs);
extern void freeVersion(Version* ptr);

extern VersionComparator *newVersionComparator(const ResourceLocation* id,
    const VersionComparatorResult (apply)(const Version*, const Version*));
extern char* versionComparatorToString(const VersionComparator* ptr);
char* internalVersionComparatorToString(const VersionComparator* ptr, const char* tabs);
extern void freeVersionComparator(VersionComparator* ptr);

extern DependencyDict *newDependencyDict(const ResourceLocation* id);
extern DependencyDictElement *addToDependencyDict(DependencyDict* dependencyDict,
    const ResourceLocation* id, const Module* module, const VersionComparator* versionComparator,
    u_int8_t flags);
extern void removeFromDependencyDictAndFree(DependencyDict* dependencyDict, DependencyDictElement* ptr);
extern char* dependencyDictToString(const DependencyDict* ptr);
char* internalDependencyDictToString(const DependencyDict* ptr, const char* tabs,
    const void** ignored, size_t ignoredLength);
extern char* dependencyDictElementToString(const DependencyDictElement* ptr);
char* internalDependencyDictElementToString(const DependencyDictElement* ptr, const char* tabs,
    const void** ignored, size_t ignoredLength);
extern void freeDependencyDict(DependencyDict* ptr);
