
#include <stdio.h>
#include <chrono>

#define USE_NAMESPACE test_assert_unroll
#define USE_ASSERTS
#include "test_filter.h"
#undef USE_NAMESPACE

#define USE_NAMESPACE test_noassert_unroll
#undef USE_ASSERTS
#include "test_filter.h"
#undef USE_NAMESPACE

#define USE_NAMESPACE test_assert_loop
#define USE_LOOP_INSTEAD_OF_UNROLL
#define USE_ASSERTS
#include "test_filter.h"
#undef USE_NAMESPACE

#define USE_NAMESPACE test_noassert_loop
#define USE_LOOP_INSTEAD_OF_UNROLL
#undef USE_ASSERTS
#include "test_filter.h"
#undef USE_NAMESPACE

#define USE_NAMESPACE test_raw
#define USE_RAW_SCALAR_FILTER
#include "test_filter.h"
#undef USE_NAMESPACE


void test_do_assert_msg(const char* file, int line, const char* function, const char* msg)
{
	printf("Assertion failed: '%s' in %s at %s:%i\n", msg, function, file, line);
}

static void WriteTga(const char* path, int width, int height, const uint32_t* data)
{
	FILE* tga = fopen(path, "wb");
	uint8_t header[] = {
		0, // ID length
		0, // no color map
		2, // uncompressed, true color
		0, 0, 0, 0,
		0,
		0, 0, 0, 0, // x and y origin
		uint8_t(width & 0x00FF),
		uint8_t((width & 0xFF00) >> 8),
		uint8_t(height & 0x00FF),
		uint8_t((height & 0xFF00) >> 8),
		32, // bpp
		0
	};
	fwrite(header, 1, sizeof(header), tga);
	fwrite(data, 4, width * height, tga);
	fclose(tga);
}

int main()
{
	const int kSize = 256;
	uint8_t* src_image = new uint8_t[kSize * kSize * 4];
	int idx = 0;
	for (int y = 0; y < kSize; y++)
	{
		for (int x = 0; x < kSize; x++)
		{
			src_image[idx + 0] = (x * 3) ^ (y * 3);
			src_image[idx + 1] = x ^ y;
			src_image[idx + 2] = (x * 7) ^ (y * 7);
			src_image[idx + 3] = 255;
			idx += 4;
		}
	}
	uint8_t* dst_image1 = new uint8_t[kSize * kSize * 4];
	uint8_t* dst_image2 = new uint8_t[kSize * kSize * 4];
	uint8_t* dst_image3 = new uint8_t[kSize * kSize * 4];
	uint8_t* dst_image4 = new uint8_t[kSize * kSize * 4];
	uint8_t* dst_image5 = new uint8_t[kSize * kSize * 4];
	float dt1 = test_assert_unroll::filter_image(kSize, src_image, dst_image1);
	float dt2 = test_noassert_unroll::filter_image(kSize, src_image, dst_image2);
	float dt3 = test_assert_loop::filter_image(kSize, src_image, dst_image3);
	float dt4 = test_noassert_loop::filter_image(kSize, src_image, dst_image4);
	float dt5 = test_raw::filter_image(kSize, src_image, dst_image5);
	printf("Time taken: %.1f %.1f %.1f %.1f %.1f ms\n", dt1, dt2, dt3, dt4, dt5);
	WriteTga("out-input.tga", kSize, kSize, (const uint32_t*)src_image);
	WriteTga("out-output1.tga", kSize, kSize, (const uint32_t*)dst_image1);
	WriteTga("out-output2.tga", kSize, kSize, (const uint32_t*)dst_image2);
	WriteTga("out-output3.tga", kSize, kSize, (const uint32_t*)dst_image3);
	WriteTga("out-output4.tga", kSize, kSize, (const uint32_t*)dst_image4);
	WriteTga("out-output5.tga", kSize, kSize, (const uint32_t*)dst_image5);
	delete[] src_image;
	delete[] dst_image1;
	delete[] dst_image2;
	delete[] dst_image3;
	delete[] dst_image4;
	delete[] dst_image5;

	return 0;
}
