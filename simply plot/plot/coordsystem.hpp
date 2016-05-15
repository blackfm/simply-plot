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
#include "figure.hpp"
#include "dimensions.hpp"

namespace simplot {
  class Figure;
  class Graph;
  class CoordSystem {
  public:
    CoordSystem(const Figure& parentFigure);
    int initFromGraph(const Graph& graph); // Initialising the coordinate system with a graph (for origin and scale)
    int setWidth(float w);
    int setHeight(float h);
    int setOriginPosition(Coordinate position) {originPosition = position; return 1;}
    
    float getWidth() {return dimensions.getWidth();}
    float getHeight() {return dimensions.getHeight();}
    
    Coordinate toPhysicalPosition(const Coordinate& value) const; // convert from value to absolute position on paper
    std::vector<Coordinate> toPhysicalPosition(const std::vector<Coordinate>& value) const; // convert an array of values to absolute positions on paper
    Coordinate getOriginPosition() const {return originPosition;}
    
    int setXticksValues(const std::vector<float>& values); // set values where x-axis ticks are placed
    int setYticksValues(const std::vector<float>& values); // set values where y-axis ticks are placed
    int setXticksLabels(const std::vector<std::string>& labels); // set labels to be put at x ticks
    int setYticksLabels(const std::vector<std::string>& labels); // set labels to be put at y ticks
    
    bool axisXon() {return drawAxisX;}
    bool axisYon() {return drawAxisY;}
    bool ticksXon() {return drawTicksX;}
    bool ticksYon() {return drawTicksY;}
    
    std::vector<float> getXticksValues() {return xTicksValues;}
    std::vector<float> getYticksValues() {return yTicksValues;}
    
  private:
    const Figure& parentFigure; // the figure that this coordinate system belongs to
    
    // Physical values
    Coordinate position; // with respect to the bottom-left corner of the figure
    Dimensions dimensions;
    //float width;
    //float height;
    Coordinate originPosition; // with respect to the bottom-left corner of the system itself
    
    // Values related to the values against axes
    Coordinate originValue; // value at the origin position (0, 0) by default
    float scaleX; // units of value per units of figure
    float scaleY; // units of value per units of figure
    
    // Values related to plotting axes
    bool drawAxisX;
    bool drawAxisY;
    
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
