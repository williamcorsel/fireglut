/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 */

#include "firework.h"
#include "GL/glut.h"
#include "sound.h"
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <math.h>


#define BASE_SIZE 10

#define ROCKET_VEL 70.0

// Explosion properties
#define EXPLOSION_PARTICLES 20
#define EXPLOSION_TRAIL 10
#define EXPLOSION_LIFESPAN 3.0
#define EXPLOSION_STRENGTH 10.0

// Trail properties
#define TRAIL_LIFESPAN 4.0
#define TRAIL_DEVIATION 5.0


// Constructor for firework
Firework::Firework(Vector3 _pos, Sound * _sound) : builder(Builder()), pos(_pos), sound(_sound)
{  std::cout << "Armed firework!" << std::endl; }

Firework::~Firework(){
    delete(rocket);
}

void Firework::setupParticles(const Vector3 position, const Vector4 color){
    float angle;

    for(int i = 0; i < EXPLOSION_PARTICLES; i++){
        particles.push_back(Particle(EXPLOSION_LIFESPAN)); // Create new Particles
    }

    for(int i = 0; i < (int)particles.size(); i++){ // Setup particle vailues
        angle = 360.0 / (float)i;
        particles[i].pos = position;
        particles[i].vel = Vector3(sin(angle) * EXPLOSION_STRENGTH, cos(angle) * EXPLOSION_STRENGTH, 0.0f);
        particles[i].col = color;
    }
}


const void Firework::drawParticles(void){
    for(int i = 0; i < (int)particles.size(); i++){
        if(particles[i].time > 0.0){ // If still time left
            drawParticle(&particles[i], EXPLOSION_TRAIL);
        }else{
            removeParticle(i);
        }
    }
}


const void Firework::drawParticle(Particle * particle, const int trailLength){
    Vector3 position = particle->pos;
    float alpha;
    float startAlpha = particle->col.w();
    
    if(trailLength > 0){
        if((int)particle->posQueue.size() >= trailLength){ 
            particle->posQueue.pop_back(); // keep queue the same size
        }
        particle->posQueue.push_front(position); // add new position
    }

    drawBasicParticle(particle);

    if(trailLength > 0){
        for(int j = 0; j < (int)particle->posQueue.size(); j++){
            alpha = startAlpha - (startAlpha / (float)particle->posQueue.size()) * (float)j;
            particle->pos = particle->posQueue[j];
            particle->col.w() = alpha;
            drawBasicParticle(particle);
        }
    }
    particle->pos = position;
    particle->col.w() = startAlpha;
}


const void Firework::drawBasicParticle(Particle * particle){
    Vector3 position = particle->pos;
    Vector4 color = particle->col;
    float width = particle->width;

    glPushMatrix();
    glTranslatef(position.x(), position.y(), position.z());
    glScalef(width, width, width);
    glColor4f(color.x(), color.y(), color.z(), color.w());
    builder.particle();
    glPopMatrix();
}


const void Firework::drawRocket(void){
    builder.setColor(Vector4(0.05, 0.05, 0.05, 1.0));
    builder.base(pos, BASE_SIZE); // Print base
    builder.setColor(Vector4(0.698, 0.133, 0.133, 1.0));
    builder.cylinder(pos); // Print cylinder
}


void Firework::fire(void){
    sound->playSound("sounds/launch.wav");
    shoot();
}


void Firework::gravityUpdate(const float time){
    for(int i = 0; i < (int)particles.size(); i++){
        particles[i].update(time, true);
    }
    if(rocket != NULL){
        rocket->update(time, false);
        if(rocket->time < 0.0){
            explode(rocket->pos, getFireworkColor());
            delete(rocket);
            rocket = NULL;
        }
    }
}


void Firework::removeParticle(const int i){
    if(i < 0 || i >= (int)particles.size()){
        std::cerr << "ERROR: i (" << i << ") is out of range" << std::endl;
        return;
    }
    particles.erase(particles.begin() + i);
}

const void Firework::explode(const Vector3 position, const Vector4 color){
    setupParticles(position, color);
    sound->playSound("sounds/firework.wav");
}

const void Firework::drawRocketParticle(){
    if(rocket == NULL)
        return;

    drawParticle(rocket, 5);
}

const void Firework::shoot(void){
    rocket = new Particle(TRAIL_LIFESPAN);
    float rx = (float)rand() / (float)RAND_MAX * (TRAIL_DEVIATION + TRAIL_DEVIATION) - TRAIL_DEVIATION;
    float rz = (float)rand() / (float)RAND_MAX * (TRAIL_DEVIATION + TRAIL_DEVIATION) - TRAIL_DEVIATION;

    rocket->pos = Vector3(pos.x(), pos.y() + 20.0f, pos.z());
    rocket->vel = Vector3(rx, ROCKET_VEL, rz);
    rocket->col = Vector4(1.000, 0.843, 0.000, 1.000);
    std::cout << "Created new particle " << std::endl;
}

void Firework::draw(void){
    drawRocket();
    drawParticles();
    drawRocketParticle();
}

const Vector4 Firework::getFireworkColor(){
    std::vector<Vector4> colors = {
        Vector4(1.000, 0.000, 0.000, 1.000),
        Vector4(1.000, 0.549, 0.000, 1.000),
        Vector4(1.000, 1.000, 0.000, 1.000),
        Vector4(0.196, 0.804, 0.196, 1.000),
        Vector4(0.000, 0.000, 1.000, 1.000),
        Vector4(0.502, 0.000, 0.502, 1.000),
        Vector4(1.000, 1.000, 1.000, 1.000)
    };

    int index = rand() % colors.size();
    return colors[index];
}
