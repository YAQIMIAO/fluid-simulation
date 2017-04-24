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
#if defined(__APPLE_CC__)
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif

#define IX(x, y, z) ((x) + (y) * N + (z) * N * N)

class Particles {
public:
    int size;
    float dt;
    float diff;
    float visc;
    float *s;
    float *density;

    float *Vx;
    float *Vy;
    float *Vz;

    float *Vx0;
    float *Vy0;
    float *Vz0;



    Particles();
    Particles(int size, int diffusion, int viscosity, float dt);
    void render() const;
    void step(){} // simulate one frame

    void freeParticles();

    void FluidCubeAddDensity(int x, int y, int z, float amount);

    void FluidCubeAddVelocity(int x, int y, int z, float amountX, float amountY, float amountZ);

    void set_bnd(int b, float *x, int N);

    void lin_solve(int b, float *x, float *x0, float a, float c, int iter, int N);

    void diffuse (int b, float *x, float *x0, float diff, float dt, int iter, int N);

    void project(float *velocX, float *velocY, float *velocZ, float *p, float *div, int iter, int N);

    void advect(int b, float *d, float *d0,  float *velocX, float *velocY, float *velocZ, float dt, int N);

    void FluidCubeStep();


private:
    struct Particle
    {
        glm::dvec3 p;
        glm::dvec3 v;
        glm::dvec3 v_last;
    };
    
    std::vector<Particle> particles;
};

#endif /* PARTICLES_H */

