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
#include "simple_string_lib.h"

#include <stdlib.h>
#include <string.h>

const ResourceLocationNamespace litlaunchNamespace = "litlaunch";

const ResourceLocation *newResourceLocation(const ResourceLocationNamespace _namespace,
                                            const ResourceLocationPath _path)
{
    const size_t _namespaceLength = strlen(_namespace);
    const size_t _pathLength = strlen(_path);
    const ResourceLocationTotal _total = concatenate(_namespace, ":", _path);
    const size_t _totalLength = strlen(_total);

    const ResourceLocation location = {_namespace, _path, _total};
    ResourceLocation* ptr = malloc(sizeof(*ptr) + (_namespaceLength + _pathLength + _totalLength) * sizeof(char));
    memcpy(ptr, &location, sizeof(ResourceLocation));
    return ptr;
}

char* resourceLocationToString(const ResourceLocation *ptr)
{
    char* result = malloc(strlen(ptr->_total) * sizeof(char));
    memcpy(result, ptr->_total, strlen(ptr->_total));
    return result;
}

void freeResourceLocation(ResourceLocation *ptr)
{
    free(ptr);
}