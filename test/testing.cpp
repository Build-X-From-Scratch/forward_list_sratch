#include <gtest/gtest.h>
#include <cstddef>
#include <vector>
#include <numeric>
#include <ranges>
#include <algorithm>
#include "../header/forward_list.hpp"
// ==== Helper Function ====
template<typename T>
void check_merge_result(forward_lists<T>& dest,
                        forward_lists<T>& donor,
                        const std::vector<T>& expected)
{
    // donor harus kosong
    EXPECT_TRUE(donor.is_empty());

    // size harus sesuai
    EXPECT_EQ(dest.get_size(), expected.size());

    // isi harus sama
    std::vector<T> actual;
    for (auto x : dest) {
        actual.push_back(x);
    }
    EXPECT_EQ(actual, expected);
}

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
TEST(Modifiers_testing,swap_testing){
    forward_lists<int>fl = {100,200,300,400};
    forward_lists<int>list = {12,13,14,15,16,17};
    EXPECT_EQ(fl.get_size(),4);
    EXPECT_EQ(list.get_size(),6);
    std::vector<int>expectation_a = {12,13,14,15,16,17};
    std::vector<int>expectation_b = {100,200,300,400};
    std::vector<int>actual_a,actual_b;
    fl.swap(list);
    for(auto x: fl){
        actual_a.push_back(x);
    }
    for(auto x: list){
        actual_b.push_back(x);
    }
    EXPECT_EQ(actual_a,expectation_a);
    EXPECT_EQ(actual_b,expectation_b);
}
TEST(Sort_testing,Sorting_testI){
    forward_lists<int>list = {10,9,8,7,6,5};
    EXPECT_EQ(list.get_size(), 6);
    list.sort();
    std::vector<int>expectations = {5,6,7,8,9,10};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectations);
}
TEST(Sort_testing, Sorting_with_comparator) {
    // data awal
    forward_lists<int> list = {42, 13, 7, 99, 5, 21, 88};
    EXPECT_EQ(list.get_size(), 7);

    // ---- test ascending (default) ----
    list.sort(std::less<int>());
    std::vector<int> expectations = {5, 7, 13, 21, 42, 88, 99};
    std::vector<int> actual;
    for (auto x : list) {
        actual.push_back(x);
    }
    EXPECT_EQ(actual, expectations);

    // ---- test descending ----
    forward_lists<int> list2 = {42, 13, 7, 99, 5, 21, 88};
    list2.sort(std::greater<int>());
    expectations = {99, 88, 42, 21, 13, 7, 5};
    actual.clear();
    for (auto x : list2) {
        actual.push_back(x);
    }
    EXPECT_EQ(actual, expectations);

    // ---- test custom: urutkan berdasarkan digit terakhir ----
    forward_lists<int> list3 = {42, 13, 7, 99, 5, 21, 88};
    list3.sort([](int a, int b) {
        return (a % 10) < (b % 10); // bandingkan berdasarkan satuan
    });
    expectations = {21, 42, 13, 5, 7, 88, 99}; 
    // penjelasan: digit akhir = {1,2,3,5,7,8,9}
    actual.clear();
    for (auto x : list3) {
        actual.push_back(x);
    }
    EXPECT_EQ(actual, expectations);
}
TEST(Sort_testing, Sorting_random_stress) {
    const int N = 1000;
    std::vector<int> input;
    for (int i = 0; i < N; i++) {
        input.push_back(rand() % 10000); // random angka
    }

    forward_lists<int> list;
    for (int x : input) {
        list.push_front(x);  // isi pakai push_front
    }

    // ground truth (pakai input asli, urutan nggak penting karena di-sort juga)
    std::vector<int> expectations = input;
    std::sort(expectations.begin(), expectations.end(), std::greater<int>());

    // sort dengan comparator custom (descending)
    list.sort(std::greater<int>());

    // ambil hasil dari forward_list
    std::vector<int> actual;
    for (auto x : list) {
        actual.push_back(x);
    }

    EXPECT_EQ(actual, expectations);
}
TEST(Insert_testing,push_back_testing){
    forward_lists<int>list;
    EXPECT_TRUE(list.is_empty());
    list.push_back(1);
    EXPECT_EQ(list.get_size(),1);
    list.push_back(2);
     EXPECT_EQ(list.get_size(),2);
    list.push_back(3);
     EXPECT_EQ(list.get_size(),3);
    std::vector<int>expectations = {1,2,3};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectations);
}
TEST(pop_testing,pop_back_test){
    forward_lists<int>list = {1,2,3};
    list.pop_back();
    EXPECT_EQ(list.get_size(),2);
    list.pop_back();
    EXPECT_EQ(list.get_size(),1);
}
TEST(merge_testing,Merge_testI){
    forward_lists<int>fl = {1,2,3};
    forward_lists<int>list = {4,5,6};
    list.merge(fl);
    EXPECT_TRUE(fl.is_empty());
    std::vector<int>expectations = {1,2,3,4,5,6};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectations);
}
TEST(merge_testing, Merge_StressTest) {
    // merge banyak list kecil -> jadi satu list panjang
    const int N = 1000; // jumlah list
    const int M = 10;   // ukuran tiap list
    std::vector<forward_lists<int>> lists;
    lists.reserve(N);

    // siapkan banyak list dengan isi unik
    int counter = 0;
    for (int i = 0; i < N; i++) {
        forward_lists<int> fl;
        for (int j = 0; j < M; j++) {
            fl.push_back(counter++);
        }
        lists.push_back(std::move(fl));
    }

    // merge semua list ke list pertama
    for (int i = 1; i < N; i++) {
        lists[0].merge(lists[i]);
        EXPECT_TRUE(lists[i].is_empty());  // donor harus kosong
    }

    // cek ukuran akhir
    EXPECT_EQ(lists[0].get_size(), N * M);

    // cek isi urut sesuai konstruksi
    std::vector<int> actual;
    for (auto x : lists[0]) {
        actual.push_back(x);
    }

    std::vector<int> expected(N * M);
    std::iota(expected.begin(), expected.end(), 0); // 0..N*M-1

    EXPECT_EQ(actual, expected);
}

TEST(merge_testing, Merge_WithEmptyLists) {
    forward_lists<int> fl1 = {1,2,3};
    forward_lists<int> empty;

    // merge dengan list kosong
    fl1.merge(empty);
    EXPECT_TRUE(empty.is_empty());
    EXPECT_EQ(fl1.get_size(), 3);

    // merge list kosong ke list isi
    empty.merge(fl1);
    EXPECT_TRUE(fl1.is_empty());
    EXPECT_EQ(empty.get_size(), 3);

    std::vector<int> actual;
    for (auto x : empty) {
        actual.push_back(x);
    }
    std::vector<int> expected = {1,2,3};
    EXPECT_EQ(actual, expected);
}

TEST(merge_testing, Merge_SelfMerge) {
    forward_lists<int> fl = {1,2,3};
    fl.merge(fl); // harus tidak crash dan tidak berubah
    EXPECT_EQ(fl.get_size(), 3);

    std::vector<int> actual;
    for (auto x : fl) {
        actual.push_back(x);
    }
    std::vector<int> expected = {1,2,3};
    EXPECT_EQ(actual, expected);
}
TEST(merge_testing, Merge_BasicGlobalRef) {
    forward_lists<int> fl = {1,2,3};
    forward_lists<int> list = {4,5,6};

    list.merge(fl);

    check_merge_result(list, fl, {1,2,3,4,5,6});
}

TEST(merge_testing, Merge_EmptyGlobalRef) {
    forward_lists<int> fl = {1,2,3};
    forward_lists<int> empty;

    // merge empty ke fl
    fl.merge(empty);
    check_merge_result(fl, empty, {1,2,3});

    // merge fl ke empty
    empty.merge(fl);
    check_merge_result(empty, fl, {1,2,3});
}

TEST(merge_testing, Merge_SelfGlobalRef) {
    forward_lists<int> fl = {1,2,3};
    fl.merge(fl); // STL-like: no-op

    EXPECT_EQ(fl.get_size(), 3);

    std::vector<int> actual;
    for (auto x : fl) {
        actual.push_back(x);
    }
    EXPECT_EQ(actual, (std::vector<int>{1,2,3}));
}

TEST(merge_testing, Merge_StressGlobalRef) {
    const int N = 500;
    const int M = 20;

    std::vector<forward_lists<int>> lists;
    lists.reserve(N);

    int counter = 0;
    for (int i = 0; i < N; i++) {
        forward_lists<int> fl;
        for (int j = 0; j < M; j++) {
            fl.push_back(counter++);
        }
        lists.push_back(std::move(fl));
    }

    for (int i = 1; i < N; i++) {
        lists[0].merge(lists[i]);
    }

    std::vector<int> expected(N * M);
    std::iota(expected.begin(), expected.end(), 0);

    check_merge_result(lists[0], lists[N-1], expected);
}
TEST(merge_sort,merge_sort_testingI){
    forward_lists<int>list = {1,2,3};
    forward_lists<int>fl = {4,5,6};
    list.merge_sort(fl);
    std::vector<int>expectation = {1,2,3,4,5,6};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}   
TEST(niqe_testing,delete_global){
    forward_lists<int>list = {1, 2, 2, 3, 4, 4, 4, 5, 5};
    list.uniqe_all();
    std::vector<int>expectation = {1, 2, 3, 4, 5};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(unique_testing,adjency_duplicate){
    forward_lists<int> list = { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 2, 4, 4 }; 
    list.uniqe();
    std::vector<int>expectations = {1,2,3,2,4};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectations);
}
TEST(assign_range,container_testing){
    forward_lists<int>list = {1,2,3};
    EXPECT_EQ(list.get_size(),3);
    std::vector<int>assgn = {100,200,300};
    list.assign_range(assgn);
    std::vector<int>expectation = {100,200,300};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
    EXPECT_EQ(list.get_size(),3);
}
// 1) Assign dari range kosong ke list non-empty
TEST(assign_range, empty_range_overwrites_nonempty) {
    forward_lists<int> list = {1,2,3,4,5};
    ASSERT_EQ(list.get_size(), 5u);

    std::vector<int> empty;
    EXPECT_NO_THROW(list.assign_range(empty));

    std::vector<int> actual;
    for (auto &x : list) actual.push_back(x);

    EXPECT_TRUE(actual.empty());
    EXPECT_EQ(list.get_size(), 0u);
}

// 2) Assign dari vector besar (stress ukuran)
TEST(assign_range, large_vector_stress) {
    constexpr int N = 100000;
    std::vector<int> big(N);
    std::iota(big.begin(), big.end(), 0);

    forward_lists<int> list = {42};
    list.assign_range(big);

    ASSERT_EQ(list.get_size(), static_cast<size_t>(N));

    // Build actual sekali, lalu cek beberapa titik
    std::vector<int> actual;
    actual.reserve(N);
    for (auto &x : list) actual.push_back(x);

    ASSERT_EQ(actual.size(), static_cast<size_t>(N));
    EXPECT_EQ(actual.front(), 0);
    EXPECT_EQ(actual[12345], 12345);
    EXPECT_EQ(actual.back(), N - 1);
}

// 3) Assign dari iota view (lazy input range)
TEST(assign_range, iota_view_basic) {
    auto rng = std::views::iota(10, 20); // 10..19

    forward_lists<int> list;
    list.assign_range(rng);

    std::vector<int> expectation(10);
    std::iota(expectation.begin(), expectation.end(), 10);

    std::vector<int> actual;
    for (auto &x : list) actual.push_back(x);

    EXPECT_EQ(actual, expectation);
    EXPECT_EQ(list.get_size(), expectation.size());
}

// 4) Assign dari pipeline view (filter + transform)
TEST(assign_range, filtered_transformed_view) {
    std::vector<int> base(50);
    std::iota(base.begin(), base.end(), 0);

    auto even_squares =
        base
        | std::views::filter([](int x){ return x % 2 == 0; })
        | std::views::transform([](int x){ return x * x; });

    forward_lists<int> list = {-1,-2,-3};
    list.assign_range(even_squares);

    std::vector<int> expectation;
    expectation.reserve(25);
    for (int i = 0; i < 50; i += 2) expectation.push_back(i * i);

    std::vector<int> actual;
    for (auto &x : list) actual.push_back(x);

    EXPECT_EQ(actual, expectation);
    EXPECT_EQ(list.get_size(), expectation.size());
}

// 5) Repeated assign dengan ukuran naik-turun
TEST(assign_range, repeated_resizing) {
    forward_lists<int> list;

    // a) kosong -> kecil
    list.assign_range(std::initializer_list<int>{7,8});
    {
        std::vector<int> actual;
        for (auto &x : list) actual.push_back(x);
        EXPECT_EQ(actual, (std::vector<int>{7,8}));
        EXPECT_EQ(list.get_size(), 2u);
    }

    // b) kecil -> besar
    std::vector<int> vbig(5000);
    std::iota(vbig.begin(), vbig.end(), 1);
    list.assign_range(vbig);
    {
        std::vector<int> actual;
        actual.reserve(5000);
        for (auto &x : list) actual.push_back(x);
        ASSERT_EQ(actual.size(), 5000u);
        EXPECT_EQ(actual.front(), 1);
        EXPECT_EQ(actual.back(), 5000);
        EXPECT_EQ(list.get_size(), 5000u);
    }

    // c) besar -> sangat kecil
    list.assign_range(std::initializer_list<int>{42});
    {
        std::vector<int> actual;
        for (auto &x : list) actual.push_back(x);
        EXPECT_EQ(actual, (std::vector<int>{42}));
        EXPECT_EQ(list.get_size(), 1u);
    }

    // d) kecil -> kosong
    std::vector<int> empty;
    list.assign_range(empty);
    {
        std::vector<int> actual;
        for (auto &x : list) actual.push_back(x);
        EXPECT_TRUE(actual.empty());
        EXPECT_EQ(list.get_size(), 0u);
    }
}

// 6) Assign dari initializer_list langsung
TEST(assign_range, initializer_list_direct) {
    forward_lists<int> list = {9,9,9};
    list.assign_range({100,200,300,400});

    std::vector<int> expectation = {100,200,300,400};
    std::vector<int> actual;
    for (auto &x : list) actual.push_back(x);

    EXPECT_EQ(actual, expectation);
    EXPECT_EQ(list.get_size(), expectation.size());
}

// 7) Assign dari container lain (forward_lists -> forward_lists via buffer)
TEST(assign_range, from_another_forward_lists) {
    forward_lists<int> src = {5,4,3,2,1};
    forward_lists<int> dst = {42};

    // buffer aman (hindari self-assign langsung)
    std::vector<int> buffer;
    for (auto &x : src) buffer.push_back(x);

    dst.assign_range(buffer);

    std::vector<int> actual;
    for (auto &x : dst) actual.push_back(x);

    EXPECT_EQ(actual, (std::vector<int>{5,4,3,2,1}));
    EXPECT_EQ(dst.get_size(), 5u);
}

// 8) Stress: banyak round dengan views berbeda-beda
TEST(assign_range, many_views_mixed_stress) {
    forward_lists<int> list;

    for (int round = 0; round < 50; ++round) {
        int start = round * 10;
        int stop  = start + 10;
        auto rng = std::views::iota(start, stop);

        if (round % 2 == 0) {
            auto evens = rng | std::views::filter([](int x){ return x % 2 == 0; });
            list.assign_range(evens);

            std::vector<int> expectation;
            for (int x = start; x < stop; ++x) if (x % 2 == 0) expectation.push_back(x);

            std::vector<int> actual;
            for (auto &v : list) actual.push_back(v);

            EXPECT_EQ(actual, expectation);
            EXPECT_EQ(list.get_size(), expectation.size());
        } else {
            auto odds_sq = rng
                | std::views::filter([](int x){ return x % 2 != 0; })
                | std::views::transform([](int x){ return x * x; });
            list.assign_range(odds_sq);

            std::vector<int> expectation;
            for (int x = start; x < stop; ++x) if (x % 2 != 0) expectation.push_back(x * x);

            std::vector<int> actual;
            for (auto &v : list) actual.push_back(v);

            EXPECT_EQ(actual, expectation);
            EXPECT_EQ(list.get_size(), expectation.size());
        }
    }
}

// 9) Robustness: hindari self-assign langsung (copy terlebih dahulu)
TEST(assign_range, avoid_self_assign_by_copy_first) {
    forward_lists<int> list = {1,2,3,4};
    std::vector<int> buffer;
    for (auto &x : list) buffer.push_back(x);

    EXPECT_NO_THROW(list.assign_range(buffer));

    std::vector<int> actual;
    for (auto &x : list) actual.push_back(x);

    EXPECT_EQ(actual, (std::vector<int>{1,2,3,4}));
    EXPECT_EQ(list.get_size(), 4u);
}
TEST(remove,remove_single_value){
    forward_lists<int>list = {1,2,3,4,5};
    EXPECT_EQ(list.get_size(),5);
    // int value = 3;
    list.remove(3);
    EXPECT_EQ(list.get_size(),4);
    std::vector<int>expectation = {1,2,4,5};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(remove,remove_single_value_on_tail){
    forward_lists<int>list = {1,2,3,4,5};
    EXPECT_EQ(list.get_size(),5);
    EXPECT_EQ(list.back(),5);
    // int value = 5;
    list.remove(5);
    EXPECT_EQ(list.get_size(),4);
    std::vector<int>expectation ={1,2,3,4};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(list.back(),4);
    EXPECT_EQ(actual,expectation);
}
TEST(remove,remove_node_on_pos){
    forward_lists<int>list = {1,2,3,4,5};
    EXPECT_EQ(list.get_size(),5);
    // int value = 5;
    std::size_t pos = 3;
    list.remove(pos);
    EXPECT_EQ(list.get_size(),4);
    std::vector<int>expectation ={1, 2, 3, 5};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(remove, remove_from_empty_list) {
    forward_lists<int> list;
    EXPECT_EQ(list.get_size(), 0);
    list.remove(10); // harusnya aman
    EXPECT_EQ(list.get_size(), 0);
}

TEST(remove, remove_head_by_pos) {
    forward_lists<int> list = {1,2,3,4,5};
    list.remove(std::size_t(0));
    EXPECT_EQ(list.get_size(), 4);

    std::vector<int> expected = {2,3,4,5};
    std::vector<int> actual;
    for(auto x: list) actual.push_back(x);
    EXPECT_EQ(actual, expected);
}

TEST(remove, remove_tail_by_value) {
    forward_lists<int> list = {10,20,30};
    list.remove(30);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.back(), 20);
}

TEST(remove, remove_middle_by_value) {
    forward_lists<int> list = {7,8,9,10};
    list.remove(9);
    EXPECT_EQ(list.get_size(), 3);

    std::vector<int> expected = {7,8,10};
    std::vector<int> actual;
    for(auto x: list) actual.push_back(x);
    EXPECT_EQ(actual, expected);
}

TEST(remove, remove_all_elements_by_pos) {
    forward_lists<int> list = {1,2,3,4,5};
    for(int i=0; i<5; i++) {
        list.remove(std::size_t(0)); // selalu hapus head
    }
    EXPECT_EQ(list.get_size(), 0);
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.begin(), list.end()); // list kosong
}

TEST(remove, remove_non_existent_value) {
    forward_lists<int> list = {1,2,3};
    list.remove(99); // tidak ada 99
    EXPECT_EQ(list.get_size(), 3);

    std::vector<int> expected = {1,2,3};
    std::vector<int> actual;
    for(auto x: list) actual.push_back(x);
    EXPECT_EQ(actual, expected);
}

TEST(remove, stress_remove_many_elements) {
    forward_lists<int> list;
    for(int i=0; i<1000; i++) {
        list.push_back(i);
    }
    EXPECT_EQ(list.get_size(), 1000);

    list.remove(0);                     // hapus head
    list.remove(500);                   // hapus tengah
    list.remove(list.get_size()-1);     // hapus tail

    EXPECT_EQ(list.get_size(), 997);

}
TEST(emplace_testing,emplace_front_testing){
    forward_lists<int>list = {1,2,3};
    EXPECT_EQ(list.get_size(),3);
    list.emplace_front(5);
    EXPECT_EQ(list.get_size(),4);
    std::vector<int>expectation = {5,1,2,3};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}   
TEST(emplace_testing,emplace_back_testing){
    forward_lists<int>list = {1,2,3};
    EXPECT_EQ(list.get_size(),3);
    list.emplace_front(5);
    EXPECT_EQ(list.get_size(),4);
    list.emplace_back(10);
    std::vector<int>expectation = {5,1,2,3,10};
    EXPECT_EQ(list.get_size(),5);
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}   
TEST(emplace_testing,emplace_front_testing_empty){
    forward_lists<int>list;
    EXPECT_TRUE(list.is_empty());
    list.emplace_front(1);
    EXPECT_TRUE(!list.is_empty());
    list.emplace_front(2);
    list.emplace_front(3);
    std::vector<int>expectation = {3,2,1};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(emplace_testing,emplace_back_testing_empty){
    forward_lists<int>list;
    EXPECT_TRUE(list.is_empty());
    list.emplace_back(1);
    EXPECT_EQ(list.get_size(),1);
    EXPECT_TRUE(!list.is_empty());
    list.emplace_back(2);
    EXPECT_EQ(list.get_size(),2);
    list.emplace_back(3);
    EXPECT_EQ(list.get_size(),3);
    std::vector<int>expectation = {1,2,3};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(remove_if,simple_remove_lambda){
    forward_lists<int>list = {1,2,4,6,8,9,10};
    // int k = 3;
    list.remove_if([](int x){return x % 2 == 0;});
    std::vector<int>expectation = {1,9};
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(remove_if,remove_until_empty){
    forward_lists<int> list = {2,2,2,2,2,2,2,2};
    list.remove_if([](int x){return x % 2 == 0 ;});
    std::vector<int>expectation = {};
    std::vector<int>actual;
    EXPECT_TRUE(list.is_empty());
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(remove_if,remove_stressTesting){
    forward_lists<int>list;
    int k = 10;
    for(int i = 0;i <= 100;i++){
        list.push_back(i);
        list.remove_if([k](int x){return x <= k;});
    }
    std::vector<int>expectations;
    for(int i = 11;i <= 100;i++){
        expectations.push_back(i);
    }
    std::vector<int>actual;
    for(auto x: list){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectations);
}