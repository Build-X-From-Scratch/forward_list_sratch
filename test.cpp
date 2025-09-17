#include <bits/stdc++.h>
void sliding_window(){
    std::vector<int>nums = {1,4,6,3,9};
    int target = 18;
    int n = 3;
    int sum = 0;
    for(int i = 0;i < n;i++){
        sum += nums[i];
    }
    int window = sum;
    if(window == target){
        std::cout << "Target ditemukan" << std::endl;
    }else{
        bool checked = false;
        for(size_t i = n;i < nums.size();i++){
            window += nums[i] + nums[i - n];
            if(window == target){
                checked = true;
                break;
            }
        }
        if(checked == false){
            std::cout << "Target tidak ditemukan" << std::endl;
        }else{
            std::cout << "Target ditemukan" << std::endl;

        }
    }
}
int main(){
    std::forward_list<int>sl;
    std::cout << sl.max_size() << std::endl;
    std::cin.get();
    return 0;
}