build(){
    cmake -S . -B build
    cmake --build build -j
    ctest --test-dir build -V
}
build