#!/bin/zsh
set -e
compile_head(){
    echo "Sedang mengkompilasi header..."
    # Asumsi Anda berada di direktori utama, pindah ke 'header'
    cd header
    clang++ -c forward_list.hpp -o ../bin/header.o
    # Kembali ke direktori utama
    cd ..
}
compile_imp(){
    echo "direktori saat ini $pwd"
    echo "Sedang mengkompilasi implementasi..."
    # Asumsi Anda berada di direktori utama, pindah ke 'implementation'
    cd implementation
    clang++ -c implementation.cpp -o ../bin/imp.o
    # Kembali ke direktori utama
    cd ..
}

linking(){
    echo "Sedang melakukan proses linking..."
    # Gunakan path yang benar ke file objek
    clang++ ./bin/header.o ./bin/imp.o -o ./bin/res
}

jalankan(){
    echo "Menyelesaikan semua kompilasi."
    echo "Direktori saat ini: "
    pwd
    echo "Menjalankan program..."
    clear
    # Panggil file executable yang berada di direktori 'bin'
    ./bin/res
}
run(){
    # Buat direktori 'bin' jika belum ada
    if [ ! -d "bin" ]; then
        mkdir bin
    fi
    compile_head
    compile_imp
    linking
    jalankan
}
# Mulai eksekusi
run