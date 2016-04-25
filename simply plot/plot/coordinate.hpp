//
//  coordinate.hpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//
//  A x,y coordinate. Essentially used to pass one variable
//  instead of two.

#ifndef coordinate_hpp
#define coordinate_hpp

#include <stdio.h>

namespace simplot {
  class Coordinate {
  public:
    Coordinate();
    Coordinate(float nX, float nY);
    
    Coordinate& operator+=(const Coordinate& coord2);
    Coordinate& operator-=(const Coordinate& coord2);
    friend Coordinate operator+(Coordinate lhs, const Coordinate& rhs);
    friend Coordinate operator-(Coordinate lhs, const Coordinate& rhs);
    
    float getX() const {return x;}
    float getY() const {return y;}
    int setX(float newx) {
      x = newx;
      return 1;
    }
    int setY(float newy) {
      y = newy;
      return 1;
    }
    
  private:
    float x;
    float y;
  };
}
#endif /* coordinate_hpp */
