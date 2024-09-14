
#include "test_math_vector.h"
#include <stdio.h>
#include <chrono>

#ifdef USE_NAMESPACE
namespace USE_NAMESPACE {
#endif

#ifndef USE_RAW_SCALAR_FILTER
	inline float4 load_pixel(const uint8_t* src, int size, int x, int y)
	{
		x &= size - 1;
		y &= size - 1;
		uchar4 bpix(src + (y * size + x) * 4);
		float4 pix = float4(bpix) * (1.0f / 255.0f);
		return pix;
	}
	inline void store_pixel(uint8_t* dst, int size, int x, int y, float4 pix)
	{
		pix = math_max(pix, float4(0.0f));
		pix = math_min(pix, float4(1.0f));
		pix = math_round(pix * 255.0f);
		((uchar4*)dst)[y * size + x] = uchar4(pix);
	}
#else
	inline void load_pixel(const uint8_t* src, int size, int x, int y, float pix[4])
	{
		x &= size - 1;
		y &= size - 1;
		const uint8_t* ptr = src + (y * size + x) * 4;
		pix[0] = ptr[0] * (1.0f / 255.0f);
		pix[1] = ptr[1] * (1.0f / 255.0f);
		pix[2] = ptr[2] * (1.0f / 255.0f);
		pix[3] = ptr[3] * (1.0f / 255.0f);
	}
	inline void store_pixel(uint8_t* dst, int size, int x, int y, const float pix[4])
	{
		float r = std::max(pix[0], 0.0f);
		float g = std::max(pix[1], 0.0f);
		float b = std::max(pix[2], 0.0f);
		float a = std::max(pix[3], 0.0f);
		r = std::min(r, 1.0f);
		g = std::min(g, 1.0f);
		b = std::min(b, 1.0f);
		a = std::min(a, 1.0f);
		r = std::round(r * 255.0f);
		g = std::round(g * 255.0f);
		b = std::round(b * 255.0f);
		a = std::round(a * 255.0f);
		uint8_t* ptr = dst + (y * size + x) * 4;
		ptr[0] = uint8_t(r);
		ptr[1] = uint8_t(g);
		ptr[2] = uint8_t(b);
		ptr[3] = uint8_t(a);
	}
#endif

float filter_image(int size, const uint8_t* src, uint8_t* dst)
{
	auto t0 = std::chrono::high_resolution_clock::now();
	const int kFilter = 5;
	int idx = 0;
	float blend = 0.2f;
	float inv_size = 1.0f / size;
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
#ifndef USE_RAW_SCALAR_FILTER
			float4 pix(0.0f);
			float4 tint(x * inv_size, y * inv_size, 1.0f - x * inv_size, 1.0f);
			for (int by = y - kFilter; by <= y + kFilter; by++)
			{
				for (int bx = x - kFilter; bx <= x + kFilter; bx++)
				{
					float4 sample = load_pixel(src, size, bx, by);
					sample = sample * (1.0f - blend) + tint * blend;
					pix += sample;
				}
			}
			pix *= 1.0f / ((kFilter * 2 + 1) * (kFilter * 2 + 1));
			store_pixel(dst, size, x, y, pix);
#else
			float pix[4] = { 0,0,0,0 };
			float tint[4] = { x * inv_size, y * inv_size, 1.0f - x * inv_size, 1.0f };
			for (int by = y - kFilter; by <= y + kFilter; by++)
			{
				for (int bx = x - kFilter; bx <= x + kFilter; bx++)
				{
					float sample[4];
					load_pixel(src, size, bx, by, sample);
					sample[0] = sample[0] * (1.0f - blend) + tint[0] * blend;
					sample[1] = sample[1] * (1.0f - blend) + tint[1] * blend;
					sample[2] = sample[2] * (1.0f - blend) + tint[2] * blend;
					sample[3] = sample[3] * (1.0f - blend) + tint[3] * blend;
					pix[0] += sample[0];
					pix[1] += sample[1];
					pix[2] += sample[2];
					pix[3] += sample[3];
				}
			}
			float scale = 1.0f / ((kFilter * 2 + 1) * (kFilter * 2 + 1));
			pix[0] *= scale;
			pix[1] *= scale;
			pix[2] *= scale;
			pix[3] *= scale;
			store_pixel(dst, size, x, y, pix);
#endif
		}
	}
	auto t1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> dt = t1 - t0;
	return dt.count();
}

#ifdef USE_NAMESPACE
} // namespace
#endif
