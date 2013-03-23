/* 
 * File:   Position.hpp
 * Author: Philipp Jährling
 *
 * Created on 18. Januar 2012, 00:50
 */

#ifndef POSITION_HPP
#define	POSITION_HPP

class Position {
public:
    Position();
    Position(int x, int y);
    virtual ~Position();
    bool operator==(const Position&) const ;
    int _x;
    int _y;
private:

};

#endif	/* POSITION_HPP */

