//
//  kern_start.cpp
//  FreeCOM1
//
//  Copyright © 2022 flagers. All rights reserved.
//

// Lilu headers
#include <Headers/plugin_start.hpp>
#include <Headers/kern_api.hpp>

#include "kern_fcom1.hpp"

static FCOM1 fcom1;

#pragma mark - Plugin start
static void pluginStart() {
    int kernelDebugArg = 0;
    DBGLOG(MODULE_SHORT, "start");
    PE_parse_boot_argn("debug", &kernelDebugArg, sizeof(kernelDebugArg));
    if ((kernelDebugArg & 8) != 0) {
        fcom1.init();
    } else {
        SYSLOG(MODULE_SHORT, "DB_KPRT not in kernel debug mask; nothing to do.");
    }
};

// Boot args.
static const char *bootargOff[] {
    "-fcom1off"
};
static const char *bootargDebug[] {
    "-fcom1dbg"
};
static const char *bootargBeta[] {
    "-fcom1beta"
};

// Plugin configuration.
PluginConfiguration ADDPR(config) {
    xStringify(PRODUCT_NAME),
    parseModuleVersion(xStringify(MODULE_VERSION)),
    LiluAPI::AllowNormal,
    bootargOff,
    arrsize(bootargOff),
    bootargDebug,
    arrsize(bootargDebug),
    bootargBeta,
    arrsize(bootargBeta),
    KernelVersion::SnowLeopard,
    KernelVersion::Ventura,
    pluginStart
};
