set INFNAME=%1%
set DRVNAME=%2%
set BLDTYPE=%3%
set GUID=%4%

type header.txt                                            > IntelUndiBin\%INFNAME%
echo   BASE_NAME                      = %DRVNAME%         >> IntelUndiBin\%INFNAME%
echo   FILE_GUID                      = %GUID%            >> IntelUndiBin\%INFNAME%
echo   MODULE_TYPE                    = UEFI_DRIVER       >> IntelUndiBin\%INFNAME%
echo   VERSION_STRING                 = 1.0               >> IntelUndiBin\%INFNAME%
echo.                                                     >> IntelUndiBin\%INFNAME%
echo [Binaries.X64]                                       >> IntelUndiBin\%INFNAME%
echo   PE32^|IntelUndiBin/%BLDTYPE%/X64/%DRVNAME%.efi     >> IntelUndiBin\%INFNAME%
echo.                                                     >> IntelUndiBin\%INFNAME%
echo [Binaries.AARCH64]                                   >> IntelUndiBin\%INFNAME%
echo   PE32^|IntelUndiBin/%BLDTYPE%/AARCH64/%DRVNAME%.efi >> IntelUndiBin\%INFNAME%
