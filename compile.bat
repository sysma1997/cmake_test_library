cd .\build\
cmake -DCMAKE_BUILD_TYPE=Debug ..
ninja

cd ..\test\libs\sysma\
del /S *

cd ..\..\..\bin\
Xcopy * ..\test\libs\sysma\ /E /H /C /I