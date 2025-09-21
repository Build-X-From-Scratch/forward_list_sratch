build(){
    cmake -S . -B build
    cmake --build build -j
    ctest --test-dir build --timeout 5 -V
}
build