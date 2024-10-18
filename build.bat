REM Clear current session log 
cls
REM Source environment (Uncomment lines starting with "set" if you current env does not have these defined.)
set HFS=D:/SideFX/Houdini20.5.332
set AR_RESOLVER_NAME=perforceResolver
set AR_DCC_NAME=HOUDINI

rmdir /S /Q build
rmdir /S /Q dist

cmake . -B build -G "Visual Studio 17 2022" -A x64 -T v143
cmake --build build  --clean-first --config Release
cmake --install build