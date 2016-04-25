//
//  figure.cpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "figure.hpp"

namespace simplot {
  Figure::Figure() {
    height = 0;
    width = 0;
    origin = Coordinate(0, 0);
    //  CoordSystem tempSystem;
    //  coordSystems.push_back(tempSystem);
  }
  
  int Figure::setWidth(float w) {
    if (w < 0) { // incorrect width
      width = 0;
      return 0;
    }
    else {
      width = w;
      return 1;
    }
  }
  
  int Figure::setHeight(float h) {
    if (h < 0) { // incorrect height
      height = 0;
      return 0;
    }
    else {
      height = h;
      return 1;
    }
  }
}