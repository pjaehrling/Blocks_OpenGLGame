/* 
 * File:   Block.hpp
 * Author: Philipp Jährling
 *
 * Created on 14. Januar 2012, 21:34
 */

#ifndef BLOCK_HPP
#define	BLOCK_HPP

#include "Drawable.hpp"
#include "Field.hpp"


class Block : public Drawable {
    public:
        //Konstruktoren
            Block(char* fn, Texture* tex, Texture* texFocus, bool big, bool turned);
            virtual ~Block();
        //Variablen
        //Funktionen
            void moveRight();
            void moveLeft();
            void moveUp();
            void moveDown();
            void setFocusTexture(Texture* texFocus);
            void setFocus(bool val);
            void setTopLeftCorner();
            void setShine(bool val, GLenum firstLight, GLenum secondLight);
            void draw();

    private:
        //Variablen
            Texture* textureFocus;
            float stepWideVert;
            float stepWideHor;
            bool focus;
            bool turned;
            bool big;
            bool shine;
            GLenum light1;
            GLenum light2;
        //Funktionen
};

#endif	/* BLOCK_HPP */

