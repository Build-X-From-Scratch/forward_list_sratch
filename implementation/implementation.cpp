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
    for(auto it = fl.begin(); it != fl.end(); ++it) {
        std::cout << *it << " " << std::endl;
    }
    std::cin.get();
    return 0;
}   