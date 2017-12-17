#ifndef __RAY_H__
#define __RAY_H__

#include <glm/glm.hpp>

class Ray {
public:
	glm::vec3 A, B;

	Ray() {}
	Ray(const glm::vec3& _a, const glm::vec3& _b) : A(_a), B(_b) {}
	glm::vec3 origin() const { return A; }
	glm::vec3 direction() const { return B; }
	glm::vec3 point_at(float _t) const { return A + (_t*B); }
};

#endif