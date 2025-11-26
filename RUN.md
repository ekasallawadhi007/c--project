PowerShell build and run instructions

From PowerShell, change to the project folder and run the build script:

```powershell
cd path\to\library_management_project\library_management_project
.\build.ps1
.\library.exe
```

Or, if you have GNU Make available (MSYS2/MinGW):

```powershell
cd path\to\library_management_project\library_management_project
make
.\library.exe
```

Set-Location -LiteralPath 'C:\Users\ekas\Documents\library_management_project[1]\library_management_project' ; .\library.exe

Notes:
- The build script requires `gcc` in your PATH (MinGW / MSYS2).
- The Makefile will also build `library.exe` when `make` is available.
