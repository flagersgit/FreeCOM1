//
//  kern_fcom2.hpp
//  FreeCOM2
//
//  Created by flagers on 9/5/22.
//  Copyright © 2022 flagers. All rights reserved.
//

#ifndef kern_fcom2_hpp
#define kern_fcom2_hpp

#define MODULE_SHORT "fcom2"

#include <IOKit/IOService.h>
#include <Headers/kern_patcher.hpp>

static const char *kext16X50ACPI[] { "/System/Library/Extensions/Apple16X50Serial.kext/Contents/PlugIns/Apple16X50ACPI.kext/Contents/MacOS/Apple16X50ACPI" };
static KernelPatcher::KextInfo kextList[] {
  {"com.apple.driver.Apple16X50ACPI", kext16X50ACPI, arrsize(kext16X50ACPI), {true}, {}, KernelPatcher::KextInfo::Unloaded },
};

class FCOM2 {
public:
  void init();
  void deinit();
    
private:
  void processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t addres, size_t size);
};


#endif /* kern_fcom2_hpp */
