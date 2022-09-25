//
//  kern_fcom1.hpp
//  FreeCOM1
//
//  Created by flagers on 9/5/22.
//  Copyright © 2022 flagers. All rights reserved.
//

#ifndef kern_fcom1_hpp
#define kern_fcom1_hpp

#define MODULE_SHORT "fcom1"

#include <IOKit/IOService.h>
#include <Headers/kern_patcher.hpp>

static const char *kext16X50ACPI[] { "/System/Library/Extensions/Apple16X50Serial.kext/Contents/PlugIns/Apple16X50ACPI.kext/Contents/MacOS/Apple16X50ACPI" };
static KernelPatcher::KextInfo kextList[] {
  {"com.apple.driver.Apple16X50ACPI", kext16X50ACPI, arrsize(kext16X50ACPI), {true}, {}, KernelPatcher::KextInfo::Unloaded },
};

static const char *_16X50ACPI_probe_symbol { "__ZN26com_apple_driver_16X50ACPI5probeEP9IOServicePi" };

class FCOM1 {
public:
  void init();
  void deinit();
    
private:
  void processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t addres, size_t size);
    
  // argument 'that' is actually the driver IOKit class, but we
  // ...don't care about those interfaces, so just use IOService.
  static IOService* _16X50ACPI_probe_handler(IOService *that, IOService *provider, SInt32 *score);
    
  mach_vm_address_t _16X50ACPI_probe_orig {0};
};


#endif /* kern_fcom1_hpp */
