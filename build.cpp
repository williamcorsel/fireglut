#include "build.h"
#include "GL/glut.h"

#include <iostream>

// Rocket properties
#define ROCKET_HEIGHT 20
#define ROCKET_WIDTH 3

#define PARTICLE_SIZE 0.5


const void Builder::base(const Vector3 pos, const float size){
    float xleft = pos.x() - size / 2.0f;
    float xright = pos.x() + size / 2.0f;
    float ztop = pos.z() + size / 2.0f;
    float zbottom = pos.z() - size / 2.0f;
    
    glColor4fv(color.elements());

    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(xleft, (GLfloat)pos.y(), zbottom);
    glVertex3f(xleft, (GLfloat)pos.y(), ztop);
    glVertex3f(xright, (GLfloat)pos.y(), ztop);
    glVertex3f(xright, (GLfloat)pos.y(), zbottom);
    glEnd();
}


const void Builder::particle(){
    glutSolidSphere(PARTICLE_SIZE, 10, 10);
}


const void Builder::rect(const Vector3 middle, const float width, const float height){
    const float halfWidth = width / 2.0f;
    const float halfHeight = height / 2.0f;

    Vector3 vertices[6][4] =
    {
        // front face
        {
            Vector3(middle.x() - halfWidth, middle.y() + halfHeight, middle.z() + halfWidth), //top left
            Vector3(middle.x() + halfWidth, middle.y() + halfHeight, middle.z() + halfWidth), // top right
            Vector3(middle.x() + halfWidth, middle.y() - halfHeight, middle.z() + halfWidth), // bottom right
            Vector3(middle.x() - halfWidth, middle.y() - halfHeight, middle.z() + halfWidth) // bottom left
        },
        // back face
        {
            Vector3(middle.x() - halfWidth, middle.y() + halfHeight, middle.z() - halfWidth), //top left
            Vector3(middle.x() + halfWidth, middle.y() + halfHeight, middle.z() - halfWidth), // top right
            Vector3(middle.x() + halfWidth, middle.y() - halfHeight, middle.z() - halfWidth), // bottom right
            Vector3(middle.x() - halfWidth, middle.y() - halfHeight, middle.z() - halfWidth) // bottom left
        },
        //left face
        {
            Vector3(middle.x() - halfWidth, middle.y() + halfHeight, middle.z() + halfWidth), //top left
            Vector3(middle.x() - halfWidth, middle.y() + halfHeight, middle.z() - halfWidth), // top right
            Vector3(middle.x() - halfWidth, middle.y() - halfHeight, middle.z() - halfWidth), // bottom right
            Vector3(middle.x() - halfWidth, middle.y() - halfHeight, middle.z() + halfWidth) // bottom left
        },
        // right face
        {
            Vector3(middle.x() + halfWidth, middle.y() + halfHeight, middle.z() + halfWidth), //top left
            Vector3(middle.x() + halfWidth, middle.y() + halfHeight, middle.z() - halfWidth), // top right
            Vector3(middle.x() + halfWidth, middle.y() - halfHeight, middle.z() - halfWidth), // bottom right
            Vector3(middle.x() + halfWidth, middle.y() - halfHeight, middle.z() + halfWidth) // bottom left
        },
        // top face
        {
            Vector3(middle.x() - halfWidth, middle.y() + halfHeight, middle.z() + halfWidth), //top left
            Vector3(middle.x() - halfWidth, middle.y() + halfHeight, middle.z() - halfWidth), // top right
            Vector3(middle.x() + halfWidth, middle.y() + halfHeight, middle.z() - halfWidth), // bottom right
            Vector3(middle.x() + halfWidth, middle.y() + halfHeight, middle.z() + halfWidth) // bottom left
        },
        // bottom face
        {
            Vector3(middle.x() - halfWidth, middle.y() - halfHeight, middle.z() + halfWidth), //top left
            Vector3(middle.x() - halfWidth, middle.y() - halfHeight, middle.z() - halfWidth), // top right
            Vector3(middle.x() + halfWidth, middle.y() - halfHeight, middle.z() - halfWidth), // bottom right
            Vector3(middle.x() + halfWidth, middle.y() - halfHeight, middle.z() + halfWidth) // bottom left
        }                    
    };
    
    for(int i = 0; i < 6; i++){ // draw the 6 faces
        face(vertices[i]);
    }
}


void Builder::setColor(const Vector4 col){ color = col; }


const void Builder::face(const Vector3 vertices[]){
    glColor4fv(color.elements());

    glBegin(GL_QUADS);

    for(int i = 0; i < 4; i++){
        glVertex3fv(vertices[i].elements());
    }

    glEnd();
}

const void Builder::cylinder(const Vector3 pos){
    glColor4fv(color.elements());
    glPushMatrix();
    
    glTranslatef(pos.x(), pos.y() + ROCKET_HEIGHT, pos.z());
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    
    gluCylinder(quadratic, ROCKET_WIDTH, ROCKET_WIDTH, ROCKET_HEIGHT, 32, 32);
    glPopMatrix();
}

const void Builder::ground(void){
    base(Vector3(0.0, -0.01, 0.0), 3000);
}
