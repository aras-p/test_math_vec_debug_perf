echo off

echo "Testing clang Debug (O0)"
clang main.cpp -std=c++17 -D_CRT_SECURE_NO_WARNINGS -o out_clang_o0.exe -O0 && out_clang_o0.exe
echo "Testing clang Debug (Og)"
clang main.cpp -std=c++17 -D_CRT_SECURE_NO_WARNINGS -o out_clang_og.exe -Og && out_clang_og.exe
echo "Testing clang Release (O2)"
clang main.cpp -std=c++17 -D_CRT_SECURE_NO_WARNINGS -o out_clang_o2.exe -O2 && out_clang_o2.exe
echo "Testing clang Release (O3)"
clang main.cpp -std=c++17 -D_CRT_SECURE_NO_WARNINGS -o out_clang_o3.exe -O3 && out_clang_o3.exe

pause
