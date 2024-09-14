
#include "test_math_vector.h"
#include "test_filter.h"
#include <stdio.h>
#include <chrono>

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
	const int kSize = 512;
	uchar4* src_image = new uchar4[kSize * kSize];
	uchar4* dst_image = new uchar4[kSize * kSize];
	int idx = 0;
	for (int y = 0; y < kSize; y++)
	{
		for (int x = 0; x < kSize; x++)
		{
			uchar4 pix;
			pix.x = (x * 3) ^ (y * 3);
			pix.y = x ^ y;
			pix.z = (x * 7) ^ (y * 7);
			pix.w = 255;
			src_image[idx++] = pix;
		}
	}
	float dt = filter_image(kSize, src_image, dst_image);
	printf("Time taken: %.1f ms\n", dt);
	WriteTga("out-input.tga", kSize, kSize, (const uint32_t*)src_image);
	WriteTga("out-output.tga", kSize, kSize, (const uint32_t*)dst_image);
	delete[] src_image;
	delete[] dst_image;

	return 0;
}
