//
//  KillCOM1.hpp
//  FreeCOM1
//
//  Created by flagers on 9/25/22.
//  Copyright © 2022 flagers. All rights reserved.
//

#ifndef KillCOM1_hpp
#define KillCOM1_hpp

#include <IOKit/IOService.h>

enum {
  COM1_PORT_ADDR = 0x3f8,
  COM2_PORT_ADDR = 0x2f8,
  COM3_PORT_ADDR = 0x3e8,
  COM4_PORT_ADDR = 0x2e8
};

class KillCOM1 : public IOService {
  OSDeclareDefaultStructors(KillCOM1);
  typedef IOService super;
  
public:
  //
  // IOService overrides.
  //
  IOService* probe(IOService *provider, SInt32 *score) APPLE_KEXT_OVERRIDE;
};

#endif /* KillCOM1_hpp */
