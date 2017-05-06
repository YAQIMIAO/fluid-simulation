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
    this->cube_length = 1.2;
    this->bound = 1.0;
    this->N = cube_length * 10;  // density defined
    this->d = cube_length / float(N);
    this->initial_height = 1.0;
    this->h = d * 1.5;
    this->hn = ceil(this->bound * 2.f / this->h);
    for(int x=0; x<N; x++)
    {
        for(int y=0; y<N; y++)
        {
            for(int z=0; z<N; z++)
            {
                Particle par;
                // Vector3D pos((x+0.5-N*0.5)*d, (y+initial_height+0.5)*d-1.0, (z+0.5-N*0.5)*d);
                Vector3D pos(-cube_length / 2.f + (x + .5) * this->d, 
                             -cube_length + this->initial_height + (y + .5) * this->d, 
                             -cube_length / 2.f + (z + .5) * this->d);
                par.p = pos;
                par.last_p = pos;
                par.v = Vector3D(0, 0, 0);
                particles.push_back(par);
            }
        }
    }

}

Particles::Particles(int N, double height)
{
    this->cube_length = N / 10.f;
    this->bound = 1.0;
    this->N = N;  // density defined
    this->d = cube_length / float(N);
    this->initial_height = height;
    for(int x=0; x<N; x++)
    {
        for(int y=0; y<N; y++)
        {
            for(int z=0; z<N; z++)
            {
                Particle par;
                // Vector3D pos((x+0.5-N*0.5)*d, (y+initial_height+0.5)*d-1.0, (z+0.5-N*0.5)*d);
                Vector3D pos(-cube_length / 2.f + (x + .5) * this->d, 
                             this->initial_height - cube_length + (y + .5) * this->d, 
                             -cube_length / 2.f + (z + .5) * this->d);
                par.p = pos;
                par.last_p = pos;
                par.v = Vector3D(0, 0, 0);
                particles.push_back(par);
            }
        }
    }
}

Particles::Particles(double cube_length, double bound, int N, double dist, double h) {
    this->cube_length = cube_length;
    this->bound = bound;
    this->N = N;
    this->d = dist;
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
        //cout<<par.p<<endl;
        int hash_value = hash_position(par.p);
        if (map[hash_value] != NULL){
            //cout<<"there is already a particle in this box"<<endl;
            map[hash_value]->push_back(&par);
            // if (map[hash_value]->size() > 1000) {
            //     cout << map[hash_value]->size() << endl;
            //     for (int i = 0; i < 3; ++i)
            //     {
            //         cout << map[hash_value]->at(i)->p << endl;
            //     }
            // }
        }else{
            //cout<<"there is no particle in this box"<<endl;
            std::vector<Particle *> * vec = new std::vector<Particle *>();
            vec->push_back(&par);
            map[hash_value] = vec;
        }
    }
}

int Particles::hash_to_key(Vector3D hash){
    int x = (int)floor(hash.x);
    int y = (int)floor(hash.y);
    int z = (int)floor(hash.z);
    //cout<<"hashkey is:"<<"("<<x<<","<<y<<","<<z<<")"<<endl;

    return x + z * (hn) + y * (hn * hn);
}

int Particles::hash_position(Vector3D pos) {

    Vector3D hash = pos / h;
    int key = hash_to_key(hash);
    //cout<<"key is:"<<key<<endl;
    return key;
}



//****************************************************
// Find particles that's within h distance away
//***************************************************


void Particles::find_neighbors(Particle &par){
    par.neighbors.clear();
    Vector3D hash = par.p / h;
    hash.x = floor(hash.x);
    hash.y = floor(hash.y);
    hash.z = floor(hash.z);

    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            for (int k = -1; k < 2; ++k)
            {
                int key = hash_to_key(hash + Vector3D(i, j, k));
                if (map[key] == NULL)
                    continue;
                for (std::vector<Particle *>::iterator iter = map[key]->begin(); iter != map[key]->end(); ++iter) {
                    if (*iter == &par)
                        continue;
                    // test dist, if ((*iter)->p - par.p).norm() < h, add neighbor to the list
                    if (((*iter)->p - par.p).norm() < h) {
                        par.neighbors.push_back((*iter));
                    }
                }
            }
        }
    }
  
}


// collision handling
void Particles::collision_handling(Particle &par){
    Vector3D delta_p = Vector3D();
    int count = 0;
    for (Particle * n: par.neighbors){
        double dist = (par.p - n->p).norm();
        Vector3D dir = (par.p - n->p).unit();
        if (dist < d){
            delta_p += dir * (h - dist);
            count++;
        }
    }

    if (count != 0){
        Vector3D correction = delta_p / 2.0/(double)count;
        par.p += correction;
    }
}

#define SURFACE_OFFSET 0.0001

// particles stop when it gets out of boundary
void Particles::boundary_check(Particle &par){

    /*

    double epsilon = d/2.0;
    double bou = bound - epsilon;

    Vector3D p0 = Vector3D(0.5, - bou, 0.5);
    Vector3D n0 = Vector3D(0, 1, 0);

    Vector3D p1 = Vector3D(-bou, 0.5, 0.5);
    Vector3D n1 = Vector3D(1, 0, 0);

    Vector3D p2 = Vector3D(bou, 0.5, 0.5);
    Vector3D n2 = Vector3D(-1, 0, 0);

    Vector3D p3 = Vector3D(0.5, 0.5, -bou);
    Vector3D n3 = Vector3D(0, 0, 1);

    Vector3D p4 = Vector3D(0.5, 0.5, bou);
    Vector3D n4 = Vector3D(0, 0, -1);


    Vector3D l0 = par.p;

    Vector3D d0 = n0 * (-1.0);
    Vector3D d1 = n1 * (-1.0);
    Vector3D d2 = n2 * (-1.0);
    Vector3D d3 = n3 * (-1.0);
    Vector3D d4 = n4 * (-1.0);

    bool b0 = dot(l0 - p0, n0) > 0.0;
    bool b1 = dot(l0 - p1, n1) > 0.0;
    bool b2 = dot(l0 - p2, n2) > 0.0;
    bool b3 = dot(l0 - p3, n3) > 0.0;
    bool b4 = dot(l0 - p4, n4) > 0.0;


    if (b0 && b1 && b2 && b3 && b4){
        return;
    }

    if (!b0 && dot(d0, n0) != 0.0){
        double t = dot((p0 - l0), n0) / (dot(d0, n0));
        Vector3D tangentP = l0 + t * d0;
        Vector3D correctionV = tangentP + SURFACE_OFFSET*n0 - par.last_p;
        par.p = par.last_p + correctionV;

    }
    if (!b1 && dot(d1, n1) != 0.0){
        double t = dot((p1 - l0), n1) / (dot(d1, n1));
        Vector3D tangentP = l0 + t * d1;
        Vector3D correctionV = tangentP + SURFACE_OFFSET*n1 - par.last_p;
        par.p = par.last_p + correctionV;

    }
    if (!b2 && dot(d2, n2) != 0.0){
        double t = dot((p2 - l0), n2) / (dot(d2, n2));
        Vector3D tangentP = l0 + t * d2;
        Vector3D correctionV = tangentP + SURFACE_OFFSET*n2 - par.last_p;
        par.p = par.last_p + correctionV;

    }
    if (!b3 && dot(d3, n3) != 0.0){
        double t = dot((p3 - l0), n3) / (dot(d3, n3));
        Vector3D tangentP = l0 + t * d3;
        Vector3D correctionV = tangentP + SURFACE_OFFSET*n3 - par.last_p;
        par.p = par.last_p + correctionV;

    }
    if (!b4 && dot(d4, n4) != 0.0){
        double t = dot((p4 - l0), n4) / (dot(d4, n4));
        Vector3D tangentP = l0 + t * d4;
        Vector3D correctionV = tangentP + SURFACE_OFFSET*n4 - par.last_p;
        par.p = par.last_p + correctionV;

    }
     */


    double epsilon = d/2.0;

    if (par.p.x <= -bound) {
        par.p.x = -bound + epsilon;
    }
    if (par.p.x >= bound) {
        par.p.x = bound - epsilon;
    }
    if (par.p.y <= -bound) {
        par.p.y = -bound + epsilon;
    }
    if (par.p.z <= -bound) {
        par.p.z = -bound + epsilon;
    }
    if (par.p.z >= bound) {
        par.p.z = bound - epsilon;
    }

}


double poly_6(double d, double h){
    if (d >= 0 && d <= h){
        return (315.0f / (64.0f * PI * pow(h, 9))) * pow((h * h - d * d), 3);
    }else{
        return 0.0;
    }
}



Vector3D gradient_w(Vector3D x){

    return x.unit();

}

Vector3D gradient_spiky(Vector3D pi, Vector3D pj, double h){
    
    Vector3D r = pi - pj;
    double dr = r.norm();
    if (dr > h || dr <= 0.0){
        return Vector3D();
    }
    
    double constant = -(45.0f/(PI * pow(h, 6))) * (h - dr) * (h - dr);
    return r.unit() * constant;
    
}


// rho_i is the density of i-th particle (sum of neighbor), rho_0 is the rest density
double C_i(double rho_i, double rho_0){
    return rho_i / rho_0  - 1.0;
}

//tensile
double sCorr(double k, double n, double delta_q, double h, double d){
    double component = poly_6(d, h)/poly_6(delta_q, h);
    return (-k) * pow(component, n);
    
}



void Particles::simulate(double frames_per_sec, double simulation_steps){
    //double h = d;

    double delta_t = 1.f / frames_per_sec / simulation_steps;

    while (simulation_steps > 0.0) {

        // NOTICE in this step, last_p is the real time p;
        // par.p is the predicted p
        // in the paper:
        // par.last_p is x_i
        // par.p is x_i*


        // falling according to gravity
        for (Particle &par: particles) {
            // calculate velocity
            Vector3D v = g * delta_t; // v = a*t
            par.v += v;
            // this is the predicted position with only external force
            par.p = par.last_p + v * delta_t;
        }

        // build spatial map according to the predicted p value
        build_spatial_map();

        // find neighbor particles
        for (Particle &par: particles) {
            find_neighbors(par);
            //print_out_self_and_neighbor(&par);
        }


        // Incompressibility
        /*   TODO: currently not working
         *   while iter < solverIterations do
              for all particles i do
                calculate λ_i
              end for
              for all particles i do
                calculate ∆p_i
                perform boundary and response
              end for
              for all particles i do
                update position x*_i ⇐ x*_i + ∆p_i
              end for
            end while
         */


        // entering a giant while loop - iterate solverIterations times
        // may want to make this global
        int iter = 0;
        while (iter < solverIterations) {

            // first for loop - calculate lambda
            for (Particle &par: particles) {

                // get current particle's density - rho_i
                double rho_i = 0.0;
                for (Particle *n: par.neighbors) {
                    rho_i += poly_6((par.p - n->p).norm(), h); // Poly6 kernel
                }
                // cout << rho_i<<endl;

                // we have rho_i and rho_0 now we can get the constraint
                double constraint_i = C_i(rho_i, rho_0);
                // cout<<constraint_i<<endl;


                // sum of gradient^2
                double sum_gradients = 0.0;
                // initiate gradient with repect to i
                Vector3D gradient_for_pi = Vector3D();
                for (Particle *n: par.neighbors) {
                    // calculate gradient with respect to j
                    Vector3D grad_j = gradient_spiky(par.p, n->p, h) / rho_0;

                    // sum add j^2
                    sum_gradients += grad_j.norm2();

                    // accumulate gradient with respect to i
                    gradient_for_pi += grad_j;
                }
                // sum add i^2
                sum_gradients += gradient_for_pi.norm2();

                // calculate lambda for par
                par.lambda = (-constraint_i / (sum_gradients + ETA));
            }

            // second and third for loop - calculate delta_p and update predicted p
            for (Particle &par: particles) {
                // for delta_p, it seems from the paper that it should be an attribute for particle
                // so although I didn't implement exactly like the paper did,
                // I still make it an attribute for now;



                par.delta_p = Vector3D();
                for (Particle *n: par.neighbors) {

                    //adds an artificial pressure
                    double scorr = sCorr(k, exp_n, delta_q * h, h, (par.p - n->p).norm());
                    par.delta_p += (par.lambda + n->lambda + scorr) * gradient_spiky(par.p, n->p, h);
                }
                par.delta_p /= rho_0;


                /*
                 * I originally added this to prevent too much "flying",
                 * not sure if it is useful for now:
                 * calculate delta_p's length, if it seems too bizarre,
                 * just ignore it for now
                 * maybe there should be a better limitation
                 */


                if (par.delta_p.norm() > this->h * 2.0) {
                    par.p += par.delta_p.unit() * this->h * 2.0;
                    //par.p += par.delta_p;
                } else {
                    par.p += par.delta_p;
                }

                // a particle collision handling here
                collision_handling(par);


                // perform boundary check
                boundary_check(par);
            }
            iter++;
        }


        /*   TODO:
         *   for all particles i do
              update velocity v_i ⇐ (1/∆t)(x*_i − x_i)
              apply vorticity confinement and XSPH viscosity
              update position x_i ⇐ x*_i
            end for
         */


        // vorticity and XSPH viscosity
        for (Particle &par: particles) {
            par.v = (par.p - par.last_p) / delta_t;
            //cout<<"par.v:"<<par.v<<endl;

            // apply vorticity

            // first calculate each particle's current vorticity
            // paper used omega, I'll use w here for simplification
            Vector3D w = Vector3D();
            for (Particle *n:par.neighbors) {
                Vector3D v_i = par.v;
                Vector3D v_j = n->v;
                Vector3D v_ij = v_j - v_i;
                Vector3D gradient = gradient_spiky(par.p, n->p, h);
                if (gradient.x !=0.0 && gradient.y != 0.0 && gradient.z!=0.0){
                    w += cross(v_ij, gradient);
                }
                //w += cross(v_ij, gradient);
            }
            if (w.x !=0.0 && w.y != 0.0 && w.z!=0.0){
                Vector3D eta = gradient_w(w);
                Vector3D N_vector = eta.unit();

                // since mass is 1, a = f/m, a = f
                double epsilon = 0.1;
                Vector3D a = epsilon * (cross(N_vector, w));
                par.v += a * delta_t;
                //cout<<"par.v:"<<par.v<<endl;
            }

            // apply viscosity
            Vector3D v_sum = Vector3D();
            for (Particle *n:par.neighbors) {
                Vector3D v_i = par.v;
                Vector3D v_j = n->v;
                Vector3D v_ij = v_j - v_i;
                double big_w = poly_6((par.p - n->p).norm(), h);
                v_sum += v_ij * big_w;
            }


            double c = 0.1;
            par.v += c * v_sum;


            // update last_p to this new p
            par.last_p = par.p;


        }

        simulation_steps -= 1;
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
        // I used last_p to render cos that is the real time position!
        glTranslatef(par.last_p.x, par.last_p.y, par.last_p.z);
        SolidSphere s = SolidSphere(render_radius);
        s.draw(par.p.x, par.p.y, par.p.z);
        glPopMatrix();
    }
    
    glPopAttrib();
}


