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

#define DENSITY 1000

class Particles {
    
    
    
private:
    struct Particle
    {
        Vector3D p;
        Vector3D last_p;
        Vector3D delta_p;
        Vector3D v;
        double lambda;
        vector<Particle *> neighbors;
    };
    
    
    // components
    vector<Particle> particles;
    
    // spatial map
    unordered_map<int, vector<Particle *> *> map;
    
    // gravity
    Vector3D g = Vector3D(0, -9.8, 0); // m per square s

    double hn;
    
    
public:
    // properties

    // render radius is how big the particles are
    double render_radius = 0.03;

    
    double cube_length;
    double bound; // bounding box - (- bound, - bound, - bound) to (bound, bound, bound)
    
    int N; // number of particles per side
    
    double d;
    double h;
    
    double initial_height;
    
    double rho_0 = 100; // initial density

    // ETA is a small relaxation parameter, I think it should be rho_0/20.0. I think it should be constant
    double ETA = 3; //relaxing factor

    double k = 0.0001;
    double exp_n = 4;
    double delta_q = 0.01;

    //Vector3D gradient_eta = Vector3D(0.001, 0.001, 0.001);

    int solverIterations = 10;

    
    Particles();
    Particles(int N, double height);
    Particles(double cube_length, double bound, int N, double d, double h);
    void render() const;
    int hash_position(Vector3D pos);
    void simulate(double frames_per_sec, double simulation_steps);// simulate one frame
    void find_neighbors(Particle &par);
    void build_spatial_map();
    int hash_to_key(Vector3D hash);
    void collision_handling(Particle &par);
    void boundary_check(Particle &par);
};

#endif /* PARTICLES_H */


