#include <iostream>
#include "../header/forward_list.hpp"
int main(){
    //initializer list
    forward_lists<int>lst = {1,2,3};
    lst.print_all(lst.begin(),lst.end());
    //memanggil default constructor    
    forward_lists<int>fl;
    fl.push_front(1);
    fl.push_front(2);
    fl.push_front(3);
    std::cout << std::endl;
    //=========== Menggunakan deferencing==============
    for(auto it = fl.begin(); it != fl.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    //================ Tanpa deferencing ===============
    for(auto it = fl.begin();it != fl.end();++it){
        std::cout << it << " ";
    }
    std::cout << std::endl;
    //================insert_after=======================
    fl.insert_after(fl.begin(),3,4);
    std::cout << "Proses insert_after 1" << std::endl;
    fl.print_all(fl.begin(),fl.end());
    std::cin.get();
    return 0;
}   