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
#include "plot.hpp"
#include "dimensions.hpp"

namespace simplot {
  class Plot;
  class Figure {
  public:
    Figure(const Plot& parentPlot);
    float getWidth() const {return dimensions.getWidth();}
    float getHeight() const {return dimensions.getHeight();}
    Dimensions getDimensions() const {return dimensions;}
    int setWidth(float width);
    int setHeight(float height);
    int setOrigin(Coordinate origin) {this->origin = origin; return 1;}
    Coordinate getOrigin() const {return origin;}
  private:
    const Plot& parentPlot;
    
    Coordinate origin;  // all the coordinates are with respect to the bottom-left corner
    Dimensions dimensions;
  };
}

#endif /* figure_hpp */
