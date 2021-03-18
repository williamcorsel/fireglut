/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 */

#include "lighting.h"

#define LIGHT_MOVEMENT_SPEED 0.2


const void Lighting::initLighting(void){
    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_LIGHTING); //enable the lighting
    glEnable(GL_LIGHT0); // Turn on our lights
    glEnable(GL_LIGHT1);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable ( GL_COLOR_MATERIAL ) ;

    glShadeModel (GL_SMOOTH); //set the shader to smooth shader
}

void Lighting::updateLighting(void){
    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse.elements()); //change the light accordingly
    glLightfv (GL_LIGHT1, GL_AMBIENT, ambient.elements()); //change the light accordingly
    glLightfv (GL_LIGHT0, GL_POSITION, pos.elements()); //change the light accordingly

    glPushMatrix();
    glTranslatef(pos.x(), pos.y(), pos.z());
    if(mflag==1) // If material options
	{
	    glMaterialfv(GL_FRONT, GL_AMBIENT, default_ambient.elements());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse.elements());
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular.elements());
        glMaterialfv(GL_FRONT, GL_SHININESS, &high_shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emmission.elements());
	}
	else
	{
        glMaterialfv(GL_FRONT, GL_AMBIENT, default_ambient.elements());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse.elements());
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat.elements());
        glMaterialfv(GL_FRONT, GL_SHININESS, &no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat.elements());
	}
	glPopMatrix();
}

void Lighting::left(){
    pos.x() -= LIGHT_MOVEMENT_SPEED;
}

void Lighting::right(){
    pos.x() += LIGHT_MOVEMENT_SPEED;
}

void Lighting::up(){
    pos.y() += LIGHT_MOVEMENT_SPEED;
}

void Lighting::down(){
    pos.y() -= LIGHT_MOVEMENT_SPEED;
}

void Lighting::toggleAmbient(){
    if(aflag == 0){
        aflag = 1;
        glEnable(GL_LIGHT1);
    }else{
        aflag = 0;
        glDisable(GL_LIGHT1);
    }
}

void Lighting::toggleDiffuse(){
    if(dflag == 0){
        dflag = 1;
        glEnable(GL_LIGHT0);
    }else{
        dflag = 0;
        glDisable(GL_LIGHT0);
    }
}

void Lighting::toggleMaterial(){
    if(mflag == 0){
        mflag = 1;
    }else{
        mflag = 0;
    }
}