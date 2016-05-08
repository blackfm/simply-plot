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
#include <string>
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
    
    int setXticksValues(const std::vector<float>& values); // set values where x-axis ticks are placed
    int setYticksValues(const std::vector<float>& values); // set values where y-axis ticks are placed
    int setXticksLabels(const std::vector<std::string>& labels); // set labels to be put at x ticks
    int setYticksLabels(const std::vector<std::string>& labels); // set labels to be put at x ticks
    
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
    
    // Values related to ticks
    bool drawTicksX; // whether to draw ticks at all
    bool drawTicksY;
    std::vector<float> xTicksValues;
    std::vector<float> yTicksValues;
    std::vector<std::string> xTicksLabels;
    std::vector<std::string> yTicksLabels;
    bool longEndTicks; // make ticks at the axis ends longer
    
    // Values related to axes
    std::string xAxisLabel;
    std::string yAxisLabel;
  };
}

#endif /* coordsystem_hpp */
