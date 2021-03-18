/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 */

#include "particle.h"

#include <algorithm>
#include <iostream>

#define GRAV_ACC 9.81

Particle::Particle(float lifespan) : pos(Vector3(0.0f, 0.0f, 0.0f)), vel(Vector3(0.0f, 0.0f, 0.0f)), col(Vector4(1.0f, 1.0f, 1.0f)), 
       width(2.0), m(1.0), time(lifespan), totalTime(lifespan) 
{}



void Particle::update(const float dtime, const bool alpha){
    pos += vel * dtime;
    vel.y() -= GRAV_ACC * dtime;
    time -= dtime;
    if(alpha && time > 0.0){ // adjust the transparency  
        col.w() = std::max(0.0, time / (totalTime / 2.0));
    }
}

const int Particle::getTrailCount(void){ return trailCount; }
