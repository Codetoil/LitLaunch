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

#include <assert.h>
#include <stdio.h>
#include "litlaunch/dependencies.h"
#include "litlaunch/litlaunch-library-api.h"

Module *initLibraryApiTests(Module* apiModule)
{
    const ResourceLocation *versionLocation =
        newResourceLocation(litLaunchNamespace, "litlaunch_library_api_tests_version");
    const Version *version = newVersion(versionLocation, "0.1.1+build.3");
    const ResourceLocation *moduleLocation =
        newResourceLocation(litLaunchNamespace, "litlaunch_library_api_tests");
    const ResourceLocation *dependencyDictLocation =
        newResourceLocation(litLaunchNamespace, "litlaunch_library_api_tests_dependency_dict");
    DependencyDict *dependencyDict = newDependencyDict(dependencyDictLocation);
    const ResourceLocation *apiDependencyDictElementLocation =
        newResourceLocation(litLaunchNamespace, "litlaunch_library_api_tests_api_dependency_dict_element");
    const ResourceLocation *apiVersionLocation =
        newResourceLocation(litLaunchNamespace, "litlaunch_library_api_version");
    const Version *apiVersion = newVersion(apiVersionLocation, "0.2.4+build.2");
    addToDependencyDict(dependencyDict, apiDependencyDictElementLocation, apiModule,
        apiVersion, getSemver2_0_0Comparator(), 0b00000000);
    return newModule(moduleLocation, version, dependencyDict);
}

void freeLibraryApiTests(Module* apiTestsModule) {
    freeResourceLocation((ResourceLocation*) apiTestsModule->version->id);
    freeVersion((Version*) apiTestsModule->version);
    freeResourceLocation((ResourceLocation*) apiTestsModule->dependencyDict->id);
    freeDependencyDict((DependencyDict*) apiTestsModule->dependencyDict);
    freeResourceLocation((ResourceLocation*) apiTestsModule->id);
    freeModule(apiTestsModule);
}

int main()
{
    printf("DYNAMIC_DEP: %i\n", DYNAMIC_DEP);
    printf("STATIC_DEP: %i\n\n", STATIC_DEP);

    printf("OPTIONAL_DEP: %i\n", OPTIONAL_DEP);
    printf("REQUIRED_DEP: %i\n\n", REQUIRED_DEP);

    Module* apiModule = initLibraryApi();
    Module* apiTestsModule = initLibraryApiTests(apiModule);
    DependencyDictElement* i;
    for (i = apiTestsModule->dependencyDict->dependencyDictBottom;
        i != apiTestsModule->dependencyDict->dependencyDictTop;
        i = i->nextElement) {
        assert(i->versionComparator->apply(i->version, i->dependency->version) == VERSION_MATCH);
    }

    printf("LitLaunch API Module: %s", moduleToString(apiModule));
    printf("LitLaunch API Tests Module: %s", moduleToString(apiTestsModule));

    freeLibraryApiTests(apiTestsModule);
    freeLitLaunchLibraryApi(apiModule);
    return 0;
}
