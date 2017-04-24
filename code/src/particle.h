#include "CGL/CGL.h"
#include "CGL/misc.h"
#include "CGL/vector3D.h"
#include "misc/sphere_drawing.h"

using namespace CGL;

struct Particle
{
public:
	virtual void render(GLShader &shader) = 0;
 	virtual void collide(PointMass &pm) = 0;
	Particle(const Vector3D &position)
		: start_position(position), position(position), last_position(position) {}
	Vector3D velocity(double delta_t) {
		return (position - last_position) / delta_t;
	}
	void render(GLShader &shader) {
		Misc::draw_sphere(shader, position, radius * 0.92);
	}

	double radius;
	double density;
	Vector3D start_position;
	Vector3D position;
	Vector3D last_position;
	Vector3D forces;
};