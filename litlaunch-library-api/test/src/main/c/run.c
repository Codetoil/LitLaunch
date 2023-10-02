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

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "litlaunch/location.h"
#include "litlaunch/dependencies.h"
#include "litlaunch/litlaunch-library-api.h"

int main()
{
    printf("DYNAMIC_DEP: %i\n", DYNAMIC_DEP);
    printf("STATIC_DEP: %i\n\n", STATIC_DEP);

    printf("OPTIONAL_DEP: %i\n", OPTIONAL_DEP);
    printf("REQUIRED_DEP: %i\n\n", REQUIRED_DEP);

    Module* apiModule = initLibraryApi();

    printf("LitLaunch Library API Implementation:\n");
    printf("\tResource Location: %s\n", apiModule->id->_total);
    printf("\tVersion:\n");
    printf("\t\tResource Location: %s\n", apiModule->version->id->_total);
    printf("\t\tValue: %s\n", apiModule->version->versionValue);
    printf("\tDependency Dict:\n");
    printf("\t\tResource Location: %s\n", apiModule->dependencyDict->id->_total);
    printf("\t\tDependency Dict Entries:\n");
    printf("\n");
    
    freeResourceLocation(apiModule->version->id);
    freeVersion(apiModule->version);
    freeResourceLocation(apiModule->dependencyDict->id);
    freeDependencyDict(apiModule->dependencyDict);
    freeResourceLocation(apiModule->id);
    freeModule(apiModule);
    return 0;
}
