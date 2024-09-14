echo "Testing gcc-11 Debug (O0)"
gcc-11 main.cpp -lstdc++ -lm -o out_gcc11_o0 -O0 && ./out_gcc11_o0
echo "Testing gcc-11 Debug (Og)"
gcc-11 main.cpp -lstdc++ -lm -o out_gcc11_og -Og && ./out_gcc11_og
echo "Testing gcc-11 Release (O2)"
gcc-11 main.cpp -lstdc++ -lm -o out_gcc11_o2 -O2 && ./out_gcc11_o2
echo "Testing gcc-11 Release (O3)"
gcc-11 main.cpp -lstdc++ -lm -o out_gcc11_o3 -O3 && ./out_gcc11_o3

echo "Testing gcc-12 Debug (O0)"
gcc-12 main.cpp -lstdc++ -lm -o out_gcc12_o0 -O0 && ./out_gcc12_o0
echo "Testing gcc-12 Debug (Og)"
gcc-12 main.cpp -lstdc++ -lm -o out_gcc12_og -Og && ./out_gcc12_og
echo "Testing gcc-12 Release (O2)"
gcc-12 main.cpp -lstdc++ -lm -o out_gcc12_o2 -O2 && ./out_gcc12_o2
echo "Testing gcc-12 Release (O3)"
gcc-12 main.cpp -lstdc++ -lm -o out_gcc12_o3 -O3 && ./out_gcc12_o3
