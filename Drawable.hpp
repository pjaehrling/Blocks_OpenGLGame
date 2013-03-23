/* 
 * File:   Drawable.hpp
 * Author: Philipp Jährling
 *
 * Created on 15. Januar 2012, 00:31
 */

#ifndef DRAWABLE_HPP
#define	DRAWABLE_HPP

#include "Texture.hpp"

//C-Code
extern "C" {
    #include <GL/glut.h>
}

class Drawable {
    public:
        //Konstruktoren
            Drawable();
            Drawable(char* fn, Texture* tex);
            virtual ~Drawable();
        //Variablen
        //Funktionen
            void scale(float x, float y, float z);
            void transform(float x, float y, float z);
            void setTexture(Texture* tex);
            void loadObject(char* fn);
            virtual void draw();

    protected:
        //Variablen
            float scl[3];
            float trans[3];
            Texture* texture;
            char* fileName;
            GLMmodel* object;
        //Funktionen
};

#endif	/* DRAWABLE_HPP */

