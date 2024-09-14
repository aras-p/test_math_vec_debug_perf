echo "Testing clang-14 Debug (O0)"
clang-14 main.cpp -std=c++17 -msse4.2 -lstdc++ -lm -o out_clang14_o0 -O0 && ./out_clang14_o0
echo "Testing clang-14 Debug (Og)"
clang-14 main.cpp -std=c++17 -msse4.2 -lstdc++ -lm -o out_clang14_og -Og && ./out_clang14_og
echo "Testing clang-14 Release (O2)"
clang-14 main.cpp -std=c++17 -msse4.2 -lstdc++ -lm -o out_clang14_o2 -O2 && ./out_clang14_o2
echo "Testing clang-14 Release (O3)"
clang-14 main.cpp -std=c++17 -msse4.2 -lstdc++ -lm -o out_clang14_o3 -O3 && ./out_clang14_o3

echo "Testing clang-15 Debug (O0)"
clang-15 main.cpp -std=c++17 -msse4.2 -lstdc++ -lm -o out_clang15_o0 -O0 && ./out_clang15_o0
echo "Testing clang-15 Debug (Og)"
clang-15 main.cpp -std=c++17 -msse4.2 -lstdc++ -lm -o out_clang15_og -Og && ./out_clang15_og
echo "Testing clang-15 Release (O2)"
clang-15 main.cpp -std=c++17 -msse4.2 -lstdc++ -lm -o out_clang15_o2 -O2 && ./out_clang15_o2
echo "Testing clang-15 Release (O3)"
clang-15 main.cpp -std=c++17 -msse4.2 -lstdc++ -lm -o out_clang15_o3 -O3 && ./out_clang15_o3
