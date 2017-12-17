#ifndef __LAMBERTIAN_H__
#define __LAMBERTIAN_H__

#include <random>
#include "Material.h"

class Lambertian : public Material {
public:
	glm::vec3 albedo;
	
	Lambertian(const glm::vec3& _a, std::mt19937& _g,
		std::uniform_real_distribution<float>& _d);

	virtual bool scatter(const Ray& _r_in, const HitRecord& _rec,
		glm::vec3& _attenuation, Ray& _scattered) const;
};

#endif