#include "iostream"
#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../clothSimulator.h"
#include "plane.h"

using namespace std;
using namespace CGL;

#define SURFACE_OFFSET 0.0001

void Plane::collide(PointMass &pm) {
  // TODO (Part 3): Handle collisions with planes.
  if (dot(pm.last_position - this->point, this->normal) * dot(pm.position - this->point, this->normal) > 0) {
    return;
  }
  Vector3D tan_point = pm.position - dot(pm.position - this->point, this->normal) * this->normal;
  float cos_theta = dot(pm.last_position - this->point, this->normal);
  Vector3D normal_side = this->normal;
  if (cos_theta < 0) {
    normal_side = -1.f * this->normal;
  } else if (cos_theta == 0) {
    pm.position = tan_point;
    return;
  }
  Vector3D correction = tan_point + SURFACE_OFFSET * normal_side  - pm.last_position;
  pm.position = pm.last_position + (1.f - friction) * correction;
}

void Plane::render(GLShader &shader) {
  nanogui::Color color(0.7f, 0.7f, 0.7f, 1.0f);

  Vector3f sPoint(point.x, point.y, point.z);
  Vector3f sNormal(normal.x, normal.y, normal.z);
  Vector3f sParallel(normal.y - normal.z, normal.z - normal.x,
                     normal.x - normal.y);
  sParallel.normalize();
  Vector3f sCross = sNormal.cross(sParallel);

  MatrixXf positions(3, 4);
  MatrixXf normals(3, 4);

  positions.col(0) << sPoint + 2 * (sCross + sParallel);
  positions.col(1) << sPoint + 2 * (sCross - sParallel);
  positions.col(2) << sPoint + 2 * (-sCross + sParallel);
  positions.col(3) << sPoint + 2 * (-sCross - sParallel);

  normals.col(0) << sNormal;
  normals.col(1) << sNormal;
  normals.col(2) << sNormal;
  normals.col(3) << sNormal;

  if (shader.uniform("in_color", false) != -1) {
    shader.setUniform("in_color", color);
  }
  shader.uploadAttrib("in_position", positions);
  shader.uploadAttrib("in_normal", normals);

  shader.drawArray(GL_TRIANGLE_STRIP, 0, 4);
}
