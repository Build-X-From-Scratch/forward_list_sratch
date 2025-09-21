build(){
    # 1) Configure & build (seperti biasa)
cmake -S . -B build
cmake --build build -j

# 2) Jalankan semua test sekali dulu (buat merekam yang gagal)
ctest --test-dir build --output-on-failure

# 3) Rerun hanya test yang gagal barusan
ctest --test-dir build --rerun-failed -V --output-on-failure

}
build