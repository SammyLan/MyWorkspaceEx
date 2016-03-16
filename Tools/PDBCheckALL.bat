@set EXE_DIR=%~dp0EXE
@FOR /R %EXE_DIR% %%i IN (*.exe) DO @(
	@echo %%i
	@call PDBCheck.bat %%i
)
@cmd