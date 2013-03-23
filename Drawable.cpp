/* 
 * File:   Drawable.cpp
 * Author: Philipp Jährling
 * 
 * Created on 15. Januar 2012, 00:31
 */

#include "Drawable.hpp"


Drawable::Drawable() {
    this->texture   = NULL;
    this->fileName  = NULL;
    this->object    = NULL;
    this->scale(0.0, 0.0, 0.0);
    this->transform(0.0, 0.0, 0.0);
}

Drawable::Drawable(char* fn, Texture* tex) {
    this->scale(1.0, 1.0, 1.0);
    this->transform(0.0, 0.0, 0.0);
    this->texture  = tex;
    this->loadObject(fn);
}

Drawable::~Drawable() {
    delete this->texture;
}

void Drawable::scale(float x, float y, float z) {
    this->scl[0] = x;
    this->scl[1] = y;
    this->scl[2] = z;
}

void Drawable::transform(float x, float y, float z) {
    this->trans[0] = x;
    this->trans[1] = y;
    this->trans[2] = z;
}

void Drawable::setTexture(Texture* tex) {
    this->texture = tex;
}

void Drawable::loadObject(char* fn) {
    this->fileName = fn;
    this->object = glmReadOBJ(fn);
}

void Drawable::draw() {
    glPushMatrix();
    glTranslatef( this->trans[0], this->trans[1], this->trans[2] );
    glScalef( this->scl[0], this->scl[1], this->scl[2] );
    this->texture->bindTexture(); 
    glmDraw( this->object, GLM_TEXTURE | GLM_SMOOTH );
    glPopMatrix();
}

