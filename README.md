FreeCOM1
================

[![Build Status](https://github.com/flagersgit/FreeCOM1/workflows/CI/badge.svg?branch=master)](https://github.com/flagersgit/FreeCOM1/actions)

[Lilu](https://github.com/acidanthera/Lilu) Kernel extension for enabling userspace access to COM ports not reserved for kernel printf when DB_KPRT is enabled.

#### Usage

* Set `KPRT ACPI Device` key in `Info.plist` to ACPI device name of serial port reserved for kernel printf.
  * Set to Hyper-V example (`UAR1`) by default. 
* `debug` boot argument must have DB_KPRT enabled.
* Only ACPI serial ports are supported, PCI serial is not supported.
* If unknown issues arise, ensure `Misc -> Serial` is set properly in OpenCore.

#### Boot arguments

- `-fcom1off` (or `-liluoff`) to disable
- `-fcom1dbg` (or `-liludbgall`) to enable verbose logging (in DEBUG builds)
- `-fcom1beta` (or `-lilubetaall`) to enable on macOS newer than 13

### Credits

- [Apple](https://www.apple.com) for macOS
- [Flagers](https://github.com/flagersgit) for this kernel extension
- [vit9696](https://github.com/vit9696) for [Lilu.kext](https://github.com/acidanthera/Lilu)
