/* 
 * File:   Texture.cpp
 * Author: Philipp Jährling
 * 
 * Created on 14. Januar 2012, 19:20
 */

#include "Texture.hpp"

Texture::Texture() {
}

Texture::Texture(char* fn, int index) {
    this->setFileName(fn);
    this->setStorageIndex(index);
}

Texture::~Texture() {
}

void Texture::setFileName(char* fn) {
    this->fileName = fn;
}

void Texture::setStorageIndex(int index) {
    this->storageIndex = index;
}

GLuint Texture::getTexName() {
    return this->txrName;
}

void Texture::initTexture() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, this->storageIndex);             //Wie die Textur im Speicher organisiert ist
    glGenTextures(this->storageIndex, &this->txrName);                  //generiert einen Namen für die Textur und speichert sie in die Variable "texName"
    glBindTexture(GL_TEXTURE_2D, this->txrName);                        //Textur binden/setzen --> alle folgenden Aktionen (inkl. in GKS schreiben) passieren mit dieser Textur
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       //Texturwdh. in x-Richtung x-->s
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       //Texturwdh. in y-Richtung y-->t
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  //Interpolation für Vergrößern: was soll passieren : hier nichts : GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  //Interpolation für Verkleinern: was soll passieren : hier nichts : GL_NEARES
    this->txrImage = gltxReadRGB(this->fileName); 
    glTexImage2D(   GL_TEXTURE_2D, 0, GL_RGB,
                    this->txrImage->width,
                    this->txrImage->height,
                    0, GL_RGB, GL_UNSIGNED_BYTE,
                    this->txrImage->data
                );
}

void Texture::bindTexture() {
    glBindTexture(GL_TEXTURE_2D, this->txrName);
}

