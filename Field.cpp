/* 
 * File:   Field.cpp
 * Author: Philipp Jährling
 * 
 * Created on 14. Januar 2012, 21:43
 */

#include <iosfwd>
#include <iostream>
#include <sstream>

#include "Field.hpp"

using namespace std;

//PUBLIC
Field::Field() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            this->content[i][j] = 0;
        }
    }
    this->winningPos = new Position(4, 2);
}
Field::~Field() {
    delete winningPos;
}

/*******************************************************************************
******************************* FOCUS-FUNCTIONS ********************************
*******************************************************************************/
int Field::focusRight(int index) {
    int toRun = this->getLength(index) - 1;
    //der folgende Block variiert für die verschiedenen Richtungen
    if ( this->isVertical(index) ) {
        //pos, searchDirX, searchDirY, runX, runY
        return this->changeFocus(index, 1, 0, 0, toRun);
        //vertikal liegend, nach rechts gucken, muss den stein auf der y-Achse seine eigene länge-1 ablaufen
    } else { //Horizontal
        return this->changeFocus(index, 1, 0, 0, 0);
        //horizontal liegend, nach rechts gucken, nur eine linie abfragen
    }
}

int Field::focusLeft(int index) {
    int toRun = this->getLength(index) - 1;
    if ( this->isVertical(index) ) {
        return this->changeFocus(index, -1, 0, 0, toRun);
    } else { //Horizontal
        return this->changeFocus(index, -1, 0, 0, 0);
    }
}

int Field::focusUp(int index) {
    int toRun = this->getLength(index) - 1;
    if ( this->isVertical(index) ) {
        return this->changeFocus(index, 0, -1, 0, 0);
    } else { //Horizontal
        return this->changeFocus(index, 0, -1, toRun, 0);
    }
}

int Field::focusDown(int index) {
    int toRun = this->getLength(index) - 1;
    if ( this->isVertical(index) ) {
        return this->changeFocus(index, 0, 1, 0, 0);
    } else { //Horizontal
        return this->changeFocus(index, 0, 1, toRun, 0);
    }
}

//PRIVATE

int Field::changeFocus(int index, int searchDirX, int searchDirY, int runX, int runY) {
    int focusStep = 1;
    int focusX    = 0;
    int focusY    = 0;
    int focusTmp  = 0;
    Position pos  = this->searchPosition(index);
    //cout << "AktFocusPosition: " << pos._x << "/" << pos._y << " Index: " << index << endl;

    // wenn in eine Richtung gesucht werden soll:
    //     aktPos + (die aktuelle Schrittlänge * der Richtung(+/-)
    // sonst
    //     aktPos bleibt so
    focusX = (searchDirX == 0) ? (pos._x)  :  (pos._x + (focusStep * searchDirX)) ; 
    focusY = (searchDirY == 0) ? (pos._y)  :  (pos._y + (focusStep * searchDirY)) ;
    while( (focusX >= 0 && focusX < SIZE) && (focusY >= 0 && focusY < SIZE) ) { //hier sollte auch eine falsche Position auffallen

        //gerade linie
        if( (content[focusY][focusX] > 0) && (content[focusY][focusX] != index) ) {
            //Stein gefunden
            return content[focusY][focusX];
        }

        //Stein durchlaufen START
       if( runX > 0 ) { //Stein horizontal ablaufen?
            for (int i = 0; i <= runX; i++ ) {
                focusTmp = focusX + i;
                if( (content[focusY][focusTmp] > 0) && (content[focusY][focusTmp] != index) ) {
                    //Stein gefunden
                    return content[focusY][focusTmp]; //hori. Wert ändert sich
                }
            }
        }
        if( runY > 0 ) { //Stein vertikal ablaufen?
            for (int i = 0; i <= runY; i++ ) {
                focusTmp = focusY + i;
                if( (content[focusTmp][focusX] > 0) && (content[focusTmp][focusX] != index) ) {
                    //Stein gefunden
                    return content[focusTmp][focusX]; //vert. Wert ändert sich
                }
            }
        }
        //Stein durchlaufen ENDE

        
        
        focusStep++; //Schrittweite erhöhen
        focusX = (searchDirX == 0) ? (pos._x)  :  (pos._x + (focusStep * searchDirX)) ;
        focusY = (searchDirY == 0) ? (pos._y)  :  (pos._y + (focusStep * searchDirY)) ;
    }
    return 0;
}


/*******************************************************************************
******************************* MOVE-FUNCTIONS *********************************
*******************************************************************************/
int Field::moveRight(int index) {
    //Gewinnprüfung
    if (index == 1) {
        Position pos = this->searchPosition(index);
        if ( pos == *(this->winningPos) ) {
            return 2;
        }
    }

    if ( this->isHorizontal(index) ) {
        Position pos  = this->searchPosition(index);
        int dest = ( pos._x + this->getLength(index) );
        if ( (dest >= 0) && (dest < SIZE) && (content[pos._y][dest] == 0) ) {
            content[pos._y][pos._x] = 0;
            content[pos._y][dest] = index;
            return 1;
        }
    }
    return 0;
}

int Field::moveLeft(int index) {
     if ( this->isHorizontal(index) ) {
        Position pos  = this->searchPosition(index);
        int dest = (pos._x - 1);
        if ( (dest >= 0) && (dest < SIZE) && (content[pos._y][dest] == 0) ) {
            content[pos._y][(pos._x + this->getLength(index) - 1)] = 0;
            content[pos._y][dest] = index;
            return 1;
        }
    }
    return 0;
}

int Field::moveUp(int index) {
    if ( this->isVertical(index) ) {
        Position pos  = this->searchPosition(index);
        int dest = (pos._y - 1);
        if ( (dest >= 0) && (dest < SIZE) && (content[dest][pos._x] == 0) ) {
            content[(pos._y + this->getLength(index) - 1)][pos._x] = 0;
            content[dest][pos._x] = index;
            return 1;
        }
    }
    return 0;
}

int Field::moveDown(int index) {
    if ( this->isVertical(index) ) {
        Position pos  = this->searchPosition(index);
        int dest =  ( pos._y + this->getLength(index) );
        if ( (dest >= 0) && (dest < SIZE) && (content[dest][pos._x] == 0) ) {
            content[pos._y][pos._x] = 0;
            content[dest][pos._x] = index;
            return 1;
        }
    }
    return 0;
}

/*******************************************************************************
******************************* UTIL-FUNCTIONS *********************************
*******************************************************************************/
//PUBLIC
bool Field::loadLevel(int level) {
    //ANFANG - Hier erstmal nur Musterwerte
    this->elementCounter = 7;
    int tmp1[SIZE][SIZE] = { { 0,  0,  0, 30,  0, 10}
                           , { 0,  0,  0, 30, 14, 10}
                           , {11,  1,  1, 30, 14,  0}
                           , {11, 13,  0,  0,  0,  0}
                           , {12, 13,  0,  0,  0,  0}
                           , {12,  0, 20, 20,  0,  0} };

    int tmp2[SIZE][SIZE] = { {10, 20, 20, 15, 21, 21}
                           , {10, 12, 13, 15,  0, 16}
                           , {11, 12, 13,  1,  1, 16}
                           , {11,  0, 14,  0,  0, 17}
                           , { 0,  0, 14,  0,  0, 17}
                           , {40, 40, 40,  0,  0,  0} };

    int tmp3[SIZE][SIZE] = { {30, 10, 40, 40, 40,  0}
                           , {30, 10,  0, 12, 22, 22}
                           , {30,  1,  1, 12,  0, 13}
                           , { 0, 11, 31, 20, 20, 13}
                           , { 0, 11, 31,  0,  0, 14}
                           , { 0,  0, 31, 21, 21, 14} };
    //ENDE - später evtl. aus File
    switch (level) {
        case 1:
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    this->content[i][j] = tmp1[i][j];
                }
            }
            break;

        case 2:
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    this->content[i][j] = tmp2[i][j];
                }
            }
            break;
        default:
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    this->content[i][j] = tmp3[i][j];
                }
            }
            break;
    }
    return true;
}

int Field::getElementCounter() {
    return this->elementCounter;
}

vector< vector<int> > Field::getElementList() {
    vector< vector<int> > vRes;
    vector<int> vFound;
    vector<int>::iterator it;
    vector<int>::iterator itEnd;
    int curIndex = 0;
    int tmp = 0;

    /*
     * Geht das komplette Feld durch und added alle Elemente, zum Rückgabevector,
     * unter der Vorraussetzung, dass diese noch nicht gefunden wurden.
     */

    for (int i = 0; i < SIZE; i++) { //Alle Zeilen durchgehen
        for (int j = 0; j < SIZE; j++) { //Alle Spalten durchgehen
            if ( this->content[i][j] > 0 ) { //Liegt dort ein Element?
                
                //gucken ob Element schon mal gefunden wurde*/
                curIndex = this->content[i][j];

                if ( vFound.empty() ) {
                    vRes.push_back( createElementForList(curIndex, j, i) );
                    vFound.push_back(curIndex);
                } else {
                    it = vFound.begin();
                    itEnd = vFound.end();
                    while ( (it != itEnd) && ( curIndex != *it) ) {
                        ++it;
                    }
                    //Falls das Element schon gefunden wurde,
                    //wäre der Wert des Iterators = dem gefundenen Index -> Abbruchbedingung Schleife
                    if ( curIndex != *it ) {
                        vRes.push_back( createElementForList(curIndex, j, i) );
                        vFound.push_back(curIndex);
                    }
                }

            }
        }
    }
    return vRes;
}

//PRIVATE
vector<int> Field::createElementForList(int index, int x, int y) {
    vector<int> vTmp;
    vTmp.push_back(index);                   //erster Wert  = index
    vTmp.push_back(x);                       //zweiter Wert = x-Koordinate
    vTmp.push_back(y);                       //dritter Wert = y-Koordinate
    vTmp.push_back(this->getLength(index));  //vierter Wert = länge des Elements
    if (this->isHorizontal(index)) {         //fünfter Wert = ist Stein gedreht
        vTmp.push_back(1); //horizontal (gedreht)
    } else {
        vTmp.push_back(0); //vertikal (nicht gedreht)
    }
    return vTmp;
    //0 -> false / 1 -> true
}

Position& Field::searchPosition(int index) {
    Position* res = new Position;
    res->_x = -1;
    res->_y = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ( this->content[i][j] == index ) {
                res->_x = j;
                res->_y = i;
                return *res;
            }
        }
    }
    return *res;
}

bool Field::isVertical(int index) {
    if ( (index >= 10 && index < 20) || (index >= 30 && index < 40) ) {
       return true;
    } else {
        return false;
    }
}

bool Field::isHorizontal(int index) {
    if ( (index == 1) || (index >= 20 && index < 30) || (index >= 40 && index < 50) ) {
        return true;
    } else {
        return false;
    }
}

int Field::getLength(int index) {
    if ( index >= 30 && index < 50) {
        return 3;
    } else {
        return 2;
    }
}

