@echo off

set "make_cmd=make -f makefile 1>&2"

if /i "%~1" == "rebuild" (
    %make_cmd% clean
)
%make_cmd%

if errorlevel 1 1>&2 (
    echo;
    set /p "=Unable to build target executable :^(" 0<nul
    pause 1>nul
    exit /b 1
)
for %%e in ("*.exe") do start "" /b "%%~e" 1>&2

exit /b 0
