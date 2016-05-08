//
//  coordsystem.cpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "coordsystem.hpp"

namespace simplot {
  CoordSystem::CoordSystem() {
    position = Coordinate(0, 0);
    width = 0;
    height = 0;
    
    originPosition = Coordinate(0, 0);
    originValue = Coordinate(0, 0);
    scaleX = 0;
    scaleY = 0;
    
    drawTicksX = true;
    drawTicksY = true;
    longEndTicks = true;
    
  }
  
  int CoordSystem::initFromGraph(const Graph& graph) { // initialising origin and scale from the graph
    originValue = Coordinate(graph.getminX(), graph.getminY());
    if (graph.getmaxX() != graph.getminX()) {
      scaleX = width/(graph.getmaxX() - graph.getminX());
    }
    if (graph.getmaxY() != graph.getminY()) {
      scaleY = height/(graph.getmaxY() - graph.getminY());
    }
    return 1;
  }
  
  int CoordSystem::setWidth(float w) {
    if (w <= 0) {
      width = 0;
      return 0;
    }
    width = w;
    return 1;
  }
  
  int CoordSystem::setHeight(float h) {
    if (h <= 0) {
      height = 0;
      return 0;
    }
    height = h;
    return 1;
  }
  
  Coordinate CoordSystem::toPhysicalPosition(const Coordinate& value) const {
    // Converting a value to the physical position relative to the bottom left
    // corner of the coordinate system
    Coordinate result((value.getX() - originValue.getX())*scaleX,  // physical position with respect
                      (value.getY() - originValue.getY())*scaleY); // to the origin
    result = result + originPosition; // position with respect to the bottom-left corner of the system
    return result;
  }
  
  int CoordSystem::setXticksValues(const std::vector<float>& values) { // set values where x-axis ticks are placed
    xTicksValues = values;
    return 1;
  }
  int CoordSystem::setYticksValues(const std::vector<float>& values) { // set values where y-axis ticks are placed
    yTicksValues = values;
    return 1;
  }
  int CoordSystem::setXticksLabels(const std::vector<std::string>& labels) { // set labels to be put at x ticks
    xTicksLabels = labels;
    return 1;
  }
  int CoordSystem::setYticksLabels(const std::vector<std::string>& labels) { // set labels to be put at x ticks
    yTicksLabels = labels;
    return 1;
  }
}