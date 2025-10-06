#include <benchmark/benchmark.h>
#include "../header/forward_list.hpp"
#include <forward_list>
//stl saya
static void BM_My_PushFront(benchmark::State& state){
    for(auto _ : state){
        forward_lists<int>list;
        for(int i = 0;i < state.range(0);i++){
            list.push_front(i);
        }
        state.SetComplexityN(state.range(0));
        benchmark::DoNotOptimize(list);
    }
}
BENCHMARK(BM_My_PushFront)->Arg(1000)->Arg(10000)->Complexity();

static void BM_Stl_PushFront(benchmark::State& state){
    for(auto _ : state){
        std::forward_list<int>list;
        for(int i = 0;i < state.range(0);i++){
            list.push_front(i);
        }
        state.SetComplexityN(state.range(0));
        benchmark::DoNotOptimize(list);
    }
}
BENCHMARK(BM_Stl_PushFront)->Arg(1000)->Arg(10000)->Complexity();

static void BM_my_single_push(benchmark::State& state){
    for(auto _ : state){
        forward_lists<int>list;
        list.push_front(10);
        benchmark::DoNotOptimize(list);
        state.SetComplexityN(state.iterations());
    }
}
BENCHMARK(BM_my_single_push)->Arg(1000)->Arg(100000)->Complexity();

static void BM_stl_single_push(benchmark::State& state){
    for(auto _ : state){
        std::forward_list<int>list;
        list.push_front(10);
        benchmark::DoNotOptimize(list);
        state.SetComplexityN(state.iterations());
    }
}
BENCHMARK(BM_stl_single_push)->Arg(1000)->Arg(100000)->Complexity();
BENCHMARK_MAIN();