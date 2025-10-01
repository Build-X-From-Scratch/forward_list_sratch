# Forward List(Standar Template Library)
<p align="center">
  <img src="https://img.shields.io/badge/C++-20-blue.svg" alt="C++" width="120" height="40"/>
  <img src="https://img.shields.io/badge/build-passing-brightgreen" alt="Build" width="150" height="40"/>
  <img src="https://img.shields.io/badge/license-MIT-orange" alt="License" width="120" height="40"/>
</p>

## Introductions
This project is a custom implementation of the C++ Standard Template Library (STL) **forward_list**.  
The goal is to understand how the STL container works internally by building it from scratch,  
including various member functions, iterators, and algorithms such as sort, merge, and reverse.

## Project Structure
```cpp
.
├── build_failed.sh        // Script for simulating failed build
├── build_testing.sh       // Script for running unit tests
├── CMakeLists.txt         // CMake configuration
├── compile.sh             // Compile main implementation
├── compile_sort.sh        // Compile sorting-related code
├── CONTRIBUTING.md        // Contribution guidelines
├── header/                // Header files
│   └── forward_list.hpp   // Forward list template implementation
├── implementation/        // Implementation details
│   ├── implementation.cpp
│   └── implementation_sort.cpp
├── LICENSE                // License file (MIT)
├── src/                   // Source code prototypes
│   ├── forward_list.cpp
│   ├── merge_list.cpp
│   └── merge_sort.cpp
├── test/                  // Unit tests
│   └── testing.cpp
└── README.md              // Project documentation
```
## Requirements
- **Compiler**: g++ 10+/clang++ 12+
- **OS**: Linux(recomended),MacOS,Mikocok
## Instalation
Clone this repo
```bash
git clone https://github.com/Build-X-From-Scratch/forward_list_sratch.git
```
### copy header to your project
```bash
cp -r forward_list_sratch/header/forward_list.hpp .
```

## example 
```cpp
#include <iostream>
#include <vector>
#include "../header/forward_list.hpp" //->this header
int main(){
    std::cout << "Testing" << std::endl;
    forward_lists<int>flst = {1,2,3};
    flst.pop_front();
    flst.pop_front();
    flst.print_all(flst.begin(),flst.end()); //3
    return 0;
}   
```
## Compile
if you use g++ then:
```bash
g++ -stdc=c++20 example.cpp -o example
./example
```
if you use clang then:

```bash
clang++ -stdc=c++20 example -o example
./example
```
## 📌 TODO (Next Features)

| Feature        | Status |
|----------------|--------|
| insert_after   | ✅ Done |
| erase_after    | ✅ Done |
| push_front     | ✅ Todo |
| pop_front      | ✅ Todo |
| reverse        | ✅ Todo |
| unique         | ⬜ Todo |
| Unit Testing   | ✅ Todo |
| Sort           | ✅ Todo |
| Swap           | ✅ Todo |
| emplace_back   | ⬜ Todo |
| emplace_front  | ⬜ Todo |
| Assign         | ✅ Todo |
| Merge          | ✅ Todo |

## License
This project is licensed under the [MIT License](./LICENSE).  
You are free to use, modify, and distribute it with proper attribution.