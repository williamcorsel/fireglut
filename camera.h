/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"


//Class containing information and function for the Camera of the camera
class Camera{
private:
    
    // Position of the camera
    Vector3 * cameraPos;

    // Position of the target
    Vector3 * targetPos;

    //Rotation of camera around y axis 
    float rotation = 0.0f;

public:
    Camera(void);
    ~Camera(void);

    // Movement functions for camera
    void forward(const float speed);
    void backward(const float speed);
    void up(const float speed);
    void down(const float speed);
    void left(const float speed);
    void right(const float speed);

    // Reset Camera back to startPos
    void reset();

    // Getters and Setters
    Vector3 * getTargetPos(void);
    void setTargetPos(Vector3 * pos);
    Vector3 * getPosition(void);
    void setPosition(Vector3 * pos);
    const float getRotation(void);
    void setRotation(const float rot);
};

#endif