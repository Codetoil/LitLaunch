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

package io.github.codetoil.litlaunch.api;

/**
 * Components are important elements of a piece of software that a plugin uses to interface between
 * a piece of software and libraries.
 * For example, for the LitLaunch Minecraft ModLoader, a plugin would be a mod, the software would be
 * Minecraft, a library would be the plugin containing information about blocks, and the component would
 * be an Object representing that block.
 */
public class Component
{
    public native String getName();
    public native LitLaunchLibrary getLibrary();

    
}
