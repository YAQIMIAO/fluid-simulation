#include <vector>

#include "CGL/CGL.h"
#include "CGL/misc.h"
#include "particle.h"
#include "collision/collisionObject.h"

using namespace CGL;
using namespace std;

struct Fluid
{
	Fluid() {}
	Fluid(double side_leng, int num_side_points, double density);
	~Fluid();

	void initCube(double side_leng, int num_side_points, double density);
	void simulate(double delta_t, double simulation_steps,
	              vector<Vector3D> external_accelerations,
	              vector<CollisionObject *> *collision_objects);
	void reset();
	void render(GLShader &shader);
	void self_collide(Particle &p, double delta_t);

	std::vector<Particle> particles;
	double side_leng;
	int num_side_points;
};