#include <iostream>
#include "Vec3.h"
#include "Ray.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Vec3 color(const Ray& r) {
	Vec3 unit_direction = r.direction().unit_vector(); // -1 to 1
	float t = 0.5*(unit_direction.y() + 1.0); // 0 to 1

	Vec3 blue = Vec3(0.5, 0.7, 1.0);
	Vec3 white = Vec3(1.0, 1.0, 1.0);
	return (1.0-t)*white + t*blue; // linear interpolation
}

int main()
{
	int width = 600;
	int height = 300;
	unsigned char *data = new unsigned char [width*height*3];

	Vec3 lower_left_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			float u = float(j) / float(width);
			float v = float(height-i-1) / float(height);
			Vec3 dir = lower_left_corner + u*horizontal + v*vertical;
			Ray r(origin, dir);

			Vec3 col = color(r);
			col.make_RGB();

			int first_byte = 3 * ((width * i) + j);
			data[first_byte] = col.r();
			data[first_byte+1] = col.g();
			data[first_byte+2] = col.b();
		}
	}

	stbi_write_png("aaaaa.png", width, height, 3, data, 0);
	delete[] data;

	return EXIT_SUCCESS;
}