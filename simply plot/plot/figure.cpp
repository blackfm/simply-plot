//
//  figure.cpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "figure.hpp"

namespace simplot {
  Figure::Figure(const Plot& parentPlot) : parentPlot(parentPlot) {
    dimensions = parentPlot.getDimensions();
    //height = parentPlot.getHeight();
    //width = parentPlot.getWidth();
    origin = Coordinate(0, 0);
    //  CoordSystem tempSystem;
    //  coordSystems.push_back(tempSystem);
  }
  
  int Figure::setWidth(float w) {
    return dimensions.setWidth(w);
  }
  
  int Figure::setHeight(float h) {
    return dimensions.setHeight(h);
  }
}