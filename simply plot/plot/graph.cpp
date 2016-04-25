//
//  graph.cpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "graph.hpp"

namespace simplot {
  Graph::Graph() {
    minX = 0;
    maxX = 0;
    minY = 0;
    maxY = 0;
  }
  
  // Building a graph from a given dataset and options
  Graph::Graph(Dataset data, const std::vector<std::string>& tokens) {
    minX = 0;
    maxX = 0;
    minY = 0;
    maxY = 0;
    
    int yColumn = 0;
    int xColumn = 0;
    std::vector<double> dataY;
    std::vector<double> dataX;
    
    if (tokens.size() == 2) { // if there is a single column, plot against 1, 2, 3...
      yColumn = std::stoi(tokens[1]);
      dataY = data.getColumn(yColumn);
      dataX.assign(dataY.size(), 0);
      std::iota(dataX.begin(), dataX.end(), 1); // filling dataX with 1, 2, 3...
    }
    else {
      xColumn = std::stoi(tokens[1]);
      yColumn = std::stoi(tokens[2]);
      dataX = data.getColumn(xColumn);
      dataY = data.getColumn(yColumn);
    }
    
    // Going through the data and adding coordinates to the list, checking for min max
    for (int i = 0; i < dataX.size(); ++i) {
      Coordinate temp(dataX[i], dataY[i]);
      values.push_back(temp);
      
      updateMinMax(dataX[i], dataY[i]);
    }
  }
  
  Graph::Graph(Dataset data, int colX, int colY) { // creating an graph from two columns
    minX = 0;
    maxX = 0;
    minY = 0;
    maxY = 0;
    
    std::vector<double> dataY;
    std::vector<double> dataX;
    
    dataY = data.getColumn(colY);
    if (colX >= 0)
      dataX = data.getColumn(colX);
    else { // wrong (or deliberately -1) colX - using 1, 2, 3...
      dataX.assign(dataY.size(), 0);
      std::iota(dataX.begin(), dataX.end(), 1); // filling dataX with 1, 2, 3...
    }
    
    // Going through the data and adding coordinates to the list, checking for min max
    for (int i = 0; i < dataX.size(); ++i) {
      Coordinate temp(dataX[i], dataY[i]);
      values.push_back(temp);
      updateMinMax(dataX[i], dataY[i]);
    }
  }
  
  Graph::Graph(Dataset data, int colY) : Graph(data, -1, colY) {} // creating an graph from one column (plot against 1, 2, 3...)

  
  int Graph::updateMinMax(float x, float y) { // Setting new values for min/max X/Y
    if (x < minX) {minX = x;}
    else if (x > maxX) {maxX = x;}
    if (y < minY) {minY = y;}
    else if (y > maxY) {maxY = y;}
    return 1;
  }
  
  const std::vector<Coordinate>& Graph::getValues() const {
    return values;
  }
}