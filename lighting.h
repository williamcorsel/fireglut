/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 * Using elements from the Homework 2 assignment
 */

#ifndef LIGHTING_H
#define LIGHTING_H

#include "geometry.h"
#include "GL/glut.h"

// Class for controlling lighting options
class Lighting{
private:

    // Diffuse light
    Vector3 diffuse = Vector3(1.0, 1.0, 1.0);

    // Ambient light
    Vector3 ambient = Vector3(1.0, 1.0, 1.0);

    // Position of the light source
    Vector4 pos = Vector4(0.0, 0.0, 1.0, 0.0);

    // Flags for toggling lighting modes
    int aflag = 1;
    int dflag = 1;
    int mflag = 0;

    //commonly used material values
    Vector4 no_mat = Vector4(0.0, 0.0, 0.0, 1.0);
    Vector4 default_ambient = Vector4(0.2, 0.2, 0.2, 1.0);
    Vector4 mat_ambient = Vector4(0.7, 0.7, 0.7, 1.0 );
    Vector4 mat_ambient_color = Vector4( 0.8, 0.8, 0.2, 1.0 );
    Vector4 mat_diffuse = Vector4( 0.1, 0.5, 0.8, 1.0 );
    Vector4 default_diffuse = Vector4(0.8, 0.8, 0.8, 1.0);
    Vector4 mat_specular = Vector4( 1.0, 1.0, 1.0, 1.0 );
    GLfloat no_shininess = 0.0;
    GLfloat low_shininess = 5.0;
    GLfloat high_shininess = 100.0;
    Vector4 mat_emission = Vector4(0.3, 0.2, 0.2, 0.0);
    Vector4 emmission = Vector4(1.0, 1.0, 1.0, 1.0);

public:

    // Initializes the lighting options
    const void initLighting(void);

    // Updates lighting 
    void updateLighting(void);

    // Light movement functions
    void left();
    void right();
    void up();
    void down();

    // Light properties toggles
    void toggleAmbient();
    void toggleDiffuse();
    void toggleMaterial();

};

#endif