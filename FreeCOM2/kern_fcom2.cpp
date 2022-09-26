//
//  kern_fcom2.cpp
//  FreeCOM2
//
//  Created by flagers on 9/5/22.
//  Copyright © 2022 flagers. All rights reserved.
//

#include <Headers/kern_api.hpp>
#include <IOKit/IOService.h>
#include "kern_fcom2.hpp"
#include <IOKit/acpi/IOACPITypes.h>

static FCOM2 *callbackFCOM2 = nullptr;

void FCOM2::init() {
  callbackFCOM2 = this;
  
  lilu.onKextLoadForce(kextList, arrsize(kextList),
  [](void *user, KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size) {
    callbackFCOM2->processKext(patcher, index, address, size);
  }, this);
}

void FCOM2::deinit() {
    
}

void FCOM2::processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size) {
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
  }
}
