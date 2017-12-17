#include "Lambertian.h"

Lambertian::Lambertian(const glm::vec3& _a, std::mt19937& _g,
	std::uniform_real_distribution<float>& _d) :
Material(_g, _d), albedo(_a) {}

bool Lambertian::scatter(const Ray& _r_in, const HitRecord& _rec,
	glm::vec3& _attenuation, Ray& _scattered) const
{
	glm::vec3 target = _rec.point + _rec.normal + random_unit_vector();
	_scattered = Ray(_rec.point, target-_rec.point);
	_attenuation = albedo;
	return true;
	// Note we could just as well only scatter with some probability p
	// and have attenuation be albedo/p. Your choice.
}