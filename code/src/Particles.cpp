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


//****************************************************
// Constructor
//***************************************************

Particles::Particles() 
{
    this->cube_length = 1.0;
    this->bound = 1.0 - 0.05;
    this->N = 10;
    this->dt = 0.1;
    this->initial_height = 10.0;
    float d = 0.1;
    for(int x=0; x<N; x++)
    {
        for(int y=0; y<N; y++)
        {
            for(int z=0; z<N; z++)
            {
                Particle par;
                par.p = Vector3D((x+0.5-N*0.5)*d, (y+initial_height+0.5)*d-1.0, (z+0.5-N*0.5)*d);
                par.last_p = Vector3D((x+0.5-N*0.5)*d, (y+initial_height+0.5)*d-1.0, (z+0.5-N*0.5)*d);
                par.v = Vector3D(0, 0, 0);
                particles.push_back(par);
            }
        }
    }
    this->thickness = (particles[0].p - particles[1].p).norm();
}

Particles::Particles(double cube_length, double bound, int N, double d, double h) {
    this->cube_length = cube_length;
    this->bound = bound - 0.05;
    this->N = N;
    this->dt = d;
    this->initial_height = h;
    for(int x=0; x<N; x++)
    {
        for(int y=0; y<N; y++)
        {
            for(int z=0; z<N; z++)
            {
                Particle par;
                par.p = Vector3D((x+0.5-N*0.5)*d, (y+initial_height+0.5)*d-1.0, (z+0.5-N*0.5)*d);
                par.last_p = Vector3D((x+0.5-N*0.5)*d, (y+initial_height+0.5)*d-1.0, (z+0.5-N*0.5)*d);
                par.v = Vector3D(0, 0, 0);
                particles.push_back(par);
            }
        }
    }
    this->thickness = (particles[0].p - particles[1].p).norm();

}



//****************************************************
// A spatial map to help detect neighbor particles
//***************************************************

void Particles::build_spatial_map() {
    for (const auto &entry : map) {
        delete(entry.second);
    }

    map.clear();

    for (Particle &par: particles){
        float hash_value = hash_position(par.p);
        //cout<<"hash_value:"<<hash_value<<endl;
        if (map[hash_value] != NULL){
            map[hash_value]->push_back(&par);
        }else{
            std::vector<Particle *> * vec = new std::vector<Particle *>();
            vec->push_back(&par);
            map[hash_value] = vec;
        }
    }
    //cout<<map.size()<<endl;

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
    double max_y = -bound;
    double min_y = bound;

    for (Particle &par: particles){
        if (par.p.y > max_y){
            max_y = par.p.y;
        }
        if (par.p.y < min_y){
            min_y = par.p.y;
        }
    }

    // membership in some uniquely identified 3D box volume.
    float width = 2.0 * bound;
    float W = 3.0f * width / N;
    float height = (floor((max_y - min_y) * 100.0) + 1.0)/100.0;
    float H = 3.0f * height / N;
    //cout<<"W:"<<W<<endl;
    //cout<<"H:"<<H<<endl;

    float bucket_length_w = W;
    float bucket_length_h = H;


    int x = (int)(floor(((pos.x/ width) * W) / bucket_length_w));
    int y = (int)(floor(((pos.y/ height) * H) / bucket_length_h));
    int z = (int)(floor(((pos.z/ width) * W) / bucket_length_w));

    //cout<<pos<<endl;
    //cout<<x<<endl;
    //cout<<y<<endl;
    //cout<<z<<endl;
    int size = (int)floor((W * H * W) / (bucket_length_w * bucket_length_h * bucket_length_w));


    return hash_to_key(x, y, z, size);
}


//****************************************************
// Handling self-collision
//***************************************************


void Particles::self_collide(Particle &par, double simulation_steps) {
    float hash_value = hash_position(par.p);
    //TODO:



    if (map[hash_value] != NULL && map[hash_value]->size() > 1) {
        //cout<<"box with more than 1 item detected!"<<endl;
        //cout<<"box size: " <<map[hash_value]->size()<<endl;
        Vector3D correctionVs = Vector3D(0.0, 0.0, 0.0);
        int count = 0;
        for (Particle *particle: *(map[hash_value])){
            if (particle != &par){
                if ((particle->p - par.p).norm() < thickness){
                    double eta1 = (-1.0/1000.0) + ((double)rand()/(double) RAND_MAX) * (2.0 / 1000.0);
                    eta1 = clamp(eta1, -1.0/1000.0, 1.0/1000.0);
                    double eta2 = (-1.0/1000.0) + ((double)rand()/(double) RAND_MAX) * (2.0 / 1000.0);
                    eta2 = clamp(eta2, -1.0/1000.0, 1.0/1000.0);

                    Vector3D d = (par.last_p - particle->p).unit();
                    Vector3D new_p = particle->p + d * thickness;
                    Vector3D correctionV = new_p - par.p;
                    correctionV.x += eta1;
                    correctionV.z += eta2;
                    correctionVs += correctionV;
                    count++;
                }
            }
        }
        if (count != 0){
            Vector3D finalCorrectionV = (correctionVs / (double) count) / simulation_steps;
            par.p += finalCorrectionV;
        }

    }

}

void Particles::simulate(double frames_per_sec, double simulation_steps){
    // before simulate: build the spatial map

    double mass = pow(cube_length, 3) / pow(N, 3);
    double delta_t = 1.0f / frames_per_sec / simulation_steps;

    // falling according to gravity
    for (Particle &par: particles){
        Vector3D v = g * delta_t;
        Vector3D last = par.last_p;
        par.last_p = par.p;
        par.p = last + v * delta_t;
    }

    // self-collision - so that particles don't fall onto each other
    build_spatial_map();
    for (Particle &par: particles){
        self_collide(par, simulation_steps);
    }


    // stop falling when hits the tank
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


//*****************************
// Rendering method
//*****************************


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

