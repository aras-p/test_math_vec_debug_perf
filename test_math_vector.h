// Adapted from Blender BLI_math_vector.hh, BLI_math_vector_types.hh,
// BLI_unroll.hh
// which is copyright: Blender Authors, license: GPL-2.0 or later

//#pragma once // note: no, we expect this to be included several times with different namespaces/defines

#include <cmath>

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>

// Macros controlling behavior:
// USE_NAMESPACE: wrap everything into given namespace
// USE_ASSERTS: enable asserts
// USE_LOOP_INSTEAD_OF_UNROLL: use a simple loop instead of unroll<>
// USE_EXPLICIT_XYZW: use explicit xyzw accessors instead of loop/unroll
// USE_SIMD: use SSE for float4

#ifdef USE_SIMD
#if defined(__x86_64__) || defined(_M_X64) || defined(__SSE2__)
#include <emmintrin.h>
#include <smmintrin.h>
#define USE_SIMD_SSE
#endif
#endif

// --------------------------------------------------------------------------
// Assertion utility

void test_do_assert_msg(const char* file, int line, const char* function, const char* msg);

#ifdef USE_ASSERTS
#	define test_assert(a) (void)((!(a)) ? (test_do_assert_msg(__FILE__, __LINE__, __FUNCTION__, #a), 0) : 0)
#else
#   define test_assert(a) ((void)0)
#endif


#ifdef USE_NAMESPACE
namespace USE_NAMESPACE {
#endif

    // --------------------------------------------------------------------------
    // "Unrolling" utility

#ifndef USE_LOOP_INSTEAD_OF_UNROLL
    template<class Fn, size_t... I> void unroll_impl(Fn fn, std::index_sequence<I...> indices)
    {
        (fn(I), ...);
    }

    template<int N, class Fn> void unroll(Fn fn)
    {
        unroll_impl(fn, std::make_index_sequence<N>());
    }
#endif

    // --------------------------------------------------------------------------
    // Math vector type: fixed size array of values. For 2/3/4 dimensional vectors,
    // explicit members of xy, xyz, xyzw.

    template<typename T, int Size> struct vec_struct_base { std::array<T, Size> values; };
    template<typename T> struct vec_struct_base<T, 2> { T x, y; };
    template<typename T> struct vec_struct_base<T, 3> { T x, y, z; };
    template<typename T> struct vec_struct_base<T, 4> { T x, y, z, w; };
#ifdef USE_SIMD_SSE
    template<> struct vec_struct_base<float, 4> { __m128 simd; };
#endif


    template<typename T, int Size>
    struct VecBase : public vec_struct_base<T, Size>
    {
        VecBase() = default;

        explicit inline VecBase(T value)
        {
#ifdef USE_SIMD_SSE
            if constexpr (std::is_same_v<T, float> && Size == 4) {
                this->simd = _mm_set1_ps(value);
                return;
            }
#endif
#ifdef USE_EXPLICIT_XYZW
            if constexpr (Size == 4) {
                this->x = value;
                this->y = value;
                this->z = value;
                this->w = value;
                return;
            }
#endif
            for (int i = 0; i < Size; i++) {
                (*this)[i] = value;
            }
        }
        template<typename std::enable_if_t<(Size == 4)>* = nullptr>
        inline VecBase(T _x, T _y, T _z, T _w)
        {
#ifdef USE_SIMD_SSE
            if constexpr (std::is_same_v<T, float> && Size == 4) {
                this->simd = _mm_set_ps(_w, _z, _y, _x);
                return;
            }
#endif
#ifdef USE_EXPLICIT_XYZW
            this->x = _x;
            this->y = _y;
            this->z = _z;
            this->w = _w;
#else
            (*this)[0] = _x;
            (*this)[1] = _y;
            (*this)[2] = _z;
            (*this)[3] = _w;
#endif
        }

        inline VecBase(const T* ptr)
        {
#ifdef USE_SIMD_SSE
            if constexpr (std::is_same_v<T, float> && Size == 4) {
                this->simd = _mm_loadu_ps(ptr);
                return;
            }
#endif
#ifdef USE_EXPLICIT_XYZW
            if constexpr (Size == 4) {
                this->x = ptr[0];
                this->y = ptr[1];
                this->z = ptr[2];
                this->w = ptr[3];
                return;
            }
#endif

#ifndef USE_LOOP_INSTEAD_OF_UNROLL
            unroll<Size>([&](auto i) { (*this)[i] = ptr[i]; });
#else
            for (int i = 0; i < Size; i++) { (*this)[i] = ptr[i]; }
#endif
        }

        template<typename U> explicit inline VecBase(const VecBase<U, Size>& vec)
        {
#ifdef USE_SIMD_SSE
            if constexpr (std::is_same_v<T, float> && Size == 4) {
                this->simd = _mm_set_ps(float(vec.w), float(vec.z), float(vec.y), float(vec.x));
                return;
            }
#endif
#ifdef USE_EXPLICIT_XYZW
            if constexpr (Size == 4) {
                this->x = T(vec.x);
                this->y = T(vec.y);
                this->z = T(vec.z);
                this->w = T(vec.w);
                return;
            }
#endif
#ifndef USE_LOOP_INSTEAD_OF_UNROLL
            unroll<Size>([&](auto i) { (*this)[i] = T(vec[i]); });
#else
            for (int i = 0; i < Size; i++) { (*this)[i] = T(vec[i]); }
#endif
        }

        inline const T& operator[](int index) const
        {
            test_assert(index >= 0);
            test_assert(index < Size);
            return reinterpret_cast<const T*>(this)[index];
        }

        inline T& operator[](int index)
        {
            test_assert(index >= 0);
            test_assert(index < Size);
            return reinterpret_cast<T*>(this)[index];
        }

        friend inline VecBase operator+(const VecBase& a, const VecBase& b)
        {
#ifdef USE_SIMD_SSE
            if constexpr (std::is_same_v<T, float> && Size == 4) {
                VecBase r;
                r.simd = _mm_add_ps(a.simd, b.simd);
                return r;
            }
#endif
#ifdef USE_EXPLICIT_XYZW
            if constexpr (Size == 4) {
                return VecBase(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
            }
#endif
            VecBase result;
#ifndef USE_LOOP_INSTEAD_OF_UNROLL
            unroll<Size>([&](auto i) { result[i] = a[i] + b[i]; });
#else
            for (int i = 0; i < Size; i++) { result[i] = a[i] + b[i]; }
#endif
            return result;
        }

        inline VecBase& operator+=(const VecBase& b)
        {
#ifdef USE_SIMD_SSE
            if constexpr (std::is_same_v<T, float> && Size == 4) {
                this->simd = _mm_add_ps(this->simd, b.simd);
                return *this;
            }
#endif
#ifdef USE_EXPLICIT_XYZW
            if constexpr (Size == 4) {
                this->x += b.x;
                this->y += b.y;
                this->z += b.z;
                this->w += b.w;
                return *this;
            }
#endif

#ifndef USE_LOOP_INSTEAD_OF_UNROLL
            unroll<Size>([&](auto i) { (*this)[i] += b[i]; });
#else
            for (int i = 0; i < Size; i++) { (*this)[i] += b[i]; }
#endif
            return *this;
        }

        template<typename FactorT> friend inline VecBase operator*(const VecBase& a, FactorT b)
        {
#ifdef USE_SIMD_SSE
            if constexpr (std::is_same_v<T, float> && Size == 4) {
                VecBase r;
                r.simd = _mm_mul_ps(a.simd, _mm_set1_ps(b));
                return r;
            }
#endif
#ifdef USE_EXPLICIT_XYZW
            if constexpr (Size == 4) {
                return VecBase(a.x * b, a.y * b, a.z * b, a.w * b);
            }
#endif
            VecBase result;
#ifndef USE_LOOP_INSTEAD_OF_UNROLL
            unroll<Size>([&](auto i) { result[i] = a[i] * b; });
#else
            for (int i = 0; i < Size; i++) { result[i] = a[i] * b; }
#endif
            return result;
        }

        inline VecBase& operator*=(T b)
        {
#ifdef USE_SIMD_SSE
            if constexpr (std::is_same_v<T, float> && Size == 4) {
                this->simd = _mm_mul_ps(this->simd, _mm_set1_ps(b));
                return *this;
            }
#endif
#ifdef USE_EXPLICIT_XYZW
            if constexpr (Size == 4) {
                this->x *= b;
                this->y *= b;
                this->z *= b;
                this->w *= b;
                return *this;
            }
#endif

#ifndef USE_LOOP_INSTEAD_OF_UNROLL
            unroll<Size>([&](auto i) { (*this)[i] *= b; });
#else
            for (int i = 0; i < Size; i++) { (*this)[i] *= b; }
#endif
            return *this;
        }
    };

    using uchar4 = VecBase<uint8_t, 4>;
    using float4 = VecBase<float, 4>;


    // --------------------------------------------------------------------------
    // Vector math functions: freestanding functions that work on vector types

    template<typename T, int Size>
    [[nodiscard]] inline VecBase<T, Size> math_min(const VecBase<T, Size>& a, const VecBase<T, Size>& b)
    {
#ifdef USE_SIMD_SSE
        if constexpr (std::is_same_v<T, float> && Size == 4) {
            float4 r;
            r.simd = _mm_min_ps(a.simd, b.simd);
            return r;
        }
#endif
#ifdef USE_EXPLICIT_XYZW
        if constexpr (Size == 4) {
            return VecBase<T, Size>(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
        }
#endif
        VecBase<T, Size> result;
        for (int i = 0; i < Size; i++) {
            result[i] = a[i] < b[i] ? a[i] : b[i];
        }
        return result;
    }

    template<typename T, int Size>
    [[nodiscard]] inline VecBase<T, Size> math_max(const VecBase<T, Size>& a, const VecBase<T, Size>& b)
    {
#ifdef USE_SIMD_SSE
        if constexpr (std::is_same_v<T, float> && Size == 4) {
            float4 r;
            r.simd = _mm_max_ps(a.simd, b.simd);
            return r;
        }
#endif
#ifdef USE_EXPLICIT_XYZW
        if constexpr (Size == 4) {
            return VecBase<T, Size>(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
        }
#endif
        VecBase<T, Size> result;
        for (int i = 0; i < Size; i++) {
            result[i] = a[i] > b[i] ? a[i] : b[i];
        }
        return result;
    }

    template<typename T, int Size>
    [[nodiscard]] inline VecBase<T, Size> math_round(const VecBase<T, Size>& a)
    {
#ifdef USE_SIMD_SSE
        if constexpr (std::is_same_v<T, float> && Size == 4) {
            float4 r;
            r.simd = _mm_round_ps(a.simd, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
            return r;
        }
#endif
#ifdef USE_EXPLICIT_XYZW
        if constexpr (Size == 4) {
            return VecBase<T, Size>(std::round(a.x), std::round(a.y), std::round(a.z), std::round(a.w));
        }
#endif
        VecBase<T, Size> result;
        for (int i = 0; i < Size; i++) {
            result[i] = std::round(a[i]);
        }
        return result;
    }

#undef test_assert

#ifdef USE_NAMESPACE
} // namespace
#endif
