/*
 * File:   movingBlocks.cpp
 * Author: Philipp J‰hrling
 *
 * Created on 9. Januar 2012, 00:05
 */

#include <string.h>
#include <GL/gl.h>
#include "helper.hpp"
#include "Drawable.hpp"

using namespace std ;

void textOutput(GLfloat x, GLfloat y, char *text) {
    int len, i;
    glRasterPos2f(x, y);
    len = (int) strlen(text);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void skyboxShow(Texture* _skybox[], float rotX, float rotY) {
    float size = 2.5f;

    // Store the current matrix
    glPushMatrix();
    
    // Enable/Disable features
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);

    // Just in case we set all vertices to white.
    glColor4f(1,1,1,1);
    glTranslatef ( 0.0, 0.0, -2.0 );
    glRotatef ( rotX, 1.0, 0.0, 0.0 );      // Rotation um die x-Achse
    glRotatef ( rotY, 0.0, 1.0, 0.0 );      // Rotation um die y-Achse

    // Render the front quad
    glBindTexture(GL_TEXTURE_2D, _skybox[0]->getTexName());
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(  size, -size,  size );
        glTexCoord2f(1, 0); glVertex3f(  size, -size, -size );
        glTexCoord2f(1, 1); glVertex3f(  size,  size, -size );
        glTexCoord2f(0, 1); glVertex3f(  size,  size,  size );
    glEnd();
    
    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, _skybox[1]->getTexName());
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -size, -size,  size );
        glTexCoord2f(1, 0); glVertex3f(  size, -size,  size );
        glTexCoord2f(1, 1); glVertex3f(  size,  size,  size );
        glTexCoord2f(0, 1); glVertex3f( -size,  size,  size );
    glEnd();

    // Render the back quad
    glBindTexture(GL_TEXTURE_2D, _skybox[2]->getTexName());
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -size, -size, -size );
        glTexCoord2f(1, 0); glVertex3f( -size, -size,  size );
        glTexCoord2f(1, 1); glVertex3f( -size,  size,  size );
        glTexCoord2f(0, 1); glVertex3f( -size,  size, -size );
    glEnd();
    
    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, _skybox[3]->getTexName());
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(  size, -size, -size );
        glTexCoord2f(1, 0); glVertex3f( -size, -size, -size );
        glTexCoord2f(1, 1); glVertex3f( -size,  size, -size );
        glTexCoord2f(0, 1); glVertex3f(  size,  size, -size );
    glEnd();
    
    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, _skybox[4]->getTexName());
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f( -size,  size, -size );
        glTexCoord2f(0, 0); glVertex3f( -size,  size,  size );
        glTexCoord2f(1, 0); glVertex3f(  size,  size,  size );
        glTexCoord2f(1, 1); glVertex3f(  size,  size, -size );
    glEnd();

    // Render the bottom quad
    glBindTexture(GL_TEXTURE_2D, _skybox[5]->getTexName());
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -size, -size, -size );
        glTexCoord2f(0, 1); glVertex3f( -size, -size,  size );
        glTexCoord2f(1, 1); glVertex3f(  size, -size,  size );
        glTexCoord2f(1, 0); glVertex3f(  size, -size, -size );
    glEnd();

    // Restore enable bits and matrix
    glPopAttrib();
    glPopMatrix();
}

void menuShow(Drawable* _menu, float rotX) {
    glPushMatrix();
        //glDisable(GL_LIGHTING);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTranslatef ( 0.0, 0.0, -10.0 );
        glRotatef ( rotX + 10.0 , 1.0, 0.0, 0.0 );
        glRotatef ( 5.0, 0.0, 1.0, 1.0 );
        _menu->draw();
    glPopMatrix();
}

void initLight() {
   //Material/Reflektion
   GLfloat mat_specular[]       = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[]      = { 50 };

   //Lichter
   GLfloat light_position1[]    = { 1.0, 1.0, 0.0, 0.0 };
   GLfloat light_color1[]       = { 1.0, 1.0, 1.0, 1.0 }; //weiﬂ
   GLfloat light_position2[]    = { -1.0, 1.0, 0.0, 0.0 };
   GLfloat light_color2[]       = { 1.0, 1.0, 1.0, 1.0 }; //weiﬂ
   GLfloat light_color3[]       = { 1.0, 1.0, 1.0, 0.5 }; //weiﬂ

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable     (GL_NORMALIZE);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color1);
   glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color2);
   glLightfv(GL_LIGHT2, GL_AMBIENT, light_color3);

   //glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT2);


   //Stein Licht
    /*GLfloat light_color_stone[]    = { 1.0, 1.0, 0.0, 0.1 }; //gelb
    GLfloat light_cut_stone[]      = { 180.0 };
    glLightfv(GL_LIGHT3, GL_SPOT_CUTOFF, light_cut_stone);
    glLightfv(GL_LIGHT4, GL_SPOT_CUTOFF, light_cut_stone);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light_color_stone);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, light_color_stone);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);*/

   glEnable(GL_DEPTH_TEST);
}

