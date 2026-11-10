@echo off
setlocal
nmake /NOLOGO /f Makefile.msc %*
set rc=%ERRORLEVEL%
if not %rc% equ 0 (
    echo MSVC build FAILED ^(exit %rc%^)
    endlocal
    exit /b %rc%
)
echo.
echo MSVC build succeeded.
echo Target: %~dp0rar2hashcat.exe
endlocal
