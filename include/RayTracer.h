#ifndef __RAY_TRACER_H__
#define __RAY_TRACER_H__

#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <glm/glm.hpp>
#include <boost/program_options.hpp>

#include "Camera.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Lambertian.h"
#include "Metal.h"

class RayTracer {
public:
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<float> dis;

	int width, height;
	int samples, max_depth;

	Camera cam;

	HitableList world;

	std::unique_ptr<unsigned char[]> data;

	RayTracer() : gen(rd()) {}

	glm::vec3 color(const Ray& _ray, int depth) const;
	void set_options(std::string config_file);
	void run();
	void write_image(std::string file_name) const;
	glm::vec3 init_vec3(std::string _values) const;
};

#endif