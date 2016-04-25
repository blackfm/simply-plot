//
//  coordsystem.hpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//
//  Coordinate system is responsible for storing the information
//  about graphs, converting points from values to physical coordinates,
//  and so on

#ifndef coordsystem_hpp
#define coordsystem_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
#include "graph.hpp"

namespace simplot {
  class CoordSystem {
  public:
    CoordSystem();
    int initFromGraph(const Graph& graph); // Initialising the coordinate system with a graph (for origin and scale)
    int setWidth(float w);
    int setHeight(float h);
    Coordinate toPhysicalPosition(const Coordinate& value) const; // convert from value to relative position on paper
    Coordinate getOriginPosition() const {return originPosition;}
  private:
    // Physical values
    Coordinate position; // with respect to the bottom-left corner of the figure
    float width;
    float height;
    Coordinate originPosition; // with respect to the bottom-left corner of the system itself
    
    // Values related to the values against axes
    Coordinate originValue; // value at the origin position (0, 0) by default
    float scaleX; // units of value per units of figure
    float scaleY; // units of value per units of figure
  };
}

#endif /* coordsystem_hpp */
