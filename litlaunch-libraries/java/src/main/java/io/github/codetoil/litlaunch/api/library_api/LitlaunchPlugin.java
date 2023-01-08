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

package io.github.codetoil.litlaunch.api.library_api;
import org.bridj.BridJ;
import org.bridj.Pointer;
import org.bridj.StructObject;
import org.bridj.ann.Field;
import org.bridj.ann.Library;
/**
 * <i>native declaration : /workspaces/LitLaunch/litlaunch-library-api/src/main/c/litlaunch-library-api.h</i><br>
 * This file was autogenerated by <a href="http://jnaerator.googlecode.com/">JNAerator</a>,<br>
 * a tool written by <a href="http://ochafik.com/">Olivier Chafik</a> that <a href="http://code.google.com/p/jnaerator/wiki/CreditsAndLicense">uses a few opensource projects.</a>.<br>
 * For help, please visit <a href="http://nativelibs4java.googlecode.com/">NativeLibs4Java</a> or <a href="http://bridj.googlecode.com/">BridJ</a> .
 */
@Library("litlaunch-library-api") 
public class LitlaunchPlugin extends StructObject {
	static {
		BridJ.register();
	}
	@Field(0) 
	public int size() {
		return this.io.getIntField(this, 0);
	}
	@Field(0) 
	public LitlaunchPlugin size(int size) {
		this.io.setIntField(this, 0, size);
		return this;
	}
	/** C type : ISoftware* */
	@Field(1) 
	public Pointer<Software > info() {
		return this.io.getPointerField(this, 1);
	}
	/** C type : ISoftware* */
	@Field(1) 
	public LitlaunchPlugin info(Pointer<Software > info) {
		this.io.setPointerField(this, 1, info);
		return this;
	}
	/** C type : ILibrary* */
	@Field(2) 
	public Pointer<LitlaunchLibrary > requiredLibrary() {
		return this.io.getPointerField(this, 2);
	}
	/** C type : ILibrary* */
	@Field(2) 
	public LitlaunchPlugin requiredLibrary(Pointer<LitlaunchLibrary > requiredLibrary) {
		this.io.setPointerField(this, 2, requiredLibrary);
		return this;
	}
	public LitlaunchPlugin(String name, String version, LitlaunchLibrary library) {
		this(LitlaunchLibraryApiLibrary.createPluginStruct(
			Pointer.pointerToCString(name),
			Pointer.pointerToCString(version),
			Pointer.getPointer(library)));
	}
	public LitlaunchPlugin(Pointer<LitlaunchPlugin> pointer) {
		super(pointer);
	}
}
