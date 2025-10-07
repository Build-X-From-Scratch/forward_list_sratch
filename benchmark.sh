build(){
    cmake -S . -B build
    cmake --build build
    ./build/forward_list_bench
}
build