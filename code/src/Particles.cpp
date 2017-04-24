/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particles.cpp
 * Author: swl
 * 
 * Created on April 15, 2016, 12:16 PM
 */

#include "Particles.h"
#include "SolidSphere.cpp"


Particles::Particles() 
{
    int nx = 10;
    int ny = 10;
    int nz = 10;
    float d = 0.1;
    for(int x=0; x<nx; x++)
    {
        for(int y=0; y<ny; y++)
        {
            for(int z=0; z<nz; z++)
            {
                Particle par;
                par.p = Vector3D((x+0.5-nx*0.5)*d, (y+0.5)*d-1.0, (z+0.5-nz*0.5)*d);
                par.last_p = Vector3D((x+0.5-N*0.5)*d, (y+0.5)*d-1.0, (z+0.5-N*0.5)*d);
                par.v = Vector3D(0, 0, 0);
                particles.push_back(par);
            }
        }
    }
}

Particles::Particles(double cube_length, double bound, int N, double d) {
    this->cube_length = cube_length;
    this->bound = bound - 0.05;
    this->N = N;
    this->dt = d;
    for(int x=0; x<N; x++)
    {
        for(int y=0; y<N; y++)
        {
            for(int z=0; z<N; z++)
            {
                Particle par;
                par.p = Vector3D((x+0.5-N*0.5)*d, (y+10.5)*d-1.0, (z+0.5-N*0.5)*d);
                par.last_p = Vector3D((x+0.5-N*0.5)*d, (y+10.5)*d-1.0, (z+0.5-N*0.5)*d);
                par.v = Vector3D(0, 0, 0);
                particles.push_back(par);
            }
        }
    }

}



// http://stackoverflow.com/questions/5928725/hashing-2d-3d-and-nd-vectors
// hash(x,y,z) = ( x p1 xor y p2 xor z p3) mod n
float hash_to_key(int x, int y, int z, int size){
    int p1 = 73856093;
    int p2 = 19349663;
    int p3 = 83492791;
    return ( (x * p1) xor (y * p2) xor (z * p3)) % size;
}


float Particles::hash_position(Vector3D pos) {
    // TODO (Part 4): Hash a 3D position into a unique float identifier that represents
    // membership in some uniquely identified 3D box volume.
    float width = 2.0 * bound;
    float W = 3.0f * width / N;
    // 0.06 * 0.06 * 0.06
    float bucket_length_w = (5.0 * 1.5 * dt/(2.0 * width)) * W;
    //float bucket_length_z = bucket_length_x;

    //float x = (1.0 + floor(((pos.x/ width) * W) / bucket_length_x)) * bucket_length_x;
    //float y = (1.0 + floor(((pos.y/ height) * H) / bucket_length_y)) * bucket_length_y;
    //float z = (1.0 + floor(((pos.z/ (2.0/1000.0)) * T) / bucket_length_z))* bucket_length_z;

    int x = (int)(floor(((pos.x/ width) * W) / bucket_length_w));
    int y = (int)(floor(((pos.y/ width) * W) / bucket_length_w));
    int z = (int)(floor(((pos.z/ width) * W) / bucket_length_w));
    //float z = x;
    //cout<<pos<<endl;
    //cout<<x<<endl;
    //cout<<y<<endl;
    //cout<<z<<endl;
    int size = (int)floor((W * W * W) / (bucket_length_w * bucket_length_w * bucket_length_w));


    return hash_to_key(x, y, z, size);
}







void Particles::self_collide(Particle &par, double simulation_steps) {
    float hash_value = hash_position(par.p);


}

void Particles::simulate(double frames_per_sec, double simulation_steps){
    double mass = pow(cube_length, 3) / pow(N, 3);
    double delta_t = 1.0f / frames_per_sec / simulation_steps;
    for (Particle &par: particles){
        Vector3D v = g * delta_t;
        par.v += v;
        par.last_p = par.p;
        par.p += v * dt;

    }


    for (Particle &par: particles){
        self_collide(par, simulation_steps);
    }


    // cannot run out of tank
    for (Particle &par: particles){
        if (par.p.x <= -bound){
            par.p.x = -bound;
        }
        if (par.p.x >= bound){
            par.p.x = bound;
        }
        if (par.p.y <= -bound){
            par.p.y = -bound;
        }
        if (par.p.z <= -bound){
            par.p.z = -bound;
        }
        if (par.p.z >= bound){
            par.p.z = bound;
        }

    }

}











void Particles::render() const
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };
    glShadeModel (GL_SMOOTH);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glColor3f(0.2, 0.5, 0.8);
    glColorMaterial(GL_FRONT, GL_SPECULAR);
    glColor3f(0.9, 0.9, 0.9);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor3f(0.2, 0.5, 0.8);
    
    for(const Particle &par : particles)
    {    
        
        glPushMatrix();
        glTranslatef(par.p.x, par.p.y, par.p.z);
        SolidSphere s = SolidSphere();
        s.draw(par.p.x, par.p.y, par.p.z);
        glPopMatrix();
    }
    
    glPopAttrib();
}

