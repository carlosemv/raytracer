#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Ray.h"

class Camera {
public:
	glm::vec3 origin;
	glm::vec3 lower_left_corner;
	glm::vec3 horizontal, vertical;

	Camera();
	Camera(glm::vec3 _lookfrom, glm::vec3 _lookat, 
		glm::vec3 _vup, float _vfov, float _aspect);
	Ray get_ray_to(float u, float v);
};

#endif