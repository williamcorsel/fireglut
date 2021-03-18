/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include "geometry.h"
#include <deque>


// Particle class containing information about 1 particle
class Particle{
private:

    // Length of the trail of the particle
    int trailCount = 0;
    
public:
    Vector3 pos; // Position
    Vector3 vel; // Velcocity
    Vector4 col; // Colour
    float width; // Width
    float m; // Mass
    float time; // Life time remaining
    float totalTime; // Total lifespan

    // Queue containing positions for creating trails
    std::deque<Vector3> posQueue; 

    Particle(float lifespan);

    // Function for updating velocities and positions
    // Alpha is a flag for enabling alpha adjustments
    void update(const float dtime, const bool alpha);

    // Getter for trailCount
    const int getTrailCount(void);

};

#endif