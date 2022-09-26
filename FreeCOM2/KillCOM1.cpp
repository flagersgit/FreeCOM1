//
//  KillCOM1.cpp
//  FreeCOM2
//
//  Created by flagers on 9/25/22.
//  Copyright © 2022 flagers. All rights reserved.
//

#include "KillCOM1.hpp"
#include "kern_fcom2.hpp"

OSDefineMetaClassAndStructors(KillCOM1, super);

IOService* KillCOM1::probe(IOService *provider, SInt32 *score) {
  provider->setProperty("KillCOM1WasHere", kOSBooleanTrue);
  int kernelDebugArg = 0;
  PE_parse_boot_argn("debug", &kernelDebugArg, sizeof(kernelDebugArg));
  if (!((kernelDebugArg & 8) != 0)) {
    return nullptr;
  }
  const OSSymbol *providerName = provider->copyName(gIOServicePlane);
  
  OSString *kprtDeviceName = OSDynamicCast(OSString, getProperty("KPRT ACPI Device"));
  if (!kprtDeviceName) {
    SYSLOG(MODULE_SHORT, "Failed to get 'KPRT ACPI Device' property, or not an OSString");
    return nullptr;
  }
  
  if (providerName->isEqualTo(kprtDeviceName)) {
    OSSafeReleaseNULL(providerName);
    return this;
  }
  return nullptr;
}
