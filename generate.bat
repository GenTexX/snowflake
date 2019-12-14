call vendor\premake\premake5.exe vs2019
if not exist "bin\" mkdir bin\Debug-x86_64\sandbox\
copy vendor\SDL\lib\SDL2.dll bin\Debug-x86_64\sandbox