/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 */

#ifndef BUILDER_H
#define BUILDER_H

#include "geometry.h"
#include "GL/glut.h"

// Class for building various objects
class Builder{

private:

    // Color for the object
    Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

    // Quadratic object
    GLUquadric * quadratic = gluNewQuadric();

public:

    // Prints a flat quad at the given position (With middle point (x, 0, z))
    const void base(const Vector3 pos, const float size);

    // Prints a particle
    const void particle(void);

    // Draws a rectangle given the middle point
    const void rect(const Vector3 middle, const float width, const float height);

    // Sets the color vector
    void setColor(const Vector4 col);

    // Prints a face given 4 vertices
    const void face(const Vector3 vertices[]);

    // Prints a cylinder with base middle point pos
    const void cylinder(const Vector3 pos);

    // Prints a ground pane
    const void ground(void);


};

#endif