## Results

All of this on a PC with Ryzen 5950X CPU, Windows 10 and Linux via WSL.


### "Debug" build

| Codegen               | Unroll+Asserts | Loop+Asserts |Xyzw+Asserts | Raw C | SIMD  |
|-----------------------|---------------:|-------------:|------------:|------:|------:|
| Clang Linux 14 O0     |           6476 |         4858 |        1353 |   274 |  2298 |
| Clang Linux 15 O0     |           7939 |         5013 |        1441 |   286 |  2392 |
| Clang Win 17 O0       |           4965 |         4195 |         788 |   262 |  1821 |
| Gcc Linux 11 O0       |           5942 |         4056 |        1467 |   265 |  1418 |
| Gcc Linux 12 O0       |           5610 |         4068 |        1511 |   261 |  1409 |
| VS2022 (v17.11.0) /Od |           7646 |         4339 |        1281 |   285 |  1603 |
| VS2022 (v17.11.0) /Od /JMC |     17560 |         8446 |        3662 |   316 |  5594 |
|                       |                |              |             |       |
| Clang Linux 14 Og     |             74 |          875 |          75 |    68 |    53 |
| Clang Linux 15 Og     |             73 |          884 |          76 |    67 |    53 |
| Clang Win 17 Og       |             74 |          352 |          68 |    68 |    53 |
| Gcc Linux 11 Og       |            964 |         1009 |         181 |   112 |   104 |
| Gcc Linux 12 Og       |           3528 |         2141 |         354 |   112 |   130 |

### "Developer" build (optimizations on, asserts on)

| Codegen               | Unroll+Asserts | Loop+Asserts |Xyzw+Asserts | Raw C | SIMD  |
|-----------------------|---------------:|-------------:|------------:|------:|------:|
| Clang Linux 14 O2     |             45 |           45 |          45 |    20 |    20 |
| Clang Linux 15 O2     |             45 |           45 |          45 |    20 |    20 |
| Clang Win 17 O2       |             42 |           41 |          42 |    21 |    20 |
| Gcc Linux 11 O2       |             71 |          704 |          72 |    69 |    54 |
| Gcc Linux 12 O2       |             71 |          235 |          69 |    72 |    52 |
| VS2022 (v17.11.0) /O2 |            591 |           82 |          80 |    82 |    52 |

### "Release" build

| Codegen               | Unroll | Loop   |Xyzw   | Raw C | SIMD |
|-----------------------|-------:|-------:|------:|------:|-----:|
| Clang Linux 14 O2     |     45 |     45 |    45 |    20 |   20 |
| Clang Linux 15 O2     |     45 |     45 |    45 |    20 |   20 |
| Clang Win 17 O2       |     41 |     41 |    41 |    21 |   20 |
| Gcc Linux 11 O2       |     70 |    703 |    71 |    69 |   54 |
| Gcc Linux 12 O2       |     70 |    230 |    69 |    72 |   52 |
| VS2022 (v17.11.0) /O2 |     67 |     65 |    81 |    82 |   52 |
|                       |        |        |       |       |
| Clang Linux 14 O3     |     23 |     23 |    23 |    20 |   20 |
| Clang Linux 15 O3     |     23 |     23 |    23 |    20 |   20 |
| Clang Win 17 O3       |     45 |     45 |    44 |    20 |   20 |
| Gcc Linux 11 O3       |     69 |     68 |    68 |    69 |   51 |
| Gcc Linux 12 O3       |     71 |     69 |    69 |    69 |   51 |

