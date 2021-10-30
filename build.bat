@ECHO OFF
ECHO You are about to commence the build, after the build, an executable 'apost.exe' will be created.
ECHO Make sure you have cmake and make installed.
ECHO.
PAUSE

ECHO.
ECHO Generating Makefile...
cmake . -G "MinGW Makefiles"

ECHO.
ECHO Building...
make

ECHO.
ECHO Build Done...

ECHO.
ECHO Cleaning Up...
del cmake_install.cmake
del CMakeCache.txt
del Makefile
RD /S /Q CMakeFiles
ECHO Done.