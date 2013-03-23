/* 
 * File:   helper.hpp
 * Author: Philipp Jährling
 *
 * Created on 10. Januar 2012, 00:10
 */

#ifndef HELPER_HPP
#define	HELPER_HPP

#include "Texture.hpp"
#include "Drawable.hpp"
#include "Block.hpp"
//C-Code
extern "C" {
    #include <GL/glut.h>
}

using namespace std ;

void textOutput(GLfloat x, GLfloat y, char* text);

void skyboxShow(Texture* _skybox[], float rotX, float rotY);

void menuShow(Drawable* _menu, float rotX);

void initLight();

#endif	/* HELPER_HPP */

