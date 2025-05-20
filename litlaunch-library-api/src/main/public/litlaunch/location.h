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
#include <stddef.h>

typedef const char* ResourceLocationNamespace;
typedef const char* ResourceLocationPath;
typedef const char* ResourceLocationTotal;

extern const ResourceLocationNamespace litlaunchNamespace;

typedef struct ResourceLocationStruct
{
    const ResourceLocationNamespace _namespace;
    const size_t _namespaceLength;
    const ResourceLocationPath _path;
    const size_t _pathLength;
    const ResourceLocationTotal _total;
    const size_t _totalLength;
} ResourceLocation;

extern const ResourceLocation *newResourceLocation(ResourceLocationNamespace _namespace, ResourceLocationPath _path);
extern ResourceLocationNamespace getResourceLocationNamespace(const ResourceLocation *ptr);
extern size_t getResourceLocationNamespaceLength(const ResourceLocation *ptr);
extern ResourceLocationPath getResourceLocationPath(const ResourceLocation *ptr);
extern size_t getResourceLocationPathLength(const ResourceLocation *ptr);
extern ResourceLocationTotal getResourceLocationTotal(const ResourceLocation *ptr);
extern size_t getResourceLocationTotalLength(const ResourceLocation *ptr);
extern const char* resourceLocationToString(const ResourceLocation *ptr);
extern void freeResourceLocation(ResourceLocation *ptr);