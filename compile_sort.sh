#!/bin/zsh
set -euo pipefail

CXX=clang++
# ZSH: pakai array agar tiap flag jadi argumen terpisah
CXXFLAGS=(-std=c++20 -O2 -Wall -Wextra -pedantic -Iheader)
BIN_DIR=bin

mkdir -p "$BIN_DIR"

echo "Sedang mengkompilasi implementation (dengan header)..."
$CXX $CXXFLAGS -c implementation/implementation_sort.cpp -o "$BIN_DIR/imp.o"

echo "Sedang melakukan proses linking..."
$CXX $CXXFLAGS "$BIN_DIR/imp.o" -o "$BIN_DIR/res"

echo "Menjalankan program..."
"./$BIN_DIR/res"
