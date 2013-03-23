/* 
 * File:   Position.cpp
 * Author: Philipp Jährling
 * 
 * Created on 18. Januar 2012, 00:50
 */

#include "Position.hpp"

Position::Position() {
    this->_x = 0;
    this->_y = 0;
}

Position::Position(int x, int y):_x(x), _y(y) {}

Position::~Position() {
}

bool Position::operator==(const Position& pos) const {
    return ( (this->_x == pos._x) && (this->_y == pos._y) );
}



