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
  
//  OSDictionary *fcom2Matching = IOService::serviceMatching("FreeCOM2");
//  if (!fcom2Matching) {
//    SYSLOG(MODULE_SHORT, "Failed to create FreeCOM2 matching dictionary");
//    return nullptr;
//  }
//
//  DBGLOG(MODULE_SHORT, "Waiting for FreeCOM2");
//  IOService *fcom2Service = IOService::waitForMatchingService(fcom2Matching);
//  fcom2Matching->release();
//
//  if (!fcom2Service) {
//    SYSLOG(MODULE_SHORT, "Failed to locate FreeCOM2");
//    return nullptr;
//  }
  
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
/*
  bool                  isCom1 = false;
  OSArray              *provDevMemArray = nullptr;
  OSCollectionIterator *iterator = nullptr;
  OSCollectionIterator *iterator2 = nullptr;
  OSObject             *devMemArr2 = nullptr;
  IODeviceMemory       *devMemArr2Casted = nullptr;
  OSDictionary         *devMemDict = nullptr;
  OSNumber             *addr = nullptr;
  
  provider->setProperty("KillCOM1WasHere", kOSBooleanTrue);
  if (NULL == (provDevMemArray = OSDynamicCast(OSArray, provider->getProperty(gIODeviceMemoryKey)))) {
    return nullptr;
  }
  if (NULL == (iterator = OSCollectionIterator::withCollection(provDevMemArray))) {
    return nullptr;
  }
  while (NULL != (devMemArr2 = iterator->getNextObject())) {
    
    if (NULL == (devMemArr2Casted = OSDynamicCast(IODeviceMemory, devMemArr2))) {
      continue;
    }
    if (devMemArr2Casted->getPhysicalAddress() == COM1_PORT_ADDR) {
      isCom1 = true;
      break;
    }
//    if (NULL == (iterator2 = OSCollectionIterator::withCollection(devMemArr2Casted))) {
//      continue;
//    }
//    devMemDict = OSDynamicCast(OSDictionary, iterator2->getNextObject());
//    if (NULL == (addr = OSDynamicCast(OSNumber, devMemDict->getObject("address")))) {
//      continue;
//    }
//    if (addr->unsigned16BitValue() == COM1_PORT_ADDR) {
//      isCom1 = true;
//      break;
//    }
  }
  
  OSSafeReleaseNULL(iterator);
  OSSafeReleaseNULL(iterator2);
  if (isCom1) {
    return this;
  }
  return nullptr;
*/
}
