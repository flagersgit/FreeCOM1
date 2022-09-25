//
//  kern_fcom1.cpp
//  FreeCOM1
//
//  Created by flagers on 9/5/22.
//  Copyright © 2022 flagers. All rights reserved.
//

#include <Headers/kern_api.hpp>
#include <IOKit/IOService.h>
#include "kern_fcom1.hpp"

static FCOM1 *callbackFCOM1 = nullptr;

void FCOM1::init() {
  callbackFCOM1 = this;
  
  lilu.onKextLoadForce(kextList, arrsize(kextList),
  [](void *user, KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size) {
    callbackFCOM1->processKext(patcher, index, address, size);
  }, this);
}

void FCOM1::deinit() {
    
}

void FCOM1::processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size) {
  if (index == kextList[0].loadIndex) {
    KernelPatcher::LookupPatch patch {
      &kextList[0],
      reinterpret_cast<const uint8_t *>("debug"),
      reinterpret_cast<const uint8_t *>("ahaha"),
      sizeof("debug"), 1
    };

    patcher.applyLookupPatch(&patch);
    if (patcher.getError() != KernelPatcher::Error::NoError) {
      SYSLOG(MODULE_SHORT, "failed to apply 'debug' to 'ahaha' patch with error %d", patcher.getError());
      patcher.clearError();
    }
    KernelPatcher::RouteRequest request(_16X50ACPI_probe_symbol, _16X50ACPI_probe_handler, _16X50ACPI_probe_orig);
    if (!patcher.routeMultiple(index, &request, 1, address, size)) {
      SYSLOG(MODULE_SHORT, "patcher.routeMultiple for %s failed with error %d", request.symbol, patcher.getError());
      patcher.clearError();
    }
  }
}

/* static */
IOService* FCOM1::_16X50ACPI_probe_handler(IOService *that, IOService *provider, SInt32 *score) {
  const OSSymbol *providerName = provider->copyName();
  
  OSDictionary *fcom1Matching = IOService::serviceMatching("FreeCOM1");
  if (!fcom1Matching) {
    SYSLOG(MODULE_SHORT, "Failed to create FreeCOM1 matching dictionary");
    return nullptr;
  }
  
  DBGLOG(MODULE_SHORT, "Waiting for FreeCOM1");
  IOService *fcom1Service = IOService::waitForMatchingService(fcom1Matching);
  fcom1Matching->release();
  
  if (!fcom1Service) {
    SYSLOG(MODULE_SHORT, "Failed to locate FreeCOM1");
    return nullptr;
  }
  
  OSString *kprtDeviceName = OSDynamicCast(OSString, fcom1Service->getProperty("KPRT ACPI Device"));
  if (!kprtDeviceName) {
    SYSLOG(MODULE_SHORT, "Failed to get 'KPRT ACPI Device' property, or not an OSString");
    return nullptr;
  }
  
  if (providerName->isEqualTo(kprtDeviceName)) {
    OSSafeReleaseNULL(providerName);
    return nullptr;
  }
  
  return FunctionCast(_16X50ACPI_probe_handler, callbackFCOM1->_16X50ACPI_probe_orig)(that, provider, score);
}
