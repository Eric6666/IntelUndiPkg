set WORKSPACE=%CD%
set PACKAGES_PATH=%CD%;%CD%\edk2

cmd /c build -p IntelUndiPkg\IntelGigUndiPkg.dsc -a X64 -t VS2017 -b NOOPT
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelGigUndiPkg.dsc -a X64 -t VS2017 -b RELEASE
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelGigUndiPkg.dsc -a X64 -t VS2017 -b DEBUG
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelGigUndiPkg.dsc -a AARCH64 -t VS2017 -b NOOPT
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelGigUndiPkg.dsc -a AARCH64 -t VS2017 -b RELEASE
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelGigUndiPkg.dsc -a AARCH64 -t VS2017 -b DEBUG
if %ERRORLEVEL% NEQ 0 exit /B 1

cmd /c build -p IntelUndiPkg\IntelXGigUndiPkg.dsc -a X64 -t VS2017 -b NOOPT
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelXGigUndiPkg.dsc -a X64 -t VS2017 -b RELEASE
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelXGigUndiPkg.dsc -a X64 -t VS2017 -b DEBUG
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelXGigUndiPkg.dsc -a AARCH64 -t VS2017 -b NOOPT
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelXGigUndiPkg.dsc -a AARCH64 -t VS2017 -b RELEASE
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelXGigUndiPkg.dsc -a AARCH64 -t VS2017 -b DEBUG
if %ERRORLEVEL% NEQ 0 exit /B 1

REM The ICE driver doesn't build in NOOPT configuration
REM cmd /c build -p IntelUndiPkg\IntelIceUndiPkg.dsc -a X64 -t VS2017 -b NOOPT
REM if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelIceUndiPkg.dsc -a X64 -t VS2017 -b RELEASE
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelIceUndiPkg.dsc -a X64 -t VS2017 -b DEBUG
if %ERRORLEVEL% NEQ 0 exit /B 1
REM The ICE driver doesn't build in NOOPT configuration
REM cmd /c build -p IntelUndiPkg\IntelIceUndiPkg.dsc -a AARCH64 -t VS2017 -b NOOPT
REM if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelIceUndiPkg.dsc -a AARCH64 -t VS2017 -b RELEASE
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelIceUndiPkg.dsc -a AARCH64 -t VS2017 -b DEBUG
if %ERRORLEVEL% NEQ 0 exit /B 1

cmd /c build -p IntelUndiPkg\IntelI40eUndiPkg.dsc -a X64 -t VS2017 -b NOOPT
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelI40eUndiPkg.dsc -a X64 -t VS2017 -b RELEASE
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelI40eUndiPkg.dsc -a X64 -t VS2017 -b DEBUG
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelI40eUndiPkg.dsc -a AARCH64 -t VS2017 -b NOOPT
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelI40eUndiPkg.dsc -a AARCH64 -t VS2017 -b RELEASE
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c build -p IntelUndiPkg\IntelI40eUndiPkg.dsc -a AARCH64 -t VS2017 -b DEBUG
if %ERRORLEVEL% NEQ 0 exit /B 1

mkdir IntelUndiBin\Noopt\X64
mkdir IntelUndiBin\Noopt\AARCH64
mkdir IntelUndiBin\Release\X64
mkdir IntelUndiBin\Release\AARCH64
mkdir IntelUndiBin\Debug\X64
mkdir IntelUndiBin\Debug\AARCH64

copy /Y Build\IntelUndiPkg\NOOPT_VS2017\X64\GigUndiDxe.efi IntelUndiBin\Noopt\X64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\RELEASE_VS2017\X64\GigUndiDxe.efi IntelUndiBin\Release\X64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\DEBUG_VS2017\X64\GigUndiDxe.efi IntelUndiBin\Debug\X64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\NOOPT_VS2017\AARCH64\GigUndiDxe.efi IntelUndiBin\Noopt\AARCH64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\RELEASE_VS2017\AARCH64\GigUndiDxe.efi IntelUndiBin\Release\AARCH64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\DEBUG_VS2017\AARCH64\GigUndiDxe.efi IntelUndiBin\Debug\AARCH64
if %ERRORLEVEL% NEQ 0 exit /B 1

copy /Y Build\IntelUndiPkg\NOOPT_VS2017\X64\XGigUndiDxe.efi IntelUndiBin\Noopt\X64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\RELEASE_VS2017\X64\XGigUndiDxe.efi IntelUndiBin\Release\X64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\DEBUG_VS2017\X64\XGigUndiDxe.efi IntelUndiBin\Debug\X64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\NOOPT_VS2017\AARCH64\XGigUndiDxe.efi IntelUndiBin\Noopt\AARCH64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\RELEASE_VS2017\AARCH64\XGigUndiDxe.efi IntelUndiBin\Release\AARCH64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\DEBUG_VS2017\AARCH64\XGigUndiDxe.efi IntelUndiBin\Debug\AARCH64
if %ERRORLEVEL% NEQ 0 exit /B 1

REM copy /Y Build\IntelUndiPkg\NOOPT_VS2017\X64\IceUndiDxe.efi IntelUndiBin\Noopt\X64
copy /Y Build\IntelUndiPkg\RELEASE_VS2017\X64\IceUndiDxe.efi IntelUndiBin\Release\X64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\DEBUG_VS2017\X64\IceUndiDxe.efi IntelUndiBin\Debug\X64
if %ERRORLEVEL% NEQ 0 exit /B 1
REM copy /Y Build\IntelUndiPkg\NOOPT_VS2017\AARCH64\IceUndiDxe.efi IntelUndiBin\Noopt\AARCH64
REM if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\RELEASE_VS2017\AARCH64\IceUndiDxe.efi IntelUndiBin\Release\AARCH64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\DEBUG_VS2017\AARCH64\IceUndiDxe.efi IntelUndiBin\Debug\AARCH64
if %ERRORLEVEL% NEQ 0 exit /B 1

if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\NOOPT_VS2017\X64\I40eUndiDxe.efi IntelUndiBin\Noopt\X64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\RELEASE_VS2017\X64\I40eUndiDxe.efi IntelUndiBin\Release\X64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\DEBUG_VS2017\X64\I40eUndiDxe.efi IntelUndiBin\Debug\X64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\NOOPT_VS2017\AARCH64\I40eUndiDxe.efi IntelUndiBin\Noopt\AARCH64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\RELEASE_VS2017\AARCH64\I40eUndiDxe.efi IntelUndiBin\Release\AARCH64
if %ERRORLEVEL% NEQ 0 exit /B 1
copy /Y Build\IntelUndiPkg\DEBUG_VS2017\AARCH64\I40eUndiDxe.efi IntelUndiBin\Debug\AARCH64
if %ERRORLEVEL% NEQ 0 exit /B 1

cmd /c geninf.cmd GigUndiBinNoopt.inf GigUndiDxe Noopt 9FDA5C19-CC3B-4EDC-9BC0-76F93476F9D3
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c geninf.cmd GigUndiBinRelease.inf GigUndiDxe Release FD261C5A-75EA-454E-A876-C0415C813118
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c geninf.cmd GigUndiBinDebug.inf GigUndiDxe Debug 5DEFAFFE-4EF9-42D6-87BB-E49B944BE05D
if %ERRORLEVEL% NEQ 0 exit /B 1

cmd /c geninf.cmd XGigUndiBinNoopt.inf XGigUndiDxe Noopt 4B50B14C-356B-4862-9733-E0F2EAB9F7B1
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c geninf.cmd XGigUndiBinRelease.inf XGigUndiDxe Release 8D548465-A29C-4E94-98A2-654DB7ECE5FD
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c geninf.cmd XGigUndiBinDebug.inf XGigUndiDxe Debug C996C280-F5B2-433D-9861-5B0F0877DF1F
if %ERRORLEVEL% NEQ 0 exit /B 1

REM geninf.cmd IceUndiBinNoopt.inf IceUndiDxe Noopt 09A8DC03-EC6D-490C-B2F7-877A605CE700
cmd /c geninf.cmd IceUndiBinRelease.inf IceUndiDxe Release C33D9B1A-51EF-4A3E-904F-79BA7605D17D
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c geninf.cmd IceUndiBinDebug.inf IceUndiDxe Debug 4D8C5367-1440-45A2-94DD-936D1C2B1B75
if %ERRORLEVEL% NEQ 0 exit /B 1

cmd /c geninf.cmd I40eUndiBinNoopt.inf I40eUndiDxe Noopt 259C91DF-34DA-4176-9A57-686E5FD1FD86
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c geninf.cmd I40eUndiBinRelease.inf I40eUndiDxe Release CB083590-6D7C-47CC-884D-CBD57DD1CC12
if %ERRORLEVEL% NEQ 0 exit /B 1
cmd /c geninf.cmd I40eUndiBinDebug.inf I40eUndiDxe Debug CB0D3951-307C-4194-A895-FE4122671303
if %ERRORLEVEL% NEQ 0 exit /B 1






