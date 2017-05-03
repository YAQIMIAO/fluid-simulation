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
#include <unordered_set>
#include <unordered_map>
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
        Vector3D gradient_sum;
        double lamda;
        vector<int> neighbor_keys;
        vector<Particle *> neighbors;


    };


    // components
    vector<Particle> particles;

    // spatial map
    unordered_map<int, vector<Particle *> *> map;

    // gravity
    Vector3D g = Vector3D(0, -9.8, 0); // m per square s


public:
    // properties
    double ETA = 0.000001; //relaxing factor

    double cube_length;
    double bound; // bounding box - (- bound, - bound, - bound) to (bound, bound, bound)

    int N; // number of particles per side

    double d;
    double h;

    double initial_height;

    double rho_0; // initial density

    Particles();
    Particles(double cube_length, double bound, int N, double d, double h);
    void render() const;
    int hash_position(Vector3D pos);
    void simulate(double frames_per_sec, double simulation_steps);// simulate one frame
    void find_neighbors(Particle &par);
    void print_out_self_and_neighbor(Particle *par);

    Vector3D find_min();
    Vector3D find_max();

    void build_spatial_map();

    vector<int> neighbor_hash(Vector3D pos);

};

#endif /* PARTICLES_H */

