	
# Final Report

## Team Members

Yimin He

Yaqi Miao


## Abstract

In this project, we build a fluid simulation program using Position Based Fluids method. We firstly apply newton’s laws on particles, then correct to require incompressibility of fluid (requiring constant density of particles), then correct the constant density with an additional repulsive (tensile) term between particles (because the constant density term tends to produce clumps of particles). Finally, the using particles apparently leads to energy loss - the particles just settle down too quickly, so we use a vorticity calculation as a heuristic to add new energy into the system (base the amount of new force at that location on that location’s vorticity, which apparently makes sense for fluids), and in the end we attempt to include a viscosity term to introduce some clumpiness to the velocities, so that the fluid appears to move more like a whole and not like separate bouncing particles.


## Technical approach

### A 1-2 page summary of your technical approach, techniques used, algorithms implemented, etc. (use references to papers or other resources for further detail). Highlight how your approach varied from the references used (did you implement a subset, or did you change or enhance anything), the unique decisions you made and why.

summary




### A description of problems encountered and how you tackled them.

### A description of lessons learned.



## Results
	
Your final images, animations, video of your system (whichever is relevant). You can include results that you think show off what you built but that you did not have time to go over on presentation day.

1. Final images:
![alt text](images/1.png)
![alt text](images/2.png)
![alt text](images/3.png)
![alt text](images/4.png)
![alt text](images/5.png)

2. Final video:




## References

1. (Largely inspired by) Evan Wallace’s WebGL Water Simulation project, https://www.chromeexperiments.com/experiment/webgl-water-simulation

2. Position Based Fluid, http://mmacklin.com/pbf_sig_preprint.pdf

3. Fast Water Simulation for Games Using Height Fields, http://matthias-mueller-fischer.ch/talks/GDC2008.pdf

4. Fluid Simulation for Dummies, https://mikeash.com/pyblog/fluid-simulation-for-dummies.html

5. Simulation and Visualization of a 3D Fluid, https://www.mikeash.com/thesis/thesis-en.pdf

6. Fluid Simulation for Video Games, https://software.intel.com/en-us/articles/fluid-simulation-for-video-games-part-1/

7. Real-Time Fluid Dynamics for Games, http://www.dgp.toronto.edu/people/stam/reality/Research/pdf/GDC03.pdf

8. Mesh Deformation, http://catlikecoding.com/unity/tutorials/mesh-deformation/

9. Coupling 3D Eulerian, Heightfield and Particle Methods for Interactive Simulation of Large Scale Liquid Phenomena, http://matthias-mueller-fischer.ch/publications/hybridsim_preprinted.pdf

10. GPU Accelerated Computing with C and C++, https://developer.nvidia.com/how-to-cuda-c-cpp


## Contributions from each team member:
Yimin He: Implemented fluid simulation logic, rendering method and main setup. 
Yaqi Miao: An alternative UI with camera view (not used), implemented Particle initialization, spatial hashing, finding neighbors, debugging and tuning the rendering parameters; milestone report, video, and slides.
