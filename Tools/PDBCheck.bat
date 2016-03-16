@setlocal enabledelayedexpansion
@echo *****************  Begin  ****************
@echo off
@set ROOT_DIR=%~dp0
@set ENV_FILE=%ROOT_DIR%PDBCheck.ini

@for /F "tokens=1,2* delims==" %%i in (%ENV_FILE%) do (
     @set VAR=%%i
     @set VAL=%%j
     @set !VAR!=!VAL!
)

@if not exist %HRTXLOG% mkdir %HRTXLOG%

@set HRTX_FILE=%1
@set HRTX_FILE_NAME=%~n1
@set HRTX_FILE_NAME_POSTFIX=_%~n1

@if "!NEED_EXTRACT!" == "NO" goto LABLE_CHECK

@if not exist %HRTX_FILE% do set HRTX_FILE=%ROOT_DIR%HRTX.exe
@if not exist %HRTX_FILE% goto FILE_NOT_FOUND


@rem 解压安装包
@if not exist %HRTXBIN%\ mkdir %HRTXBIN%\
@if not exist %HRTXPDB%\ mkdir %HRTXPDB%\
@set HRTXBIN=%HRTXBIN%\%HRTX_FILE_NAME%
@set HRTXPDB=%HRTXPDB%\%HRTX_FILE_NAME%
@set HRTXBIN_CHECK=%HRTXBIN%\program files\Tencent\QQEIM

@call 7z x %HRTX_FILE% -o%HRTXBIN% -r >%HRTXLOG%7z%HRTX_FILE_NAME_POSTFIX%.log

:LABLE_CHECK
@echo HRTX_FILE=%HRTX_FILE%
@echo HRTX_FILE_NAME=%HRTX_FILE_NAME%
@echo HRTXBIN=%HRTXBIN%
@echo HRTXPDB=%HRTXPDB%

@rem 检查并下载PDB
@if "!NEED_DOWNLOAD!" == "YES" call symchk /r "%HRTXBIN_CHECK%" /s "srv*%PDBSRV_Dailybuild%;%PDBSRV_3rd_Dowload%"  /ocx %HRTXPDB% >%HRTXLOG%pdb_symchk1%HRTX_FILE_NAME_POSTFIX%.log

@rem 检查PDB是否跟源码关联
@if "!NEED_QUERY!" == "YES" call symstore query /r /f %HRTXPDB% /s %PDBSRV_Dailybuild% >%HRTXLOG%pdb_query%HRTX_FILE_NAME_POSTFIX%.log

@rem 备份PDB,测试的同学可以忽略此步骤
@if "!NEED_BACKUP!" == "YES" call symstore.exe add /f "%HRTXPDB%\*.*" /s "%PDBSRV_FinalRelease%" /t "HRTX" /v "%HRTX_FILE%" /c "备份PDB" >%HRTXLOG%pdb_backup%HRTX_FILE_NAME_POSTFIX%.log

@rem 检查PDB是否备份成功
@if "!NEED_CHECK!" == "YES" call symchk /r "%HRTXBIN_CHECK%" /s "srv*%PDBSRV_FinalRelease%;%PDBSRV_3rd_Check%"  >%HRTXLOG%pdb_symchk2%HRTX_FILE_NAME_POSTFIX%.log


@goto END
:FILE_NOT_FOUND
@echo file %HRTX_FILE% is not found
:END

@echo *****************  End  ****************
@if "!NEED_PAUSE!" == "YES" call cmd