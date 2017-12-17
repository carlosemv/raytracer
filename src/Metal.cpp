#include "Metal.h"
#include <iostream>

Metal::Metal(const glm::vec3& _a, float _f, std::mt19937& _g,
	std::uniform_real_distribution<float>& _d) : 
Material(_g, _d), albedo(_a), fuzz(_f) {}

glm::vec3 Metal::reflect(const glm::vec3& _v, const glm::vec3& _n) const
{
	// _v + 2B  (B = -dot(_v, _n) * _n)
	return _v - 2.0F * dot(_v, _n) * _n;
}

bool Metal::scatter(const Ray& _r_in, const HitRecord& _rec,
	glm::vec3& _attenuation, Ray& _scattered) const
{
	glm::vec3 reflected = reflect(_r_in.direction(), _rec.normal);
	if (fuzz > 0)
		_scattered = Ray(_rec.point, reflected + fuzz*random_unit_vector());
	else
		_scattered = Ray(_rec.point, reflected);

	_attenuation = albedo;
	// true when not refracted
	return (dot(_scattered.direction(), _rec.normal) > 0);
}