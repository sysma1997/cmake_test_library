cd ./build/

cmake -DCMAKE_BUILD_TYPE=Debug ..
ninja -v

cd ../bin/

.\test.exe