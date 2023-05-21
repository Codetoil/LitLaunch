#pragma once

#ifndef _LITLAUNCH_SLIM_
#define LITLAUNCH_LIBRARY_API_VERSION "0.2.1"
#else
// 0x0000: 0.1.0+build.3
// 0x0001: 0.1.4+build.4
// 0x0002: 0.2.0
// 0x0003: 0.2.1
#define LITLAUNCH_LIBRARY_API_VERSION "0x0003"
// For now keep it a string.
#endif

#include "dependencies.h"

extern Module *initLibraryApi(void);