echo off
cl.exe main.cpp /nologo /std:c++17 /Od /link /out:out_vs_od.exe && out_vs_od.exe
cl.exe main.cpp /nologo /std:c++17 /O2 /link /out:out_vs_o2.exe && out_vs_o2.exe
pause
