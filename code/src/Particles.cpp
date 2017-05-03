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
    this->bound = 1.0;
    this->N = 10;
    this->d = cube_length / float(N);
    this->initial_height = 2.0;
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
    //build_spatial_map();
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
    //build_spatial_map();
    
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
        //cout<<"hash_value:"<<hash_value<<endl;
        
        par.neighbor_keys = neighbor_hash(par.p);
        par.neighbors = vector<Particle *>();
        //cout<<par.neighbors.size()<<endl;
        //cout<<"neighbor_keys.size():"<<par.neighbor_keys.size()<<endl;
        
        //cout<<"hash_value:"<<hash_value<<endl;
        
        if (map[hash_value] != NULL){
            //cout<<"there is already a particle in this box"<<endl;
            map[hash_value]->push_back(&par);
        }else{
            //cout<<"there is no particle in this box"<<endl;
            std::vector<Particle *> * vec = new std::vector<Particle *>();
            vec->push_back(&par);
            map[hash_value] = vec;
        }
    }
    
}


Vector3D Particles::find_min(){
    Vector3D min = Vector3D(999999, 999999, 999999);
    for (Particle &par: particles) {
        if (par.p.x < min.x){
            min.x = par.p.x;
        }
        if (par.p.y < min.y){
            min.y = par.p.y;
        }
        if (par.p.z < min.z){
            min.z = par.p.z;
        }
    }
    return min;
}

Vector3D Particles::find_max(){
    Vector3D max = Vector3D(-999999, -999999, -999999);
    for (Particle &par: particles) {
        if (par.p.x > max.x){
            max.x = par.p.x;
        }
        if (par.p.y > max.y){
            max.y = par.p.y;
        }
        if (par.p.z > max.z){
            max.z = par.p.z;
        }
    }
    return max;
}

int hash_to_key(int x, int y, int z, int N){
    if (x >= 0 && y >= 0 && z>= 0 && x < N && y < N && z < N){
        int ret = (x) + (y) * N + (z) * N * N;
        //cout<<ret<<endl;
        return ret;
    }else{
        return -1;
        
    }
}

int Particles::hash_position(Vector3D pos) {
    // h is the bucket length
    h = d * 1.5;
    
    // min is - bound; max is bound
    // X is how many bucket on each side
    int X = (2 * bound / h);
    //cout<<"X:"<<X<<endl;
    
    // assign (x, y, z)
    int x = (int)floor((pos.x + bound)/ h) - 1;
    int y = (int)floor((pos.y + bound)/ h) - 1;
    int z = (int)floor((pos.z + bound)/ h) - 1;
    
    //cout<<"hashkey is:"<<"("<<x<<","<<y<<","<<z<<")"<<endl;
    int key = hash_to_key(x, y, z, X);
    //cout<<"key is:"<<key<<endl;
    
    return key;
}



void push_back_valid_hash(vector<int> *ret, int hash){
    if (hash >= 0){
        ret->push_back(hash);
    }
}


vector<int> Particles::neighbor_hash(Vector3D pos) {
    vector<int> ret = vector<int>();
    // min is - bound; max is bound
    // X is how many bucket on each side
    int X = (2 * bound / h);
    //cout<<"X:"<<X<<endl;
    
    // assign (x, y, z)
    int x = (int)floor((pos.x + bound)/ h) - 1;
    int y = (int)floor((pos.y + bound)/ h) - 1;
    int z = (int)floor((pos.z + bound)/ h) - 1;
    
    
    //cout<<"("<<x<<", "<<y<<", "<< z<<")"<<endl;
    int size = X;
    
    // 26 neighbors
    
    push_back_valid_hash(&ret, hash_to_key(x - 1, y, z, size));
    push_back_valid_hash(&ret, hash_to_key(x - 1, y, z - 1, size));
    push_back_valid_hash(&ret, hash_to_key(x - 1, y, z + 1, size));
    push_back_valid_hash(&ret, hash_to_key(x - 1, y - 1, z, size));
    push_back_valid_hash(&ret, hash_to_key(x - 1, y - 1, z - 1, size));
    push_back_valid_hash(&ret, hash_to_key(x - 1, y - 1, z + 1, size));
    push_back_valid_hash(&ret, hash_to_key(x - 1, y + 1, z, size));
    push_back_valid_hash(&ret, hash_to_key(x - 1, y + 1, z - 1, size));
    push_back_valid_hash(&ret, hash_to_key(x - 1, y + 1, z + 1, size));
    
    // ret.push_back(hash_to_key(x, y, z, size));
    push_back_valid_hash(&ret, hash_to_key(x, y, z - 1, size));
    push_back_valid_hash(&ret, hash_to_key(x, y, z + 1, size));//
    push_back_valid_hash(&ret, hash_to_key(x, y - 1, z, size));
    push_back_valid_hash(&ret, hash_to_key(x, y - 1, z - 1, size));
    push_back_valid_hash(&ret, hash_to_key(x, y - 1, z + 1, size));
    push_back_valid_hash(&ret, hash_to_key(x, y + 1, z, size));//
    push_back_valid_hash(&ret, hash_to_key(x, y + 1, z - 1, size));
    push_back_valid_hash(&ret, hash_to_key(x, y + 1, z + 1, size));//
    
    
    push_back_valid_hash(&ret, hash_to_key(x + 1, y, z, size));//
    push_back_valid_hash(&ret, hash_to_key(x + 1, y, z - 1, size));
    push_back_valid_hash(&ret, hash_to_key(x + 1, y, z + 1, size));//
    push_back_valid_hash(&ret, hash_to_key(x + 1, y - 1, z, size));
    push_back_valid_hash(&ret, hash_to_key(x + 1, y - 1, z - 1, size));
    push_back_valid_hash(&ret, hash_to_key(x + 1, y - 1, z + 1, size));
    push_back_valid_hash(&ret, hash_to_key(x + 1, y + 1, z, size));//
    push_back_valid_hash(&ret, hash_to_key(x + 1, y + 1, z - 1, size));
    push_back_valid_hash(&ret, hash_to_key(x + 1, y + 1, z + 1, size));//
    //cout<<hash_to_key(x + 1, y + 1, z + 1, size)<<endl;
    
    
    return ret;
}




//****************************************************
// Find particles that's within h distance away
//***************************************************


void Particles::find_neighbors(Particle &par){
    par.neighbors = vector<Particle *>();
    int self_hash = hash_position(par.p);
    
    // 1. is there any close particles in my box that is within h distance away?
    if (map[self_hash] != NULL && map[self_hash]->size() > 1) {
        for (Particle *particle: *(map[self_hash])){
            if (particle != &par){
                double diff = (particle->p - par.p).norm();
                if (diff < h){
                    //cout<<"found neighbor in self bin"<<endl;
                    par.neighbors.push_back(particle);
                }
            }
        }
    }
    
    
    // 2. check at most 26 neighbor bins
    for (int key: par.neighbor_keys){
        if (map[key] != NULL) {
            for (Particle *particle: *(map[key])){
                double diff = (particle->p - par.p).norm();
                if (diff < h){
                    //cout<<"found neighbor in neighbor bins"<<endl;
                    par.neighbors.push_back(particle);
                }
            }
        }
    }
    
    //cout<<"how many neighbors? "<<par.neighbors.size()<<endl;
    
    
}


void Particles::print_out_self_and_neighbor(Particle *par){
    cout<<"self key is:"<<hash_position(par->p)<<endl;
    cout<<"self position is:"<<par->p<<endl;
    cout<<"neighbors num:"<<(par->neighbors).size()<<endl;
    cout<<"neighbors are:"<<endl;
    for (Particle *neighbor: par->neighbors){
        Vector3D pos = neighbor->p;
        cout<<"position: "<<pos<<endl;
    }
    
}

double poly_6(double d, double h){
    if (d >= 0 && d <= h){
        return (315.0f / (64.0f * PI * pow(h, 9))) * pow((h * h - d * d), 3);
    }else{
        return 0.0;
    }
}


double spiky(double d, double h){
    if (d >= 0 && d <= h){
        return (15.0f / (PI * pow(h, 6))) * pow((h - d), 3);
    }else{
        return 0.0;
    }
    
    
}

Vector3D gradient_spiky(Vector3D pi, Vector3D pj, double h){
    
    Vector3D r = pi - pj;
    double dr = r.norm();
    if (dr > h || dr <= 0.0){
        return Vector3D();
    }
    
    double constant = (45.0f/(PI * pow(h, 6))) * (h - dr) * (h - dr) / dr;
    return r * constant * (-1.0);
    
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
    // before simulate: build the spatial map
    //build_spatial_map();
    
    double delta_t = 1.0f / frames_per_sec / simulation_steps;
    
    // falling according to gravity
    for (Particle &par: particles){
        Vector3D v = g * delta_t;
        par.v += v;
        
        Vector3D last = par.last_p;
        par.last_p = par.p;
        
        // this is the predicted position
        par.p += v * delta_t;
        // cout<<par.p<<endl;
    }
    
    
    
    build_spatial_map();
    
    // find neighbor particles
    for (Particle &par: particles){
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
    
    double rho_0 = 300;//poly_6(d, h); // manually determined for now
    //cout << "rho_i:" << rho_0 << endl;
    //double h = d * 1.5;
    
    
    for (Particle &par: particles) {
        // get current particle's density - rho_i
        double rho_i = 0.0;
        
        for (Particle *n: par.neighbors) {
            rho_i += poly_6((par.p - n->p).norm(), h); // Poly6 kernel
        }
        
        double constraint_i = C_i(rho_i, rho_0);
        // cout<<constraint_i<<endl;
        
        
        
        double sum_gradients = 0.0;
        
        Vector3D gradient_for_pi = Vector3D();
        
        for (Particle *n: par.neighbors) {
            Vector3D grad_j = gradient_spiky(par.p, n->p, h);
            grad_j /= rho_0;
            
            sum_gradients += dot(grad_j, grad_j);
            
            
            gradient_for_pi += grad_j;
            
        }
        
        //cout << "rho_i:" << rho_i << endl;
        sum_gradients += dot(gradient_for_pi, gradient_for_pi);
        
        
        par.lamda = (-constraint_i / (sum_gradients + rho_0 / 20.0));
        
    }
    
    
    // delta_p
    for (Particle &par: particles) {
        Vector3D delta_p = Vector3D();
        for (Particle *n: par.neighbors) {
            //adds an artificial pressure
            double scorr, delta_q, k, exp_n;
            k = 0.0001;
            exp_n = 4;
            delta_q = 0.1 * h;
            scorr = sCorr(k, exp_n, delta_q, h, (par.p - n->p).norm());
            delta_p += (par.lamda + n->lamda + scorr) * gradient_spiky(par.p, n->p, h);
        }
        delta_p /= rho_0;
        //cout<<delta_p<<endl;
        if (delta_p.norm() > h){
            //par.p += delta_p.unit();
            //par.p += delta_p;
            
        }else {
            par.p += delta_p;
        }
    }
    
    
    
    
    /*   TODO:
     *   for all particles i do
     update velocity v_i ⇐ (1/∆t)(x*_i − x_i)
     apply vorticity confinement and XSPH viscosity
     update position x_i ⇐ x*_i
     end for
     */
    
    
    
    
    
    // stop falling when hits the tank
    
    for (Particle &par: particles) {
        if (par.p.x <= -bound) {
            par.p.x = -bound + 0.05;
        }
        if (par.p.x >= bound) {
            par.p.x = bound - 0.05;
        }
        if (par.p.y <= -bound) {
            par.p.y = -bound + 0.05;
        }
        if (par.p.z <= -bound) {
            par.p.z = -bound + 0.05;
        }
        if (par.p.z >= bound) {
            par.p.z = bound - 0.05;
        }
    }
    
    
    for (Particle &par: particles) {
        //par.last_p = par.p;
        
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

    float radius = this->d * .5f;
    
    for(const Particle &par : particles)
    {    
        glPushMatrix();
        glTranslatef(par.p.x, par.p.y, par.p.z);
        SolidSphere s = SolidSphere(radius);
        s.draw(par.p.x, par.p.y, par.p.z);
        glPopMatrix();
    }
    
    glPopAttrib();
}


