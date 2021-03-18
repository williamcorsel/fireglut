/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 */

#include "camera.h"
#include <cmath>

#include <iostream>

// Start position
static const Vector3 startPos = Vector3(150.0f, 100.0f, 200.0f);
static const Vector3 startTarget = Vector3(0.0f, 0.0f, -1.0f);

//constructor
Camera::Camera(void) : cameraPos(nullptr), targetPos(nullptr)
{
    reset();
}

Camera::~Camera(void){
    delete(cameraPos);
    delete(targetPos);
}

void Camera::forward(const float speed){
    cameraPos->x() += targetPos->x() * speed;
    cameraPos->z() += targetPos->z() * speed;
}

void Camera::backward(const float speed){
    cameraPos->x() -= targetPos->x() * speed;
    cameraPos->z() -= targetPos->z() * speed;
}

void Camera::up(const float speed){
    cameraPos->y() += speed;
}

void Camera::down(const float speed){
    cameraPos->y() -= speed;
}

void Camera::reset(void){
    delete(cameraPos);
    delete(targetPos);

    cameraPos = new Vector3(startPos);
    targetPos = new Vector3(startTarget);
}

void Camera::left(const float speed){
    rotation -= speed;
    targetPos->x() = sin(rotation + speed);
    targetPos->z() = -cos(rotation + speed);
}

void Camera::right(const float speed){
    rotation += speed;
    targetPos->x() = sin(rotation + speed);
    targetPos->z() = -cos(rotation + speed);
}

// Getters and Setters
Vector3 * Camera::getTargetPos(void){ return targetPos; }
void Camera::setTargetPos(Vector3 * pos){ targetPos = pos; }
Vector3 * Camera::getPosition(void){ return cameraPos; }
void Camera::setPosition(Vector3 * pos){ cameraPos = pos; }
const float Camera::getRotation(void){ return rotation; }
void Camera::setRotation(const float rot){ rotation = rot; }
