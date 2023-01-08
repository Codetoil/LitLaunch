/*
 * Copyright (c) Codetoil 2019-2023
 * Contact me on Discord: @Codetoil#7253, or by Email: ianthisawesomee@gmail.com
 */

package io.github.codetoil.litlaunch.api;

public interface ILogger extends IComponent {
    void debug(Object obj);

    void info(Object obj);

    void warn(Object obj);

    void error(Object obj);

    void fatal(Object obj);

    void trace(Object obj);

    /**
     * Only prints if the "verbose" flag is enabled
     */
    void verbose(Object obj);

    Object getInternalLogger();

    void setInternalLogger(Object logger);
}
