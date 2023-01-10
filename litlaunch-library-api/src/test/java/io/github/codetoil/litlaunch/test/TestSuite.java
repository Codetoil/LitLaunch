/*
 * Copyright (C) 2019-2023 Codetoil
 * Contact me on Discord: @Codetoil#7253, or by Email: ianthisawesomee@gmail.com
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

package io.github.codetoil.litlaunch.test;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import io.github.codetoil.litlaunch.api.LitLaunchLibraryApi;
import io.github.codetoil.litlaunch.api.Software;

import static org.junit.jupiter.api.Assertions.assertEquals;

@DisplayName("Testing suite")
public class TestSuite {
    Software libraryApiSoftware = LitLaunchLibraryApi.initLibraryApi();

    @Test
    void checkName() {
        assertEquals("LitLaunch Library API", libraryApiSoftware.getName());
    }

    @Test
    void checkVersion() {
        assertEquals("0.1.0+build.2", libraryApiSoftware.getVersion());
    }
}
