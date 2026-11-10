# build_msvc.ps1 - MSVC native build wrapper (nmake + cl).
# Usage: .\build_msvc.ps1 [nmake args]   e.g. .\build_msvc.ps1 clean
$ErrorActionPreference = 'Stop'
$here = Split-Path -Parent $PSCommandPath
Set-Location $here
nmake /NOLOGO /f Makefile.msc @args
$rc = $LASTEXITCODE
if ($rc -ne 0) {
    Write-Host "MSVC build FAILED (exit $rc)." -ForegroundColor Red
    exit $rc
}
Write-Host ''
Write-Host 'MSVC build succeeded.'
Write-Host "Target: $here\rar2hashcat.exe"