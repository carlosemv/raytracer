#include <iostream>
#include "Vec3.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main()
{
	int width = 600;
	int height = 300;

	unsigned char *data = new unsigned char [width*height*3];

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			float r = float(j) / float(width);
			float g = float(height-i-1) / float(height);
			float b = 0.2;

			Vec3 p(r, g, b);
			p.make_RGB();

			int first_byte = 3 * ((width * i) + j);
			data[first_byte] = p.r();
			data[first_byte+1] = p.g();
			data[first_byte+2] = p.b();
		}
	}

	stbi_write_png("aaaaa.png", width, height, 3, data, 0);
	delete[] data;

	return EXIT_SUCCESS;
}