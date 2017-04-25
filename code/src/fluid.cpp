#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "fluid.h"
#include "collision/plane.h"
#include "collision/sphere.h"

using namespace std;

Fluid::Fluid(double side_leng, int num_side_points, double density) {
	this->side_leng = side_leng;
	this->num_side_points = num_side_points;
	initCube(side_leng, num_side_points, density);
}

Fluid::~Fluid() {
	particles.clear();
}

void Fluid::initCube(double side_leng, int num_side_points, double density) {
	// TODO (***)
}

void Fluid::simulate(double delta_t, double simulation_steps,
	              	 vector<Vector3D> external_accelerations,
	              	 vector<CollisionObject *> *collision_objects) {
	double mass = pow(side_leng, 3.f) / pow(num_side_points, 3.f);

	// TODO: Fluid Dynamics

}

void Fluid::reset() {
	Particle *p = &particles[0];
	for (int i = 0; i < particles.size(); i++) {
		p->position = p->start_position;
		p->last_position = p->start_position;
		p++;
	}
}

void Fluid::render(GLShader &shader) {
	// TODO: draw particles (***)
	for (Particle &p : particles) {
		p.render(shader);
	}
}

void Fluid::self_collide(Particle &p, double delta_t) {
	// TODO
}