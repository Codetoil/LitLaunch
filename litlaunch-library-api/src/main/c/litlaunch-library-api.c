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
#include "litlaunch/dependencies.h"
#include "litlaunch/litlaunch-library-api.h"

Module *initLibraryApi(void)
{
    const ResourceLocation *versionLocation =
        newResourceLocation(litlaunchNamespace, "litlaunch_library_api_version");
    const Version *version = newVersion(versionLocation, "0.2.3+build.6");
    const ResourceLocation *moduleLocation =
        newResourceLocation(litlaunchNamespace, "litlaunch_library_api");
    const ResourceLocation *dependencyDictLocation =
        newResourceLocation(litlaunchNamespace, "litlaunch_library_api_dependency_dict");
    const DependencyDict *dependencyDict = newDependencyDict(dependencyDictLocation);
    return newModule(moduleLocation, version, dependencyDict);
}

void freeLitLaunchLibraryApi(Module* apiModule) {
    freeResourceLocation((ResourceLocation*) apiModule->version->id);
    freeVersion((Version*) apiModule->version);
    freeResourceLocation((ResourceLocation*) apiModule->dependencyDict->id);
    freeDependencyDict((DependencyDict*) apiModule->dependencyDict);
    freeResourceLocation((ResourceLocation*) apiModule->id);
    freeModule(apiModule);
}