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

#include "litlaunch/location.h"

#include <stdlib.h>

const ResourceLocationNamespace litlaunchNamespace = "litlaunch";
const ResourceLocationNamespaceLength litlaunchNamespaceLength = 10;

ResourceLocation *newResourceLocation(
    const ResourceLocationNamespace _namespace, const ResourceLocationNamespaceLength _namespaceLength,
    const ResourceLocationPath _path, const ResourceLocationPathLength _pathLength,
    const ResourceLocationTotal _total, const ResourceLocationTotalLength _totalLength)
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