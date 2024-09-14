echo off
cl.exe main.cpp /nologo /std:c++17 /Od /JMC /Z7 /EHsc /RTC1 /GS /link /out:out_vs_odjmc.exe && out_vs_odjmc.exe
cl.exe main.cpp /nologo /std:c++17 /Od /EHsc /GS /link /out:out_vs_od.exe && out_vs_od.exe
cl.exe main.cpp /nologo /std:c++17 /O2 /EHsc /GS /link /out:out_vs_o2.exe && out_vs_o2.exe
pause
