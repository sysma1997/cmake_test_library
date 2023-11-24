cd ./build/

cmake -DCMAKE_BUILD_TYPE=Debug ..
ninja

cd ../bin/

.\test.exe