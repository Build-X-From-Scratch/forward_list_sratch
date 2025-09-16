#include <iostream>
#include <vector>
#include "../header/forward_list.hpp"
int main(){
    //initializer list
    std::cout << "initializer list constructor" << std::endl;
    forward_lists<int>lst = {1,2,3};
    lst.print_all(lst.begin(),lst.end());
    std::cout << "ini front: " << lst.front() << std::endl; 
    //memanggil default constructor    
    std::cout << "list FL" << std::endl;
    forward_lists<int>fl;   
    fl.push_front(1);
    fl.push_front(2);
    fl.push_front(3);
    std::cout << std::endl;
    //=========== Menggunakan deferencing==============
    for(auto it = fl.begin(); it != fl.end(); ++it) {
        std::cout << *it << " ";// 3 2 1  
    }
    std::cout << std::endl;
    //================ Tanpa deferencing ===============
    for(auto it = fl.begin();it != fl.end();++it){
        std::cout << it << " ";
    }
    std::cout << std::endl;
    //================insert_after 1=======================
    int x = 2;
    fl.insert_after(fl.before_begin(),x);
    std::cout << "Proses insert_after 1" << std::endl;
    fl.print_all(fl.begin(),fl.end());
    //================insert after 2======================== 
    forward_lists<int>fl1 = {1,2,3};
    std::cout << "insert after 2" << std::endl;
    fl1.insert_after(fl1.begin(),3,10);
    fl1.print_all(fl1.begin(),fl1.end()); //1 10 10 10 2 3
    //===============insert after 3=================================
    std::vector<int>v = {10,20,30};
    std::cout << "insert after 3" << std::endl;
    forward_lists<int>fl2 = {5,6,7};
    fl2.insert_after(fl2.begin(),v.begin(),v.end());
    fl2.print_all(fl2.begin(),fl2.end());
    //===============insert after 4=================================
    forward_lists<int>fl3 = {8,9,10};
    forward_lists<int>fwl = {50,60,40};
    fl3.insert_after(fl3.begin(),fwl.begin(),fwl.end());
    fl3.print_all(fl3.begin(), fl3.end()); //8 50 60 40 9 10
    //===============Proses Erasing===================================
    std::cout << "Pop Front" << std::endl;
    forward_lists<int>flst = {1,2,3};
    flst.print_all(flst.begin(),flst.end()); //2 3
    //std::cin.get();
    return 0;
}   