
echo off
:Location of swig.exe
set SWIG_EXE_PATH=C:\Program Files\swigwin-1.3.40\swig.exe

:Location of the swig interface file
set INTERFACE_FILE_PATH=C:\Users\Langkamp\Documents\Work\Kabala Engine G\KabalaEngine\Source\LuaBindings\KabalaEngine.i

:Location of the output file to generate
set OUTPUT_FILE_PATH=C:\Users\Langkamp\Documents\Work\Kabala Engine G\KabalaEngine\Source\LuaBindings\KELuaBindings.cpp

"%SWIG_EXE_PATH%" -c++ -lua -o "%OUTPUT_FILE_PATH%" "%INTERFACE_FILE_PATH%"

pause

