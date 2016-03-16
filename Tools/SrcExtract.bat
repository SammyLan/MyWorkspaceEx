@setlocal enabledelayedexpansion
@echo off
@set ROOT_DIR=%~dp0
@set ENV_FILE=%ROOT_DIR%PDBCheck.ini

@for /F "tokens=1,2* delims==" %%i in (%ENV_FILE%) do (
     @set VAR=%%i
     @set VAL=%%j
     @set !VAR!=!VAL!
)

@cd %HRTXPDB%
@for /R %%s in (*.pdb) do ( 
	@srctool -x -d:%HRTXSRC% %%s
) 

@cd %HRTXPDB% 

