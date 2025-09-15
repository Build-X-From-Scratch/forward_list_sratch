#include <gtest/gtest.h>
#include <vector>
#include "../header/forward_list.hpp"
//TEST(suite name,TestName)
TEST(Basic_stl,check_empty){
    forward_lists<int>fl;
    EXPECT_EQ(fl.get_size(), 0);
    EXPECT_TRUE(fl.is_empty());
}

TEST(Basic_stl,check_front){
    forward_lists<int>fl = {1};
    EXPECT_EQ(fl.front(), 1);
    EXPECT_FALSE(fl.is_empty());
}
TEST(Constructor_testing,initializer_constructor_test){
    forward_lists<int>fl = {1,2,3};
    std::vector<int>ex = {1,2,3};
    std::vector<int>actual;
    for(auto it = fl.begin();it != fl.end();++it){
        actual.push_back(*it);
    }
    EXPECT_EQ(actual, ex);
    EXPECT_FALSE(fl.is_empty());
    EXPECT_EQ(fl.get_size(), 3);
}
TEST(Constructor_testing,basic_constructor_test){
    forward_lists<int>fl;
    fl.push_front(1);
    std::vector<int>actual;
    std::vector<int>ex = {1};
    for(auto it = fl.begin();it != fl.end();++it){
        actual.push_back(*it);
    }
    EXPECT_EQ(actual, ex);
    EXPECT_FALSE(fl.is_empty());
    EXPECT_EQ(fl.get_size(), 1);
}