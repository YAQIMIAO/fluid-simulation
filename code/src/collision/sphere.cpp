#include <nanogui/nanogui.h>

#include "../misc/sphere_drawing.h"
#include "sphere.h"

using namespace nanogui;
using namespace CGL;

void Sphere::collide(Particle &p) {
  // TODO (Part 3): Handle collisions with spheres.
	// if ((pm.position - this->origin).norm() >= this->radius) {
	// 	return;
	// }
	// Vector3D tan_point = this->origin + (pm.position - this->origin).unit() * this->radius;
	// Vector3D correction = tan_point - pm.last_position;
	// pm.position = pm.last_position + correction * (1 - friction);
}

void Sphere::render(GLShader &shader) {
  // We decrease the radius here so flat triangles don't behave strangely
  // and intersect with the sphere when rendered
  Misc::draw_sphere(shader, origin, radius * 0.92);
}
