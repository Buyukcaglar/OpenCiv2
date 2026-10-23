@echo off
rem Play the portable build on Windows: tools\run-civ2.bat [GAMEDIR]
rem GAMEDIR: the installed game (default %%USERPROFILE%%\Civ2); the game saves there.
rem A maximized window with a Windows menu bar; set CIV2_FULLSCREEN=1 for full
rem screen, CIV2_CLASSIC=1 for menus and caption drawn as the original's (README).
setlocal
set "HERE=%~dp0.."
set "GAME=%~1"
if "%GAME%"=="" set "GAME=%USERPROFILE%\Civ2"
if not exist "%GAME%\civ2.exe" (echo no game in %GAME%: install Civilization II there or name its directory & exit /b 1)
if not exist "%GAME%\CIV2.DAT" copy "%HERE%\harness\CIV2.DAT" "%GAME%\" >nul
set "CIV2_DATA=%HERE%\data\native"
"%HERE%\build\civ2-port.exe" "%GAME%"
