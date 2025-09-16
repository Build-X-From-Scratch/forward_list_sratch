# Guide for Build Unit testing
```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build -V
```
or for simple build you can use this
```bash
./build/testing.cpp
```