/* 
 * File:   Field.hpp
 * Author: Philipp Jährling
 * Created on 14. Januar 2012, 21:43
 */

#ifndef FIELD_HPP
#define	FIELD_HPP
#define SIZE 6

#include <vector>
#include "Position.hpp"

class Field {

    /* Regeln für Field-Content
     * - 0 = leer
     * - 1 = der Stein
     * - (erste Stelle = Richtung)
     * - 10-19 = X
     *           X
     *
     * - 20-29 = XX
     * 
     * - 30-39 = X
     *           X
     *           X
     *
     * - 40-49 = XXX
     *
     * y = vertikale Achse = Spalten
     * x = horizontale Achse = Zeilen
     * content[y][x]
     * Nullpunkt = oben rechts ...ich weiß das ist blod! :D
     */
    public:
        //Konstruktoren
            Field();
            virtual ~Field();
        //Variablen
        //Funktionen
            int focusRight(int index);
            int focusLeft(int index);
            int focusUp(int index);
            int focusDown(int index);
            //für move-Methoden 0 = nicht möglich, 1 = möglich, 2 = gewonnen
            int moveRight(int index);
            int moveLeft(int index);
            int moveUp(int index);
            int moveDown(int index);
            bool loadLevel(int level);
            int getElementCounter();
            std::vector< std::vector<int> > getElementList();

    private:
        //Variablen
            int content [SIZE][SIZE];
            int elementCounter;
            Position* winningPos;
        //Funktionen
            std::vector<int> createElementForList(int index, int x, int y);
            int changeFocus(int index, int searchDirX, int searchDirY, int toRunX, int toRunY);
            Position& searchPosition(int index);
            bool isVertical(int index);
            bool isHorizontal(int index);
            int getLength(int index);
};

#endif	/* FIELD_HPP */

