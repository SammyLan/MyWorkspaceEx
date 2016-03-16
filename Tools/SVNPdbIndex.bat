@rem setlocal enabledelayedexpansion
@echo off
@set SVNDIR=D:\Program Files\TortoiseSVN\bin
@set WINDBGDIR=D:\Program Files (x86)\Windows Kits\8.0\Debuggers\x86\srcsrv
@set PERLDIR=D:\Perl\bin

@set svnindexcmd="%WINDBGDIR%\svnindex.cmd"
@set path=%SVNDIR%;%WINDBGDIR%;%PERLDIR%;%path%

@set HRTX_SRC_Rooot=%1
@set HRTX_CUR_DIR=%~dp0
@set DATA_INI=%HRTX_CUR_DIR%data.ini

@echo HRTX_SRC_Rooot=%HRTX_SRC_Rooot%
@echo HRTX_CUR_DIR=%HRTX_CUR_DIR%
@cd %HRTX_CUR_DIR%

@for /F "tokens=1,2* delims=:" %%i in (%DATA_INI%) do (
    @if "%%j" == "Plugin" (
		@echo ��ʼ������Ŀ¼:%HRTX_SRC_Rooot%%%i
		@for /f "delims=" %%c in ('dir /ad/b "%HRTX_SRC_Rooot%%%i"') do (
			@echo  ��ʼ��������Ŀ¼:%HRTX_SRC_Rooot%%%i\%%c\bin
			@if exist %HRTX_SRC_Rooot%%%i\%%c\bin call %svnindexcmd% /source="%HRTX_SRC_Rooot%" /symbols="%HRTX_SRC_Rooot%%%i\%%c\bin" /debug
			@echo  ��������Ŀ¼����:%HRTX_SRC_Rooot%%%i\%%c\bin	
		)
		@echo ������Ŀ¼����:%HRTX_SRC_Rooot%%%i 
	)else (
		@echo ��ʼ����Ŀ¼:%HRTX_SRC_Rooot%%%i
		@if exist %HRTX_SRC_Rooot%%%i call %svnindexcmd% /source="%HRTX_SRC_Rooot%" /symbols="%HRTX_SRC_Rooot%%%i" /debug
		@echo ����Ŀ¼����:%HRTX_SRC_Rooot%%%i
	)
)
