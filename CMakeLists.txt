cmake_minimum_required (VERSION 3.21)

project ("test_math_vec_debug_perf")

add_executable (test_math_vec_debug_perf
	main.cpp
)

set_property(TARGET test_math_vec_debug_perf PROPERTY CXX_STANDARD 17)
target_compile_definitions(test_math_vec_debug_perf PRIVATE
	_CRT_SECURE_NO_DEPRECATE
	_CRT_NONSTDC_NO_WARNINGS
	NOMINMAX
)
