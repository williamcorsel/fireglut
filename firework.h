/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 */

#ifndef FIREWORK_H
#define FIREWORK_H

#include "geometry.h"
#include "build.h"
#include "particle.h"
#include "sound.h"

#include <vector>


// Class containing all information about a firework
class Firework{

private:

    // Builder object 
    Builder builder;

    // Position of the firework on the ground level
    const Vector3 pos;

    // Array of particles to use in explosion
    std::vector<Particle> particles;

    // Particle representing the initial rocket
    Particle * rocket = nullptr;

    // Pointer to sound object
    Sound * sound;

    // Sets up the particles information with random values
    void setupParticles(const Vector3 position, const Vector4 color);

    // Returns a colour for the firework explosion
    const Vector4 getFireworkColor();

    // Draws the particles of the explosion
    const void drawParticles(void);

    // Draws a particle with a trail
    const void drawParticle(Particle * particle, const int trailLength);

    // Draws a particle without trail
    const void drawBasicParticle(Particle * particle);

    // Draws the rocket in the ground
    const void drawRocket(void);

    // Removes a particle from the particles vector
    void removeParticle(const int i);

    // Explodes the rocket
    const void explode(const Vector3 position, const Vector4 color);

    // Shoots up the rocket
    const void shoot(void);

    // Draws the rocket particle
    const void drawRocketParticle();

public:

    Firework(Vector3 pos, Sound * sound);
    ~Firework();

    // Fires off a firework
    void fire(void);

    // Draws all the elements of the firework
    void draw(void);

    // Updates particle position and velocity based on gravity values
    void gravityUpdate(const float time);

};

#endif