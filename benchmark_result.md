```bash
--------------------------------------------------------------------
Benchmark                          Time             CPU   Iterations
--------------------------------------------------------------------
BM_My_PushFront/1000           15818 ns        15780 ns        37746
BM_My_PushFront/10000         162790 ns       162402 ns         4449
BM_My_PushFront_BigO           16.27 N         16.24 N    
BM_My_PushFront_RMS                0 %             0 %    
BM_Stl_PushFront/1000          16333 ns        16298 ns        37056
BM_Stl_PushFront/10000        158990 ns       158682 ns         4394
BM_Stl_PushFront_BigO          15.90 N         15.87 N    
BM_Stl_PushFront_RMS               0 %             0 %    
BM_my_single_push/1000          40.3 ns         40.1 ns     16242546
BM_my_single_push/100000        41.2 ns         40.3 ns     18130780
BM_my_single_push_BigO         40.73 (1)       40.19 (1)  
BM_my_single_push_RMS              1 %             0 %    
BM_stl_single_push/1000         11.4 ns         11.3 ns     61348061
BM_stl_single_push/100000       11.5 ns         11.4 ns     61208383
BM_stl_single_push_BigO        11.41 (1)       11.38 (1)  
BM_stl_single_push_RMS             0 %             0 %  
```