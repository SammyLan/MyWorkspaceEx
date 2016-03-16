@echo off
@set CUR_DIR=%~dp0
@set path=%CUR_DIR%;D:\Program Files (x86)\Windows Kits\8.0\Debuggers\x86\srcsrv;D:\Program Files (x86)\Windows Kits\8.0\Debuggers\x86;%path%

@cd ..
@cd Bin
call "d:\Program Files (x86)\Microsoft Visual Studio 8\VC\vcvarsall.bat" x86
@cmd