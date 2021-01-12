@echo off

make -f makefile.make 1>&2

if errorlevel 1 1>&2 (
    echo;
    set /p "=Unable to build target executable :(" 0<nul
    pause 1>nul
    exit /b 1
)
for %%e in ("*.exe") do start "" /b "%%~e" 1>&2

exit /b 0
