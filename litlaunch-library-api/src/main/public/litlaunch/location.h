/*
 * Copyright (C) 2019-2023 Anthony Michalek
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
typedef unsigned int ResourceLocationNamespaceLength;
typedef const char* ResourceLocationPath;
typedef unsigned int ResourceLocationPathLength;
typedef const char* ResourceLocationTotal;
typedef unsigned int ResourceLocationTotalLength;

typedef struct ResourceLocationStruct
{
    ResourceLocationNamespace _namespace;
    ResourceLocationNamespaceLength _namespaceLength;
    ResourceLocationPath _path;
    ResourceLocationPathLength _pathLength;
    ResourceLocationTotal _total;
    ResourceLocationTotalLength _totalLength;
} ResourceLocation;

extern ResourceLocation *newResourceLocation(ResourceLocationNamespace _namespace, ResourceLocationNamespaceLength _namespaceLength,
    ResourceLocationPath _path, ResourceLocationPathLength _pathLength, ResourceLocationTotal _total, ResourceLocationTotalLength _totalLength);
extern ResourceLocationNamespace getResourceLocationNamespace(ResourceLocation *ptr);
extern ResourceLocationNamespaceLength getResourceLocationNamespaceLength(ResourceLocation *ptr);
extern ResourceLocationPath getResourceLocationPath(ResourceLocation *ptr);
extern ResourceLocationPathLength getResourceLocationPathLength(ResourceLocation *ptr);
extern ResourceLocationTotal getResourceLocationTotal(ResourceLocation *ptr);
extern ResourceLocationTotalLength getResourceLocationTotalLength(ResourceLocation *ptr);
extern void freeResourceLocation(ResourceLocation *ptr);