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
    EXPECT_EQ(fl.get_size(),5);
    EXPECT_EQ(fl.front(), 1);
     fl.pop_front();
    std::vector<int>actual;
    std::vector<int>expectation = {2,3,4,5};
    for(auto x: fl){
        actual.push_back(x);
    }
    EXPECT_FALSE(fl.is_empty());
    EXPECT_EQ(fl.get_size(),4);
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
TEST(Constructor_testing, range_constructor){
    std::vector<int>cp = {1,2,3};
    forward_lists<int>fl(cp.begin(),cp.end());
    std::vector<int>expec;
    std::vector<int>actual = {1,2,3};
    for(auto x: fl){
        expec.push_back(x);
    }
    EXPECT_EQ(actual, expec);
    forward_lists<int>range = {1,2,3,};
    forward_lists<int>mv(range.begin(),range.end());
    std::vector<int>expectations;
    for(auto x: mv){
        expectations.push_back(x);
    }
    EXPECT_EQ(actual,expectations);
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
TEST(Constructor_testing,mv_constructor){
    forward_lists<int>fl = {1,2,3,4};
    int size_fl = fl.get_size();
    std::vector<int>exFl;
    for(auto x: fl){
        exFl.push_back(x);
    }
    forward_lists<int>flst = std::move(fl);
    int size_flst = flst.get_size();
    EXPECT_EQ(size_fl,size_flst);
    std::vector<int>exFlst;
    for(auto x: flst){
        exFlst.push_back(x);
    }
    EXPECT_EQ(exFl,exFlst);
}
TEST(Constructor_testing,mv_assgn_test){
    forward_lists<int>list;
    list = {1,2,3};
    int Ssize = list.get_size();
    forward_lists<int>cp;
    cp = std::move(list);
    std::vector<int>Slist;
    std::vector<int>Scp;
    for(auto x: list){
        Slist.push_back(x);
    }
    for(auto x: cp){
        Scp.push_back(x);
    }
    EXPECT_EQ(list.get_size(),0);
    EXPECT_EQ(cp.get_size(),3);
    EXPECT_EQ(cp.get_size(),Ssize);
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
TEST(Insert_testing,insert_afterII){
    forward_lists<int>fl = {1,2,3};
    std::vector<int>v = {10,20,30};
    fl.insert_after(fl.begin(),v.begin(),v.end());
    std::vector<int>expectations = {1,10,20,30,2,3};
    std::vector<int>actual;
    for(auto x: fl){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectations);
    EXPECT_EQ(fl.get_size(),6);
    EXPECT_FALSE(fl.is_empty());
}
TEST(Insert_testing,insert_afterIII){
    forward_lists<int>fl = {1,2,3,4,5};
    EXPECT_EQ(fl.get_size(),5);
    forward_lists<int>flst;
    EXPECT_TRUE(flst.is_empty());
    flst.push_front(10);
    flst.push_front(20);
    flst.push_front(30);
    EXPECT_EQ(flst.get_size(),3);
    //flst  = {30 20 10}
    fl.insert_after(fl.begin(),flst.begin(),flst.end());
    std::vector<int>expectations = {1,30,20,10,2,3,4,5};
    std::vector<int>actual;
    for(auto x: fl){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectations);
    EXPECT_EQ(fl.get_size(),8);
}
TEST(erase_testing,erase_afterI){
    forward_lists<int>fl = {10,20,30,40,50,60,70,80,90,100};
    EXPECT_EQ(fl.get_size(),10);
    fl.erase_after(fl.begin());
    std::vector<int>expectations = {10,30,40,50,60,70,80,90,100};
    std::vector<int>actual;
    for(auto x: fl){
        actual.push_back(x);
    }
    EXPECT_EQ(fl.get_size(),9);
    EXPECT_EQ(actual,expectations);
}
TEST(Assign_test,Assign_testI){
    forward_lists<int>list = {1,2,3,4,5};
    EXPECT_EQ(list.get_size(),5);
    list.assign(10,100);
    EXPECT_EQ(list.get_size(),10);
    std::vector<int>expectations = {100,100,100,100,100,100,100,100,100,100};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectations);
}
TEST(Assign_test,Assign_testII){
    forward_lists<int>list = {100,100,100,100,100,100,100,100,100,100};
    EXPECT_EQ(list.get_size(),10);
    list.assign({1,2,3,4,5,6});
    EXPECT_EQ(list.get_size(),6);
    std::vector<int>expectations = {1,2,3,4,5,6};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectations);
}
TEST(Assign_test,Assign_testIII){
    forward_lists<int>list = {100,100,100,100,100,100,100,100,100,100};
    EXPECT_EQ(list.get_size(),10);
    std::vector<int>Cp = {45,6,7,1,35,62,1};
    list.assign(Cp.begin(),Cp.end());
    EXPECT_EQ(list.get_size(),7);
    std::vector<int>expectations = {45,6,7,1,35,62,1};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectations);
}
TEST(splice_test,splice_testI){
    forward_lists<int>fl = {1,2,3};
    forward_lists<int>list = {10,20,30};
    fl.splice_after(fl.begin(),list);
    std::vector<int>expectations = {1,10,20,30,2,3};
    std::vector<int>actual;
    for(auto x: fl){
        actual.push_back(x);
    }
    EXPECT_EQ(fl.get_size(),6);
    EXPECT_EQ(list.get_size(),0);
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(actual,expectations);
}
TEST(splice_test,splice_testII){
    forward_lists<int>fl = {100,200,300};
    forward_lists<int>lists = {20,30,40};
    EXPECT_EQ(fl.get_size(),3);
    EXPECT_EQ(lists.get_size(),3);
    fl.splice_after(fl.begin(),lists,lists.begin());
    std::vector<int>expectations = {100,30,200,300};
    std::vector<int>actual;
    for(auto x: fl){
        actual.push_back(x);
    }
    EXPECT_EQ(fl.get_size(),4);
    EXPECT_EQ(lists.get_size(),2); 
    EXPECT_EQ(actual,expectations);
}
TEST(splice_test,splice_testIII){
    forward_lists<int>fl = {1000,2000,3000,4000,5000,6000};
    forward_lists<int>lists = {1,2,3,4,5};
    EXPECT_EQ(fl.get_size(),6);
    EXPECT_EQ(lists.get_size(),5);
    fl.splice_after(fl.begin(),lists,lists.begin(),lists.end());
    std::vector<int>expectations = {1000,2,3,4,5,2000,3000,4000,5000,6000};
    std::vector<int>actual;
    for(auto x: fl){
        actual.push_back(x);
    }
    EXPECT_EQ(fl.get_size(),10);
    EXPECT_EQ(lists.get_size(),1); 
    EXPECT_EQ(actual,expectations);
}