//
//  coordinate.cpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "coordinate.hpp"

namespace simplot {
  Coordinate::Coordinate() {
    x = 0;
    y = 0;
  }
  
  Coordinate::Coordinate(float nX, float nY) {
    x = nX;
    y = nY;
  }
  
  Coordinate& Coordinate::operator+=(const Coordinate & coord2) {
    this->setX(x + coord2.getX());
    this->setY(y + coord2.getY());
    return *this;
  }
  
  Coordinate& Coordinate::operator-=(const Coordinate & coord2) {
    this->setX(x - coord2.getX());
    this->setY(y - coord2.getY());
    return *this;
  }
  
  Coordinate operator+(Coordinate lhs, const Coordinate& rhs) {
    lhs += rhs;
    return lhs;
  }
  
  Coordinate operator-(Coordinate lhs, const Coordinate& rhs) {
    lhs -= rhs;
    return lhs;
  }
}