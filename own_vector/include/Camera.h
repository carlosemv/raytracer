#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Ray.h"

class Camera {
public:
	Vec3 origin;
	Vec3 lower_left_corner;
	Vec3 horizontal, vertical;

	Camera() : origin(Vec3(0.0, 0.0, 0.0)),
		lower_left_corner(Vec3(-2.0, -1.0, -1.0)),
		horizontal(Vec3(4.0, 0.0, 0.0)),
		vertical(Vec3(0.0, 2.0, 0.0)) {}
	Ray get_ray_to(float u, float v) { 
		Vec3 dir = lower_left_corner + u*horizontal + v*vertical;
		return Ray(origin, dir); 
	}

};

#endif