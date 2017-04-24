/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particles.h
 * Author: swl
 *
 * Created on April 15, 2016, 12:16 PM
 */

#ifndef PARTICLES_H
#define PARTICLES_H

#include <glm/glm.hpp>
#include <vector>
#include <stdlib.h>
#include <iostream>
#if defined(__APPLE_CC__)
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif
#include <CGL/vector3D.h>

using namespace std;
using namespace CGL;

class Particles {



private:
    struct Particle
    {
        Vector3D p;
        Vector3D last_p;
        Vector3D v;
    };


    // components
    vector<Particle> particles;


public:
    // properties
    double cube_length;
    double bound; // (- bound, - bound, - bound) to (bound, bound, bound)
    int N; // number of particles per side
    double dt;


    Particles();
    Particles(double cube_length, double bound, int N, double d);
    void render() const;
    float hash_position(Vector3D pos);
    void simulate(double frames_per_sec, double simulation_steps);// simulate one frame
    void self_collide(Particle &par, double simulation_steps);
    Vector3D g = Vector3D(0, -9.8, 0); // m per square s


};

#endif /* PARTICLES_H */

