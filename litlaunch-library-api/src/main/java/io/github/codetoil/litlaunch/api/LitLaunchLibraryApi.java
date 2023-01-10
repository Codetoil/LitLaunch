package io.github.codetoil.litlaunch.api;

public class LitLaunchLibraryApi {
    public static native Software createSoftwareStruct(String name, String version);
    public static native LitLaunchLibrary createLibraryStruct(String name, String version);
    public static native LitLaunchPlugin createPluginStruct(String name, String version, LitLaunchLibrary requiredLibrary);
    public static native Component createComponent(String name, LitLaunchLibrary componentLibrary);
    public static native Software initLibraryApi();
}
