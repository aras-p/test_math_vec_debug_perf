
#include "test_math_vector.h"
#include <stdio.h>
#include <chrono>

static float4 load_pixel(const uchar4* src, int size, int x, int y)
{
	x &= size - 1;
	y &= size - 1;
	float4 pix = float4(src[y * size + x]) * (1.0f / 255.0f);
	return pix;
}

static void store_pixel(uchar4* dst, int size, int x, int y, float4 pix)
{
	pix = math_max(pix, float4(0.0f));
	pix = math_min(pix, float4(1.0f));
	pix = math_round(pix * 255.0f);
	dst[y * size + x] = uchar4(pix);
}

static float filter_image(int size, const uchar4* src, uchar4* dst)
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
		}
	}
	auto t1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> dt = t1 - t0;
	return dt.count();
}
