cd .\build\
cmake -DCMAKE_BUILD_TYPE=Debug ..
ninja

cd ..\test\libs\sysma\
del *sysma* *database*

cd ..\..\..\bin\
copy * ..\test\libs\sysma\