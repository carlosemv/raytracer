#ifndef __METAL_H__
#define __METAL_H__

#include "Material.h"

class Metal : public Material {
public:
	glm::vec3 albedo;
	float fuzz;

	Metal(const glm::vec3& _a, float _f, std::mt19937& _g,
		std::uniform_real_distribution<float>& _d);

	glm::vec3 reflect(const glm::vec3& _v, const glm::vec3& _n) const;
	virtual bool scatter(const Ray& _r_in, const HitRecord& _rec,
		glm::vec3& _attenuation, Ray& _scattered) const;
};

#endif