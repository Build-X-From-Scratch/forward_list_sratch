# Forward List(Standar Template Library)
<p align="center">
  <img src="https://img.shields.io/badge/C++-20-blue.svg" alt="C++" width="120" height="40"/>
  <img src="https://img.shields.io/badge/build-passing-brightgreen" alt="Build" width="150" height="40"/>
  <img src="https://img.shields.io/badge/license-MIT-orange" alt="License" width="120" height="40"/>
</p>

## Introductions
Maybe I Not Sure for this introduction,i am not smart for write this stupid Introduction,i just focus to get
best result
# Structure Directory
```cpp
.
├── build_failed.sh //shell scripting for build and testing
├── build_testing.sh
├── CMakeLists.txt
├── commitlint.config.js
├── compile_commands.json -> build/compile_commands.json
├── compile.sh
├── compile_sort.sh //
├── CONTRIBUTING.MD
├── header //header stl
│   └── forward_list.hpp
├── implementation //implementantian stl
│   ├── implementation.cpp
│   └── implementation_sort.cpp
├── LICENSE
├── package.json
├── package-lock.json
├── README.md
├── refactor.md
├── src //prototype implementasi method 
│   ├── forward_list.cpp
│   ├── merge_list.cpp
│   └── merge_sort.cpp
├── test //unit testing
│   └── testing.cpp
└── testing.md
```
## Requirements
- Compiler: g++ 10+/clang++ 12+
- OS: Linux(recomended),MacOS,Mikocok
## Instalation
Clone this repo
```bash
git clone https://github.com/Build-X-From-Scratch/forward_list_sratch.git
```
copy header to your project,if your in directory your project
```cpp
cp -r forward_list_sratch/header/forward_lists.hpp
```
if you not on directory project
```bash
cp -r forward_list_sratch/header/forward_lists.hpp your directory
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
https://github.com/Build-X-From-Scratch/forward_list_sratch/blob/main/LICENSE