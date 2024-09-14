## Results

All of this on a PC with Ryzen 5950X CPU, Windows 10 and Linux via WSL.


### "Debug" build

| Codegen               | Unroll+Asserts | Loop+Asserts |Xyzw+Asserts | Raw C |
|-----------------------|---------------:|-------------:|------------:|------:|
| Clang Linux 14 O0     |         6054.5 |       5244.0 |      1353.6 | 274.5 |
| Clang Linux 15 O0     |         5952.8 |       5344.5 |      1373.7 | 273.8 |
| Clang Win 17 O0       |         5544.7 |       4388.1 |       803.5 | 277.6 |
| Gcc Linux 11 O0       |         5832.6 |       4349.5 |      1490.0 | 262.2 |
| Gcc Linux 12 O0       |         5610.7 |       4068.0 |      1487.0 | 260.5 |
| VS2022 (v17.11.0) /Od |         7646.8 |       4339.8 |      1281.0 | 285.8 |
|                       |                |              |             |       |
| Clang Linux 14 Og     |           74.4 |        875.1 |        77.0 |  68.5 |
| Clang Linux 15 Og     |           74.4 |        892.1 |        81.3 |  70.6 |
| Clang Win 17 Og       |           88.8 |        366.4 |        81.1 |  80.4 |
| Gcc Linux 11 Og       |          972.0 |       1008.9 |       180.9 | 111.1 |
| Gcc Linux 12 Og       |         3528.8 |       2324.0 |       354.1 | 112.8 |

### "Developer" build (optimizations on, asserts on)

| Codegen               | Unroll+Asserts | Loop+Asserts |Xyzw+Asserts | Raw C |
|-----------------------|---------------:|-------------:|------------:|------:|
| Clang Linux 14 O2     |           49.4 |         49.5 |        49.4 |  22.6 |
| Clang Linux 15 O2     |           52.0 |         49.6 |        49.4 |  22.7 |
| Clang Win 17 O2       |           56.8 |         56.6 |        57.5 |  34.4 |
| Gcc Linux 11 O2       |           71.5 |        696.4 |        69.0 |  69.1 |
| Gcc Linux 12 O2       |           71.0 |        235.4 |        69.1 |  72.5 |
| VS2022 (v17.11.0) /O2 |          591.2 |         82.3 |        80.4 |  82.3 |

### "Release" build

| Codegen               | Unroll | Loop   |Xyzw   | Raw C |
|-----------------------|-------:|-------:|------:|------:|
| Clang Linux 14 O2     |   49.2 |   48.3 |  49.4 |  22.6 |
| Clang Linux 15 O2     |   50.0 |   48.8 |  49.5 |  22.7 |
| Clang Win 17 O2       |   57.1 |   57.2 |  57.5 |  34.4 |
| Gcc Linux 11 O2       |   70.8 |  696.9 |  69.0 |  69.1 |
| Gcc Linux 12 O2       |   70.6 |  230.2 |  69.3 |  72.5 |
| VS2022 (v17.11.0) /O2 |   67.6 |   65.9 |  81.2 |  82.3 |
|                       |        |        |       |       |
| Clang Linux 14 O3     |   26.0 |   26.6 |  25.6 |  22.7 |
| Clang Linux 15 O3     |   30.1 |   30.2 |  26.2 |  22.7 |
| Clang Win 17 O3       |   62.6 |   62.8 |  62.5 |  34.9 |
| Gcc Linux 11 O3       |   69.3 |   68.5 |  68.9 |  69.0 |
| Gcc Linux 12 O3       |   69.7 |   69.7 |  69.4 |  69.8 |

