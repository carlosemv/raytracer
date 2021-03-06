#include <iostream>
#include <random>
#include <ctime>

#include "Camera.h"
#include "HitableList.h"
#include "Sphere.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis;

Vec3 random_unit_vector() {
	Vec3 p;
	do {
		p = 2 * Vec3(dis(gen), dis(gen), dis(gen)) - 1;
	} while (dot(p, p) >= 1.0);
	return p;
}

Vec3 color(const Ray& _ray, const Hitable& _world) 
{
	HitRecord record;
	float max = std::numeric_limits<float>::max();
	if (_world.hit(_ray, 0.0, max, record)) {
		Vec3 target = record.point + record.normal + random_unit_vector(); 
		return 0.5 * color(Ray(record.point, target-record.point), _world);
	}

	Vec3 blue = Vec3(0.5, 0.7, 1.0);
	Vec3 white = Vec3(1.0, 1.0, 1.0);

	Vec3 unit_direction = _ray.direction().unit_vector();
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * white + t * blue;
}

int main() 
{
	int width = 400;
	int height = 200;

	Camera cam;

	HitableList world;
	auto s1 = std::make_unique<Sphere>(Vec3(0, 0, -1), 0.5);
	auto s2 = std::make_unique<Sphere>(Vec3(0, -100.5, -1), 100);

	world.add(std::move(s1));
	world.add(std::move(s2));

	auto data = std::make_unique<unsigned char[]>(width*height*3);

	int samples = 100;

    std::chrono::duration <double> ray_time, color_time;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			Vec3 col;
			for (int s = 0; s < samples; ++s) {
			    auto start = std::chrono::steady_clock::now();
				
				float rightwardness = j + dis(gen);
				float upwardness = height - (i+1) + dis(gen);

				float u = rightwardness / float(width);
				float v = upwardness / float(height);
				
				Ray r = cam.get_ray_to(u, v);
				
				auto end = std::chrono::steady_clock::now();
				ray_time += end-start;

				start = std::chrono::steady_clock::now();
				col = col + color(r, world); // todo += v3
				end = std::chrono::steady_clock::now();

				color_time += end-start;
			}

			col = col / samples; // todo /= float
			col.make_RGB();

			int first_byte = 3 * ((width * i) + j);
			data[first_byte] = col.r();
			data[first_byte+1] = col.g();
			data[first_byte+2] = col.b();
		}
	}

    std::cout << "ray time: " << ray_time.count() << " seconds\n";
    std::cout << "color time: " << color_time.count() << " seconds\n";
    std::cout << "total: " << (ray_time + color_time).count() << " seconds\n";

	stbi_write_png("aaaaa.png", width, height, 3, data.get(), 0);

	return EXIT_SUCCESS;
}