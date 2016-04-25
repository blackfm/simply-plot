//
//  plot.cpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "plot.hpp"

namespace simplot {
  
  Plot::Plot() {
    dimensions.setHeight(0);
    dimensions.setWidth(0);
    unit = "mm";
  }
  
  int Plot::setUnit(std::string u) {
    // ADD check for unit validity
    /*
     if (isValidUnit(u)) {
     unit = u;
     return 1;
     }
     else {
     unit = defaultUnit;
     return 0;
     }
     */
    
    unit = u;
    return 1;
  }
  
  // adding a figure to the vector
  int Plot::addFigure(Figure fig) {
    figures.push_back(fig);
    return 1;
  }
  
  
  int Plot::addDataSet(std::string filename, const std::vector<std::string>& options) { // add a dataset and initialise it from file
    Dataset data;
    datasets.push_back(data);
    Dataset& newData = datasets.back();
    return newData.loadFromFile(filename, options);
  }
  
  int Plot::plotxy(int colX, int colY, const std::vector<std::string>& options) { // add (x,y) graph using columns colX, colY from the current dataset
    Graph newGraph(datasets.back(), colX, colY);
    addGraph(newGraph);
    return 1;
  }
  
  int Plot::addGraph(Graph graph) { // add a graph to the vector with proper checks
    graphs.push_back(graph);
    // Checking whether there are figures in plot, creating one if there are none
    if (figures.empty()) {
      Figure newFigure;
      newFigure.setWidth(this->getWidth()); // setting size equal to the one of the plot
      newFigure.setHeight(this->getHeight());
      figures.push_back(newFigure);
    }
    // Checking whether there are coordinate systems, creating one if there are none
    if (coordSystems.empty()) {
      CoordSystem newSystem;
      double parentFigure = figures.size() - 1;
      newSystem.setWidth(figures[parentFigure].getWidth()); // setting size equal to the parent figure
      newSystem.setHeight(figures[parentFigure].getHeight());
      newSystem.initFromGraph(graphs.back()); // setting min/max ranges from the graph
      coordSystems.push_back(newSystem);
      parentsCoordSystems.push_back(parentFigure); // making a record about system's parent figure
    }
    parentsGraphs.push_back(coordSystems.size() - 1); // making a record about graph's parent system

    return 1;
  }
  
  // Getting physical positions of points of a graph with respect to the bottom-left of the plot
  std::vector<Coordinate> Plot::getGraphPhysicalPositions(int nGraph) const {
    std::vector<Coordinate> values = graphs[nGraph-1].getValues();
    double numberOfValues = values.size();
    
    unsigned long nSystem = parentsGraphs[nGraph-1];
    const CoordSystem& system = coordSystems[nSystem];
    unsigned long nFigure = parentsCoordSystems[nSystem];
    const Figure& figure = figures[nFigure];
    
    std::vector<Coordinate> result;
    for (int i = 0; i < numberOfValues; i++) {
      Coordinate temp(system.toPhysicalPosition(values[i])); // physical position with respect to coord system
      temp += system.getOriginPosition() + figure.getOrigin();
      // inverting y axis to start from (0, height) and point upwards.
      temp.setY(getHeight() - temp.getY());
      result.push_back(temp);
    }
    return result;
  }
}