/* 
 * File:   movingBlocks.cpp
 * Author: Philipp Jährling
 *
 * Created on 9. Januar 2012, 00:05
 */

//Standartbibliotheken
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

//Eigene
#include "helper.hpp"
#include "Block.hpp"
#include "Field.hpp"
#include "Texture.hpp"

//C-Code
extern "C" {
    #include <GL/glut.h>
	#include <GL/gl.h>
}

using namespace std ;
/*******************************************************************************
********************************** VARIABLEN ***********************************
*******************************************************************************/
// Fenster
int wnd_width   = 1024; //800;
int wnd_height  = 768; //600;

// Szene
float rotXStart = 40.0;
float rotYStart = -90.0;
float rotX      = 0; //rotXStart;
float rotY      = 0; //rotYStart;
float rotStep   = 2.0;
bool camMod     = false;
bool menuMod    = true;
bool done       = false;
int focusIndex  = 1;
int menuIndex   = 1;
int level       = 1;

GLfloat light_position1[] = { 1.0, 1.0, 0.0, 0.0 };
//GLfloat light_position2[] = { 0.0, 1.0, 1.0, 0.0 }; //von links im Spiel
GLfloat light_position2[] = { -1.0, 1.0, 0.0, 0.0 };
GLfloat light_position3[] = { 0.0, 0.0, 1.0, 0.0 };

char* fnBigBlock    = (char*)"blockBigObject.obj";
char* fnSmallBlock  = (char*)"blockSmallObject.obj";
char* fnBox         = (char*)"boxObject.obj";
char* fnSkyboxTex[] = { (char*)"texture/brightday/skyboxRight.rgb"
                      , (char*)"texture/brightday/skyboxFront.rgb"
                      , (char*)"texture/brightday/skyboxLeft.rgb"
                      , (char*)"texture/brightday/skyboxBack.rgb"
                      , (char*)"texture/brightday/skyboxTop.rgb"
                      , (char*)"texture/brightday/skyboxBottom.rgb" };

//Texturen
Texture* texWood       = NULL;
Texture* texWood2      = NULL;
Texture* texWood3      = NULL;
Texture* texGreyStone  = NULL;
Texture* texRedStone   = NULL;
Texture* texOcherStone = NULL;
Texture* texMenu       = NULL;
Texture* texLevelDone  = NULL;
Texture* texSkyBox[6];

//Logik
Field* field        = NULL;
//Anzeige-Objekte
Drawable* box       = NULL;
Drawable* menu      = NULL;
Drawable* levelDone = NULL;
map<int, Block*> mBlockObjects;

/*******************************************************************************
*************************** ANIMATIONS-FUNKTIONEN ******************************
*******************************************************************************/
void TurnCamBack(int value) {
    if (rotY != rotYStart) {
        rotY = (rotY < rotYStart) ? (rotY + rotStep) : (rotY - rotStep);
        glutPostRedisplay();
        glutTimerFunc(10, TurnCamBack, 0);
    } else {
		if (rotX != rotXStart) {
		    rotX = (rotX < rotXStart) ? (rotX + rotStep) : (rotX - rotStep);
		    glutPostRedisplay();
		    glutTimerFunc(10, TurnCamBack, 0);
    	}
	}
}

void AnimateMenu(int value) {
    float rotEnd = menuIndex * 90.0;
    if (rotEnd == 270 && rotX == 0) { rotX = 360; }
    if (rotEnd == 0 && rotX == 270) { rotX = -90; }
    //cout << "rotEnd: " << rotEnd << " / rotX: " << rotX << endl;
    if (menuMod == true && rotX != rotEnd) {
        if ( rotX < rotEnd ) {
            //nach oben drehen
            rotX = (rotX == 360) ? (0 + rotStep) : (rotX + rotStep);
        } else {
            rotX = (rotX == 0) ? (360 - rotStep) : (rotX - rotStep);
        }
        glutPostRedisplay();
        glutTimerFunc(10, AnimateMenu, 0);
    }
}

/*******************************************************************************
************************************** UTILS ***********************************
*******************************************************************************/
void generateBlockObjects() {
    vector< vector<int> > vBlocksData;
    vBlocksData = field->getElementList();
    int index   = 0;
    int posHori = 0;
    int posVert = 0;
    int length  = 0;
    int turned  = 0; //0 -> false / 1 -> true
    bool focused = false;

    for (int i = 0; i < vBlocksData.size(); i++) {
        index   = vBlocksData[i].at(0); //erster Wert  = index
        posHori = vBlocksData[i].at(1); //zweiter Wert = horizontales Feld
        posVert = vBlocksData[i].at(2); //dritter Wert = vertikales Feld
        length  = vBlocksData[i].at(3); //vierter Wert = länge des Elements
        turned  = vBlocksData[i].at(4); //fünfter Wert = ist Stein gedreht*/

        //Erzeugen
        if (index == 1) {
            mBlockObjects[index] = new Block(fnSmallBlock, texRedStone, texOcherStone, false, (bool)turned) ;
        } else {
            if (length == 2) {
                mBlockObjects[index] = new Block(fnSmallBlock, texGreyStone, texOcherStone, false, (bool)turned) ;
            } else {
                mBlockObjects[index] = new Block(fnBigBlock, texGreyStone, texOcherStone, true, (bool)turned) ;
            }
            if (!focused) {
                mBlockObjects[index]->setFocus(true);
                focusIndex = index;
                focused = true;
            }
        }
        
        //mBlockObjects[index]->setShine(true, GL_LIGHT3, GL_LIGHT4);

        //An richtige Position bringen
        mBlockObjects[index]->setTopLeftCorner();
        for (int h = 0; h < posHori; h++) {
            mBlockObjects[index]->moveRight();
        }
        for (int v = 0; v < posVert; v++) {
            mBlockObjects[index]->moveDown();
        }
        //testing
        /*for (int j = 0; j < vBlocksData[i].size(); j++) { cout << vBlocksData[i][j] << endl; }*/
    }
}

void InitLevel() {
    //davor Level setzten, danach Redisplay
    done = false;
    field->loadLevel(level);
    generateBlockObjects();
    rotX = 0;
    rotY = 0;
    TurnCamBack(0);
    camMod  = false;
    menuMod = false;
}

void initMenu(int val) {
    done = false;
    menuMod = true;
    rotX = menuIndex * 90;
    mBlockObjects.clear();
    glutPostRedisplay();
}

/*******************************************************************************
***************************** ANZEIGE-FUNKTIONEN *******************************
*******************************************************************************/
void InitGL(void) {
    glClearColor( 0.0, 0.0, 0.0, 0.0 );     // Hintergrundfarbe
    glEnable( GL_NORMALIZE );
    glEnable(GL_DEPTH_TEST);

    initLight();

    //Texturen
    texWood         = new Texture((char*)"texture/wood1.rgb", 1);
	texWood2        = new Texture((char*)"texture/wood2.rgb", 1);
	texWood3        = new Texture((char*)"texture/wood3.rgb", 1);
    texGreyStone    = new Texture((char*)"texture/stone_grey1.rgb", 2);
    texOcherStone   = new Texture((char*)"texture/stone_ocher1.rgb", 3);
    texRedStone     = new Texture((char*)"texture/stone_red1.rgb", 4);
    texMenu         = new Texture((char*)"texture/stone_menu.rgb", 5);
    texLevelDone    = new Texture((char*)"texture/stone_done.rgb", 6);
    texWood->initTexture();
	texWood2->initTexture();
	texWood3->initTexture();
    texGreyStone->initTexture();
    texOcherStone->initTexture();
    texRedStone->initTexture();
    texMenu->initTexture();
    texLevelDone->initTexture();

    //Skybox
    for (int i = 0; i < 6; i++) {
        texSkyBox[i] = new Texture( fnSkyboxTex[i], (7 + i) );
        texSkyBox[i]->initTexture();
    }

    //Feld
    field = new Field();
    //Objekte
    box  = new Drawable(fnBox, texWood);
    menu = new Drawable(fnBigBlock, texMenu);
    levelDone = new Drawable(fnBigBlock, texLevelDone);
    initMenu(0);
}

void Resize(int width, int height) {
    glViewport( 0, 0, (GLint)width, (GLint)height );
    wnd_width = width;
    wnd_height= height;
}

void Display(void) {
    // Projektionsmatrix einstellen
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );   // Puffer leeren

    // Transformation der Ansicht
    glFrustum(-1, 1, -1, 1, 4, 100);

    // In ModelMode gehen
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);

    if (menuMod == true) {
        //Skybox
        skyboxShow(texSkyBox, 0, 0);
        glPushMatrix();
            glEnable(GL_LIGHTING); // --> Beleuchtung AN
            glLightfv(GL_LIGHT0, GL_POSITION, light_position2);
            glLightfv(GL_LIGHT1, GL_POSITION, light_position3);
            menuShow(menu, rotX);
        glPopMatrix();
        // Menü
        
    } else {
        //Skybox
        skyboxShow(texSkyBox, rotX, rotY);
        //Spielfeld + Elemente
        glPushMatrix();
            glEnable(GL_LIGHTING); // --> Beleuchtung AN
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            // Verschiebung in z-Richtung nach hinten (rauszoomen)
            glTranslatef ( 0.0, 0.0, -20.0 );
            glRotatef ( rotX, 1.0, 0.0, 0.0 );      // Rotation um die x-Achse
            glRotatef ( rotY, 0.0, 1.0, 0.0 );      // Rotation um die y-Achse
            glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
            glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
        
            //Objekte zeichen
            box->draw();
            for( map<int, Block*>::iterator it = mBlockObjects.begin(), itEnd = mBlockObjects.end(); it != itEnd; ++it) {
                (*it).second->draw();
            }

            
        glPopMatrix();
        if (done == true) {
            glPushMatrix();
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                glTranslatef ( 0.0, -1.0, -8.0 );
                glRotatef ( rotX - rotXStart + 15.0, 1.0, 0.0, 0.0 );      // Rotation um die x-Achse
                glRotatef ( rotY + rotYStart, 0.0, 1.0, 0.0 );      // Rotation um die y-Achse
                glRotatef ( 5.0, 0.0, 1.0, 0.0 );      // Rotation um die y-Achse
                levelDone->draw();        
            glPopMatrix();
        }
    }
    
    // Anzeigen
    glFlush();
}

/*******************************************************************************
********************************** STEUERUNG ***********************************
*******************************************************************************/
void menuAction () {
    if (menuIndex > 0) {
        level = menuIndex;
        InitLevel();
        glutPostRedisplay();
    } else {
        exit(0);
    }
}

//PFEILTASTEN - Ansicht drehen, Menu-Auswahl oder Stein bewegen
void SpecialKeys(int key, int x, int y) {
    switch (key) {
        //PFEIL OBEN
        case GLUT_KEY_UP:
            if (menuMod == true) {
                menuIndex = (menuIndex < 3) ? menuIndex+1 : 0;
                //cout << "MenuIndex: " << menuIndex << endl;
                AnimateMenu(0);
            } else if (camMod == true) {
                rotX += rotStep;
                glutPostRedisplay();
            } else {
                if (field->moveUp(focusIndex) == 1) {
                    mBlockObjects[focusIndex]->moveUp();
                    glutPostRedisplay();
                }
            }
            break;
        //PFEIL UNTEN
        case GLUT_KEY_DOWN:
            if (menuMod == true) {
                menuIndex = (menuIndex > 0) ? menuIndex-1 : 3;
                //cout << "MenuIndex: " << menuIndex << endl;
                AnimateMenu(0);
            } else if (camMod == true) {
                rotX -= rotStep;
                glutPostRedisplay();
            } else {
                if (field->moveDown(focusIndex) == 1) {
                    mBlockObjects[focusIndex]->moveDown();
                    glutPostRedisplay();
                }
            }
            break;
        //PFEIL LINKS
        case GLUT_KEY_LEFT:
            if (camMod == true) {
                rotY += rotStep;
                glutPostRedisplay();
            } else if (menuMod == false)  {
                if (field->moveLeft(focusIndex) == 1) {
                    mBlockObjects[focusIndex]->moveLeft();
                    glutPostRedisplay();
                }
            }
            break;
        //PFEIL RECHTS
        case GLUT_KEY_RIGHT:
            if (camMod == true) {
                rotY -= rotStep;
                glutPostRedisplay();
            } else if (menuMod == false) {
                int res = field->moveRight(focusIndex);
                if (res == 1) {
                    mBlockObjects[focusIndex]->moveRight();
                    glutPostRedisplay();
                } else if (res == 2) {
                    mBlockObjects[focusIndex]->moveRight();
                    done = true;
                    glutPostRedisplay();
                    glutTimerFunc(2500, initMenu, 0);
                }
            }
            break;
        //DEFAULT
        default:
            return;
    }
    //cout << "Rotation: X=" << rotX << " / " << "Y=" << rotY << endl ;
}

//NROMALE TASTEN - Stein auswählen, Menu-Punkt auswählen und Modus wechseln
void Keyboard(unsigned char key, int x, int y) {
    int newIndex = 0;
    switch ((int)key) {
        case 101:       // e --> Modus wechseln
            if (menuMod == false) {
                camMod = (camMod == true) ? false : true;
                TurnCamBack(0);
            }
            break;
        case 13:        // Enter --> in Menu = Auswahl
            if ( menuMod == true ) {
                menuAction();
            }
        case 119:       // w --> Fokus nach "oben" verschieben (-x)
            newIndex = field->focusUp(focusIndex);
            if (newIndex != 0) {
                mBlockObjects[focusIndex]->setFocus(false);
                mBlockObjects[newIndex]->setFocus(true);
                focusIndex = newIndex;
                glutPostRedisplay();
            }
            break;
        case 97:        // a --> Fokus nach "links" verschieben (+z)
            newIndex = field->focusLeft(focusIndex);
            if (newIndex != 0) {
                mBlockObjects[focusIndex]->setFocus(false);
                mBlockObjects[newIndex]->setFocus(true);
                focusIndex = newIndex;
                glutPostRedisplay();
            }
            break;
        case 115:       // s --> Fokus nach "unten" verschieben (+x)
            newIndex = field->focusDown(focusIndex);
            if (newIndex != 0) {
                mBlockObjects[focusIndex]->setFocus(false);
                mBlockObjects[newIndex]->setFocus(true);
                focusIndex = newIndex;
                glutPostRedisplay();
            }
            break;
        case 100:       // d --> Fokus nach "rechts" verschieben (-z)
            newIndex = field->focusRight(focusIndex);
            if (newIndex != 0) {
                mBlockObjects[focusIndex]->setFocus(false);
                mBlockObjects[newIndex]->setFocus(true);
                focusIndex = newIndex;
                glutPostRedisplay();
            }
            break;
        case 113:       // q --> zurück zum Menü
            if (menuMod == false) {
                initMenu(0);
            }
            break;
		case 49:       // q --> zurück zum Menü
            if (menuMod == false) {
                box->setTexture(texWood);
				glutPostRedisplay();
            }
            break;
		case 50:       // q --> zurück zum Menü
            if (menuMod == false) {
                box->setTexture(texWood2);
				glutPostRedisplay();
            }
            break;
		case 51:       // q --> zurück zum Menü
            if (menuMod == false) {
                box->setTexture(texWood3);
				glutPostRedisplay();
            }
            break;

        default:
            break;
    }
    //cout << "Keyboard:" << (int)key << endl ;
}

/*******************************************************************************
************************************** MAIN ************************************
*******************************************************************************/
int main(int argc, char **argv) {
    glutInit( &argc, argv );                // Initialsierung der GLUT-Bibliothek
    glutInitDisplayMode(    GLUT_SINGLE |   // einfacher Puffer
                            //GLUT_DOUBLE |   // doppelter Puffer
                            GLUT_DEPTH  |   // Tiefen Puffer vorhanden
                            GLUT_RGB );     // Farbpuffer mit Rot,Grün und Blau
    glutInitWindowSize( wnd_width,wnd_height );
    glutInitWindowPosition( 100,100 );
    glutCreateWindow( "We call it Blocks" );
    InitGL();
    
    //Festlegen der Funktionen die GLUT verwenden soll
    glutDisplayFunc( &Display );            // zeichnen des Bildes 
    glutReshapeFunc( &Resize );             // Größenänderungen des Fensters
    glutKeyboardFunc( &Keyboard );          // Buchstaben etc.
    glutSpecialFunc( &SpecialKeys );        // Pfeiltasten etc.
    glutMainLoop();                         // Glut-Endlosschleife
    return 0;
}
