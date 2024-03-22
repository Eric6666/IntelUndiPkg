# IntelUndiPkg
Repository for Intel UNDI EFI Drivers

The files in the IntelUndiPkg folder were fetched from
https://www.intel.com/content/www/us/en/download/15755/intel-ethernet-connections-boot-utility-preboot-images-and-efi-drivers.html.

PREBOOT.zip was downloaded and files extracted from PREBOOT.exe.
Then, files were extracted from the following files in APPS\EFI\OPENSRC:

GigUndiDxe.zip
i40eUndiDxe.zip
IceUndiDxe.zip
XGigUndiDxe.zip

They were consolidated into the IntelUndiPkg folder.

edk2 was added as a submodule, checked out at tag edk2-stable202102.

The tools buildall.cmd, geninf.cmd and setup.cmd are used to build the
drivers for X64 and AARCH64 with VS2017 and generate .inf files that
can be used to integrate the drivers into firmware.

Users should run setup.cmd first to build the EDK2 BaseTools and
configure the environment, then run buildall.cmd to build all of the
drivers for AARCH64 and X64 for RELEASE, DEBUG and NOOPT (except the ICE
driver which fails to build in the NOOPT configuration).
The resulting binaries and .inf files will be located in the
IntelUndiBin folder.