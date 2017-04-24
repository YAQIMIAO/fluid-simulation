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
                par.p = glm::dvec3((x+0.5-nx*0.5)*d, (y+0.5)*d-1.0, (z+0.5-nz*0.5)*d);
                particles.push_back(par);
            }
        }
    }
}

Particles::Particles(int size, int diffusion, int viscosity, float dt)
{

    int N = size;
    for(int x=0; x<N; x++)
    {
        for(int y=0; y<N; y++)
        {
            for(int z=0; z<N; z++)
            {
                Particle par;
                par.p = glm::dvec3((x+0.5-N*0.5)*dt, (y+0.5)*dt-1.0, (z+0.5-N*0.5)*dt);
                particles.push_back(par);
            }
        }
    }

    this->size = size;
    this->dt = dt;
    this->diff = diffusion;
    this->visc = viscosity;

    this->s = (float *)calloc(N * N * N, sizeof(float));
    this->density = (float *)calloc(N * N * N, sizeof(float));

    this->Vx = (float *)calloc(N * N * N, sizeof(float));
    this->Vy = (float *)calloc(N * N * N, sizeof(float));
    this->Vz = (float *)calloc(N * N * N, sizeof(float));

    this->Vx0 = (float *)calloc(N * N * N, sizeof(float));
    this->Vy0 = (float *)calloc(N * N * N, sizeof(float));
    this->Vz0 = (float *)calloc(N * N * N, sizeof(float));
}


void Particles::freeParticles()
{
    free(this->s);
    free(this->density);

    free(this->Vx);
    free(this->Vy);
    free(this->Vz);

    free(this->Vx0);
    free(this->Vy0);
    free(this->Vz0);
}



void Particles::FluidCubeAddDensity(int x, int y, int z, float amount)
{
    int N = size;
    density[IX(x, y, z)] += amount;
}


void Particles::FluidCubeAddVelocity(int x, int y, int z, float amountX, float amountY, float amountZ)
{
    int N = size;
    int index = IX(x, y, z);

    Vx[index] += amountX;
    Vy[index] += amountY;
    Vz[index] += amountZ;
}


void Particles::set_bnd(int b, float *x, int N)
{
    for(int j = 1; j < N - 1; j++) {
        for(int i = 1; i < N - 1; i++) {
            x[IX(i, j, 0  )] = b == 3 ? -x[IX(i, j, 1  )] : x[IX(i, j, 1  )];
            x[IX(i, j, N-1)] = b == 3 ? -x[IX(i, j, N-2)] : x[IX(i, j, N-2)];
        }
    }
    for(int k = 1; k < N - 1; k++) {
        for(int i = 1; i < N - 1; i++) {
            x[IX(i, 0  , k)] = b == 2 ? -x[IX(i, 1  , k)] : x[IX(i, 1  , k)];
            x[IX(i, N-1, k)] = b == 2 ? -x[IX(i, N-2, k)] : x[IX(i, N-2, k)];
        }
    }
    for(int k = 1; k < N - 1; k++) {
        for(int j = 1; j < N - 1; j++) {
            x[IX(0  , j, k)] = b == 1 ? -x[IX(1  , j, k)] : x[IX(1  , j, k)];
            x[IX(N-1, j, k)] = b == 1 ? -x[IX(N-2, j, k)] : x[IX(N-2, j, k)];
        }
    }

    x[IX(0, 0, 0)]       = 0.33f * (x[IX(1, 0, 0)]
                                    + x[IX(0, 1, 0)]
                                    + x[IX(0, 0, 1)]);
    x[IX(0, N-1, 0)]     = 0.33f * (x[IX(1, N-1, 0)]
                                    + x[IX(0, N-2, 0)]
                                    + x[IX(0, N-1, 1)]);
    x[IX(0, 0, N-1)]     = 0.33f * (x[IX(1, 0, N-1)]
                                    + x[IX(0, 1, N-1)]
                                    + x[IX(0, 0, N)]);
    x[IX(0, N-1, N-1)]   = 0.33f * (x[IX(1, N-1, N-1)]
                                    + x[IX(0, N-2, N-1)]
                                    + x[IX(0, N-1, N-2)]);
    x[IX(N-1, 0, 0)]     = 0.33f * (x[IX(N-2, 0, 0)]
                                    + x[IX(N-1, 1, 0)]
                                    + x[IX(N-1, 0, 1)]);
    x[IX(N-1, N-1, 0)]   = 0.33f * (x[IX(N-2, N-1, 0)]
                                    + x[IX(N-1, N-2, 0)]
                                    + x[IX(N-1, N-1, 1)]);
    x[IX(N-1, 0, N-1)]   = 0.33f * (x[IX(N-2, 0, N-1)]
                                    + x[IX(N-1, 1, N-1)]
                                    + x[IX(N-1, 0, N-2)]);
    x[IX(N-1, N-1, N-1)] = 0.33f * (x[IX(N-2, N-1, N-1)]
                                    + x[IX(N-1, N-2, N-1)]
                                    + x[IX(N-1, N-1, N-2)]);
}


void Particles::lin_solve(int b, float *x, float *x0, float a, float c, int iter, int N)
{
    float cRecip = 1.0 / c;
    for (int k = 0; k < iter; k++) {
        for (int m = 1; m < N - 1; m++) {
            for (int j = 1; j < N - 1; j++) {
                for (int i = 1; i < N - 1; i++) {
                    x[IX(i, j, m)] =
                            (x0[IX(i, j, m)]
                             + a*(    x[IX(i+1, j  , m  )]
                                      +x[IX(i-1, j  , m  )]
                                      +x[IX(i  , j+1, m  )]
                                      +x[IX(i  , j-1, m  )]
                                      +x[IX(i  , j  , m+1)]
                                      +x[IX(i  , j  , m-1)]
                            )) * cRecip;
                }
            }
        }
        set_bnd(b, x, N);
    }
}

void Particles::diffuse (int b, float *x, float *x0, float diff, float dt, int iter, int N)
{
    float a = dt * diff * (N - 2) * (N - 2);
    lin_solve(b, x, x0, a, 1 + 6 * a, iter, N);
}


void Particles::project(float *velocX, float *velocY, float *velocZ, float *p, float *div, int iter, int N)
{
    for (int k = 1; k < N - 1; k++) {
        for (int j = 1; j < N - 1; j++) {
            for (int i = 1; i < N - 1; i++) {
                div[IX(i, j, k)] = -0.5f*(
                        velocX[IX(i+1, j  , k  )]
                        -velocX[IX(i-1, j  , k  )]
                        +velocY[IX(i  , j+1, k  )]
                        -velocY[IX(i  , j-1, k  )]
                        +velocZ[IX(i  , j  , k+1)]
                        -velocZ[IX(i  , j  , k-1)]
                )/N;
                p[IX(i, j, k)] = 0;
            }
        }
    }
    set_bnd(0, div, N);
    set_bnd(0, p, N);
    lin_solve(0, p, div, 1, 6, iter, N);

    for (int k = 1; k < N - 1; k++) {
        for (int j = 1; j < N - 1; j++) {
            for (int i = 1; i < N - 1; i++) {
                velocX[IX(i, j, k)] -= 0.5f * (  p[IX(i+1, j, k)]
                                                 -p[IX(i-1, j, k)]) * N;
                velocY[IX(i, j, k)] -= 0.5f * (  p[IX(i, j+1, k)]
                                                 -p[IX(i, j-1, k)]) * N;
                velocZ[IX(i, j, k)] -= 0.5f * (  p[IX(i, j, k+1)]
                                                 -p[IX(i, j, k-1)]) * N;
            }
        }
    }
    set_bnd(1, velocX, N);
    set_bnd(2, velocY, N);
    set_bnd(3, velocZ, N);
}


void Particles::advect(int b, float *d, float *d0,  float *velocX, float *velocY, float *velocZ, float dt, int N)
{
    float i0, i1, j0, j1, k0, k1;

    float dtx = dt * (N - 2);
    float dty = dt * (N - 2);
    float dtz = dt * (N - 2);

    float s0, s1, t0, t1, u0, u1;
    float tmp1, tmp2, tmp3, x, y, z;

    float Nfloat = N;
    float ifloat, jfloat, kfloat;
    int i, j, k;

    for(k = 1, kfloat = 1; k < N - 1; k++, kfloat++) {
        for(j = 1, jfloat = 1; j < N - 1; j++, jfloat++) {
            for(i = 1, ifloat = 1; i < N - 1; i++, ifloat++) {
                tmp1 = dtx * velocX[IX(i, j, k)];
                tmp2 = dty * velocY[IX(i, j, k)];
                tmp3 = dtz * velocZ[IX(i, j, k)];
                x    = ifloat - tmp1;
                y    = jfloat - tmp2;
                z    = kfloat - tmp3;

                if(x < 0.5f) x = 0.5f;
                if(x > Nfloat + 0.5f) x = Nfloat + 0.5f;
                i0 = floorf(x);
                i1 = i0 + 1.0f;
                if(y < 0.5f) y = 0.5f;
                if(y > Nfloat + 0.5f) y = Nfloat + 0.5f;
                j0 = floorf(y);
                j1 = j0 + 1.0f;
                if(z < 0.5f) z = 0.5f;
                if(z > Nfloat + 0.5f) z = Nfloat + 0.5f;
                k0 = floorf(z);
                k1 = k0 + 1.0f;

                s1 = x - i0;
                s0 = 1.0f - s1;
                t1 = y - j0;
                t0 = 1.0f - t1;
                u1 = z - k0;
                u0 = 1.0f - u1;

                int i0i = i0;
                int i1i = i1;
                int j0i = j0;
                int j1i = j1;
                int k0i = k0;
                int k1i = k1;

                d[IX(i, j, k)] =

                        s0 * ( t0 * (u0 * d0[IX(i0i, j0i, k0i)]
                                     +u1 * d0[IX(i0i, j0i, k1i)])
                               +( t1 * (u0 * d0[IX(i0i, j1i, k0i)]
                                        +u1 * d0[IX(i0i, j1i, k1i)])))
                        +s1 * ( t0 * (u0 * d0[IX(i1i, j0i, k0i)]
                                      +u1 * d0[IX(i1i, j0i, k1i)])
                                +( t1 * (u0 * d0[IX(i1i, j1i, k0i)]
                                         +u1 * d0[IX(i1i, j1i, k1i)])));
            }
        }
    }
    set_bnd(b, d, N);
}



void Particles::FluidCubeStep()
{
    /*
    int N          = this->size;
    float visc     = this->visc;
    float diff     = this->diff;
    float dt       = this->dt;
    float *Vx      = this->Vx;
    float *Vy      = this->Vy;
    float *Vz      = this->Vz;
    float *Vx0     = this->Vx0;
    float *Vy0     = this->Vy0;
    float *Vz0     = this->Vz0;
    float *s       = this->s;
    float *density = this->density;
     */
    int N          = this->size;
    diffuse(1, Vx0, Vx, visc, dt, 4, N);
    diffuse(2, Vy0, Vy, visc, dt, 4, N);
    diffuse(3, Vz0, Vz, visc, dt, 4, N);

    project(Vx0, Vy0, Vz0, Vx, Vy, 4, N);

    advect(1, Vx, Vx0, Vx0, Vy0, Vz0, dt, N);
    advect(2, Vy, Vy0, Vx0, Vy0, Vz0, dt, N);
    advect(3, Vz, Vz0, Vx0, Vy0, Vz0, dt, N);

    project(Vx, Vy, Vz, Vx0, Vy0, 4, N);

    diffuse(0, s, density, diff, dt, 4, N);
    advect(0, density, s, Vx, Vy, Vz, dt, N);

    for(int x=0; x<N; x++)
    {
        for(int y=0; y<N; y++)
        {
            for(int z=0; z<N; z++)
            {
                int ind = IX(x, y, z);
                particles[ind].p = glm::dvec3(Vx[ind], Vy[ind], Vz[ind]);
            }
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

