//
//  figure.hpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//
//  Figure defines the plotting area for a (sub)figure
//  It contains inside coordinate system(s) with graph(s) inside

#ifndef figure_hpp
#define figure_hpp

#include <stdio.h>
#include <vector>
#include "coordinate.hpp"
#include "dataset.hpp"

namespace simplot {
  class Figure {
  public:
    Figure();
    float getWidth() {return width;}
    float getHeight() {return height;}
    int setWidth(float width);
    int setHeight(float height);
    Coordinate getOrigin() const {return origin;}
  private:
    Coordinate origin;  // all the coordinates are with respect to the bottom-left corner
    float height;
    float width;
  };
}

#endif /* figure_hpp */
