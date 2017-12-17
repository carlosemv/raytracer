#include <iostream>
#include "Vec3.h"
#include "Ray.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

bool hits_sphere(const Ray& _r, const Vec3& _center, float _radius) {
	/* 
	 * Ray : A + t*B	
	 * dot(ray(t) - center, ray(t) - center) = r2
	 * dot(A + t*B - C, A + t*B - C) = r2
	 * t*t*dot(B, B) + 2*t*dot(A-C, B) + dot(A-C, A-C) - r2 = 0
	 */

	Vec3 ac = _r.origin() - _center; // A - C
	float a = dot(_r.direction(), _r.direction()); // dot(B, B)
	float b = 2.0*dot(ac, _r.direction()); // 2*dot(A-C, B)
	float c = dot(ac, ac) - _radius*_radius;

	float discriminant = b*b - 4*a*c;
	return (discriminant >= 0);
}

Vec3 color(const Ray& _ray) {
	Vec3 blue = Vec3(0.5, 0.7, 1.0);
	Vec3 white = Vec3(1.0, 1.0, 1.0);
	Vec3 red = Vec3(0.5, 0.0, 0.0);

	Vec3 sphere_center = Vec3(0,0,-1);
	float sphere_radius = 0.5;

	if (hits_sphere(_ray, sphere_center, sphere_radius))
		return red;

	Vec3 unit_direction = _ray.direction().unit_vector();
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)*white + t*blue;
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