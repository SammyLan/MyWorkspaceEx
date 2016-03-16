@set WINDBGDIR=D:\Program Files (x86)\Windows Kits\8.0\Debuggers\x86

@set PDB_DIR=%1\
@set PDB_Server=%2
@echo PDB_DIR=%PDB_DIR%
@echo PDB_Server=%PDB_Server%

@set symstorecmd="%WINDBGDIR%\symstore.exe"
@set path=%WINDBGDIR%;%path%
symstore.exe add /f "%PDB_DIR%*.*" /s "%PDB_Server%" /t "MyPDBTest Project" /v "Build 1" /c "Dailybuild"