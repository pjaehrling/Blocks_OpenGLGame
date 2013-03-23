/* 
 * File:   Texture.hpp
 * Author: Philipp Jährling
 *
 * Created on 14. Januar 2012, 19:20
 */

#ifndef TEXTURE_HPP
#define	TEXTURE_HPP

//C-Code
extern "C" {
    #include <GL/glut.h>
    #include "glm.h"
    #include "gltx.h"
}

class Texture {
    public:
        //Konstruktoren
            Texture();
            Texture(char* fn, int index);
            virtual ~Texture();
        //Variablen
        //Funktionen
            void setFileName(char* fn);
            void setStorageIndex(int index);
            GLuint getTexName();
            void initTexture();
            void bindTexture();

    private:
        //Variablen
            char* fileName;
            GLuint txrName;
            GLTXimage* txrImage;
            int storageIndex;
        //Funktionen
};

#endif	/* TEXTURE_HPP */

