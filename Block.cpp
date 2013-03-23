/* 
 * File:   Block.cpp
 * Author: Philipp Jährling
 * 
 * Created on 14. Januar 2012, 21:34
 */

#include "Block.hpp"

Block::Block(char* fn, Texture* tex, Texture* texFocus, bool big, bool turned) {
    //Attribute aus Drawable
    this->scale(0.95, 0.95, 0.95);
    this->transform(0.0, 0.0, 0.0);
    this->texture      = tex;
    this->textureFocus = texFocus;
    this->loadObject(fn);

    //Block eigene Attribute
    this->focus  = false;
    this->turned = turned;
    this->big    = big;
    this->shine  = false;
    this->light1 = NULL;
    this->light2 = NULL;
}

Block::~Block(){};

void Block::moveRight() {
    this->transform( this->trans[0], this->trans[1], this->trans[2] - 1 );
}

void Block::moveLeft() {
     this->transform( this->trans[0], this->trans[1], this->trans[2] + 1 );
}

void Block::moveUp() {
     this->transform( this->trans[0] - 1, this->trans[1], this->trans[2] );
}

void Block::moveDown() {
    this->transform( this->trans[0] + 1, this->trans[1], this->trans[2] );
}

void Block::setFocusTexture(Texture* texFocus) {
    this->textureFocus = texFocus;
}

void Block::setFocus(bool val) {
    this->focus = val;
}

void Block::setTopLeftCorner() {
    if (this->turned == true ) {
        if (this->big == true) {
            this->transform( -2.5, 0, 1.5);
        } else {
            this->transform( -2.5, 0.0, 2.0);
        }
    } else {
        if (this->big == true) {
            this->transform( -1.5, 0, 2.5);
        } else {
            this->transform( -2.0, 0.0, 2.5);
        }
    }
}

void Block::setShine(bool val, GLenum firstLight, GLenum secondLight) {
    this->shine = val;
    if(val == true) {
        this->light1 = firstLight;
        this->light2 = secondLight;
    } else {
        this->light1 = NULL;
        this->light2 = NULL;
    }
}

void Block::draw() {
    GLfloat light_direction1[] = { 1.0, 0.0, 0.0 };
    GLfloat light_direction2[] = {-1.0, 0.0, 0.0 };
    GLfloat posNul[] = { 0.0, 0.0, 0.0 };
    glPushMatrix();
        glTranslatef( this->trans[0], this->trans[1], this->trans[2] );
        if (this->turned == true) {
            glRotatef( 90.0, 0.0, 1.0, 0.0 );
        }
        glScalef( this->scl[0], this->scl[1], this->scl[2] );
        if (this->focus == true) {
            this->textureFocus->bindTexture();
            if (this->shine == true && this->light1 != NULL && this->light2 != NULL) {
                glLightfv(this->light1, GL_SPOT_DIRECTION, light_direction1);
                glLightfv(this->light2, GL_SPOT_DIRECTION, light_direction2);
                glLightfv((GLenum)this->light1, GL_POSITION, posNul );
                glLightfv((GLenum)this->light2, GL_POSITION, posNul );
            }
        } else {
            this->texture->bindTexture();
        }
        glmDraw( this->object, GLM_TEXTURE | GLM_SMOOTH );
    glPopMatrix();
}


