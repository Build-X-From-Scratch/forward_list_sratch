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
TEST(Basic_stl,pop_element){
    forward_lists<int>fl = {1,2,3,4,5};
    fl.pop_front();
    std::vector<int>actual;
    std::vector<int>expectation = {2,3,4,5};
    for(auto x: fl){
        actual.push_back(x);
    }
    EXPECT_TRUE(!fl.is_empty());
    EXPECT_EQ(fl.get_size(),3);
    EXPECT_EQ(actual, expectation);
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
TEST(Insert_testing,push_testing){
    forward_lists<int>fl;
    fl.push_front(1);
    fl.push_front(2);
    fl.push_front(3);
    std::vector<int>ex = {3,2,1};
    std::vector<int>actual;
    for(auto x: fl){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,ex);
    EXPECT_FALSE(fl.is_empty());
    EXPECT_EQ(fl.get_size(), 3);
}
TEST(Insert_testing, push_lvalue_testing){
    forward_lists<int>fl;
    int x,y,z;
    x = 10;
    y = 20;
    z = 30;
    fl.push_front(x);
    fl.push_front(y);
    fl.push_front(z);
    std::vector<int>actual;
    std::vector<int>ex = {30,20,10};
    for(auto x: fl){
        actual.push_back(x);
    }
    EXPECT_EQ(actual, ex);
    EXPECT_FALSE(fl.is_empty());
    EXPECT_EQ(fl.get_size(), 3);
}