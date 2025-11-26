#!/usr/bin/env pwsh
# PowerShell build script for the library management program
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
Set-Location $scriptDir

$gcc = 'gcc'
if (-not (Get-Command $gcc -ErrorAction SilentlyContinue)) {
    Write-Error "gcc not found in PATH. Install MinGW/MSYS2 and ensure gcc is available."
    exit 1
}

$src = @('src\\main.c','src\\book.c')
$inc = '-Iinclude'
$flags = '-Wall -Wextra'
$out = 'library.exe'

& $gcc $flags $inc $src -o $out
if ($LASTEXITCODE -eq 0) { Write-Host "Built $out" } else { Write-Error "Build failed"; exit $LASTEXITCODE }
