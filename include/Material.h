#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <random>
#include "Ray.h"
#include "Hitable.h"

class Material {
public:
	std::mt19937& gen;
	std::uniform_real_distribution<float>& dis;

	Material(std::mt19937& _g, std::uniform_real_distribution<float>& _d) : gen(_g), dis(_d) {}

	glm::vec3 random_unit_vector() const
	{
		glm::vec3 p;
		do {
			p = 2.0F * glm::vec3(dis(gen), dis(gen), dis(gen)) - 1.0F;
		} while (dot(p, p) >= 1.0);
		return p;
	}
	virtual bool scatter(const Ray& _r_in, const HitRecord& _rec,
		glm::vec3& _attenuation, Ray& _scattered) const = 0;
};

#endif