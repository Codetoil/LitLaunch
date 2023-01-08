package io.github.codetoil.litlaunch.test;

import org.bridj.Pointer;

import io.github.codetoil.litlaunch.api.library_api.LitlaunchLibraryApiLibrary;
import io.github.codetoil.litlaunch.api.library_api.Software;

public class Test {
    public static void main(String[] args) {
        Pointer<Software> software = LitlaunchLibraryApiLibrary.initLibraryAPI();
    }
}
