//
//  coordsystem.cpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "coordsystem.hpp"

namespace simplot {
  CoordSystem::CoordSystem(const Figure& parentFigure) : parentFigure(parentFigure) {
    position = Coordinate(0, parentFigure.getHeight()); // Setting the position of origin at the bottom-left corner of the figure
    dimensions = parentFigure.getDimensions();
    
    originPosition = Coordinate(0, parentFigure.getHeight());
    originValue = Coordinate(0, 0);
    scaleX = 0;
    scaleY = 0;
    
    drawAxisX = true;
    drawAxisY = true;
    
    drawTicksX = true;
    drawTicksY = true;
    longEndTicks = true;
    
  }
  
  int CoordSystem::initFromGraph(const Graph& graph) { // initialising origin and scale from the graph
    originValue = Coordinate(graph.getminX(), graph.getminY());
    if (graph.getmaxX() != graph.getminX()) {
      scaleX = getWidth()/(graph.getmaxX() - graph.getminX());
    }
    if (graph.getmaxY() != graph.getminY()) {
      scaleY = -(getHeight()/(graph.getmaxY() - graph.getminY())); // negative, since the "natural" y axis points down
    }
    return 1;
  }
  
  int CoordSystem::setWidth(float w) {
    return dimensions.setWidth(w);
  }
  
  int CoordSystem::setHeight(float h) {
    return dimensions.setHeight(h);
  }
  
  Coordinate CoordSystem::toPhysicalPosition(const Coordinate& value) const {
    // Converting a value to the physical position relative to the top left
    // corner of the coordinate system
    Coordinate result((value.getX() - originValue.getX())*scaleX,  // physical position with respect
                      (value.getY() - originValue.getY())*scaleY); // to the origin
    result += originPosition + parentFigure.getOrigin(); // shifting to get the absolute position
    return result;
  }
  
  std::vector<Coordinate> CoordSystem::toPhysicalPosition(const std::vector<Coordinate>& values) const { // convert an array of values to absolute positions on paper
    std::vector<Coordinate> result;
    for (auto value : values) {
      result.push_back(toPhysicalPosition(value));
    }
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