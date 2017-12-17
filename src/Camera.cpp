#include "Camera.h"

#include <cmath>

Camera::Camera() : Camera(glm::vec3(0,0,1), glm::vec3(0,0,-1), glm::vec3(0,1,0), 0.5, 1.0) {}

Camera::Camera(glm::vec3 _lookfrom, glm::vec3 _lookat, 
	glm::vec3 _vup, float _vfov, float _aspect)
{
	//vfov is top to bottom in (0,1)
	float tau = 6.283185;
	float theta = (tau * _vfov) / 2;
	float half_height = std::tan(theta / 2);
	float half_width = _aspect * half_height;

	glm::vec3 u, v, w;
	origin = _lookfrom;
	w = glm::normalize(_lookfrom - _lookat);
	u = glm::normalize(cross(_vup, w));
	v = cross(w, u);

	lower_left_corner = origin - half_width*u - half_height*v - w;
	horizontal = 2 * half_width * u;
	vertical = 2 * half_height * v;
}

Ray Camera::get_ray_to(float u, float v) { 
	glm::vec3 dir = lower_left_corner + u*horizontal + v*vertical - origin;
	return Ray(origin, dir); 
}