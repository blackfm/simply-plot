//
//  plot.cpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "plot.hpp"

namespace simplot {
  
  Plot::Plot(Settings& settings) : settings(settings) {
    dimensions.setHeight(0);
    dimensions.setWidth(0);
    unit = "mm";
    dimensions.setUnit(unit);
  }
  
  Plot::~Plot() {
    // Remove all elements of instructions array
    for (auto instruction : instructions) {
      delete instruction;
    }
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
    dimensions.setUnit(unit);
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
    Graph newGraph(datasets.back(), colX, colY, currentCoordSystem());
    currentCoordSystem().initFromGraph(newGraph); // setting min/max ranges from the graph
    graphs.push_back(newGraph);
    return 1;
  }
  
  /*
  int Plot::addGraph(Graph graph) { // add a graph to the vector with proper checks
    graphs.push_back(graph);
    return 1;
  }*/
  
  // get a reference to currently active coordinate system
  CoordSystem& Plot::currentCoordSystem() {
    // if there are no coordinate systems create one
    if (coordSystems.size() == 0) {
      CoordSystem newSystem(currentFigure());
      coordSystems.push_back(newSystem);
    }
    return coordSystems.back();
  }
  
  // get a reference to currently active figure
  Figure& Plot::currentFigure() {
    // if there are no figures create one
    if (figures.size() == 0) {
      Figure newFigure(*this);
      figures.push_back(newFigure);
      float plotMargin = settings.getNumber(Settings::KEY_PLOT + "." + Settings::KEY_MARGIN);
      newFigure.setWidth(this->getWidth() - 2*plotMargin); // setting size equal to the one of the plot - margins
      newFigure.setHeight(this->getHeight() - 2*plotMargin);
      newFigure.setOrigin(Coordinate(plotMargin, plotMargin));
    }
    return figures.back();
  }
  
  // Getting physical positions of points of a graph with respect to the bottom-left of the plot
  std::vector<Coordinate> Plot::getGraphPhysicalPositions(int nGraph) const {
    const std::vector<Coordinate> values = graphs[nGraph].getValues();
    
    // REMOVED 14.05.2016 unsigned long nSystem = parentsGraphs[nGraph];
    // REMOVED 14.05.2016 const CoordSystem& system = coordSystems[nSystem];
    
    std::vector<Coordinate> result = coordSystems.back().toPhysicalPosition(values);
    return result;
  }
  
  // Axes ticks settings
  int Plot::setXticksValues(const std::vector<float>& values) { // set values where x-axis ticks are placed
    return currentCoordSystem().setXticksValues(values);
  }
  int Plot::setYticksValues(const std::vector<float>& values) { // set values where y-axis ticks are placed
    return currentCoordSystem().setYticksValues(values);
  }
  int Plot::setXticksLabels(const std::vector<std::string>& labels) { // set labels to be put at x ticks
    return currentCoordSystem().setXticksLabels(labels);
  }
  int Plot::setYticksLabels(const std::vector<std::string>& labels) { // set labels to be put at x ticks
    return currentCoordSystem().setYticksLabels(labels);
  }
  
  int Plot::render(Plotter& plotter) { // rendering the plot using the given plotter
    if (instructions.size() == 0) {
      // create instructions
      generateInstructions();
    }
    for (auto instruction : instructions) {
      instruction->render(plotter);
    }
    plotter.saveFile("test_figure.svg"); // finalising the plot and saving it into the file
    return 1;
  }
  
  int Plot::generateInstructions() { // generate the instructions set
    // Plot properties
    SetSize * newInstruction = new SetSize(dimensions);
    instructions.push_back(newInstruction);
    
    // Graphs
    /*
    for (int nGraph = 0; nGraph < numberOfGraphs(); ++nGraph) { // going through each graph
      Path * newInstruction = new Path(getGraphPhysicalPositions(nGraph));
      instructions.push_back(newInstruction);
    }*/
    
    for (auto graph : graphs) {
      Path * newPath = new Path(graph.getPhysicalPositions());
      instructions.push_back(newPath);
    }
    
    // IN PROGRESS Axes (lines, ticks, labels)
    
    for (int nSystem = 0; nSystem < numberOfCoordSystems(); ++nSystem) {
      CoordSystem& coordSystem = currentCoordSystem();
      Figure& parentFigure = figures.back();
      
      if (coordSystem.axisXon()) { // adding instruction to draw x axis
        Path * newPath = new Path();
        Coordinate firstPoint = coordSystem.getOriginPosition() + parentFigure.getOrigin(); // The first point is at the origin of the system
        Coordinate secondPoint = firstPoint + Coordinate(coordSystem.getWidth(), 0); // The last point is shifted by the width of the system
        newPath->addPoint(firstPoint);
        newPath->addPoint(secondPoint);
        instructions.push_back(newPath);
      }
      
      if (coordSystem.axisYon()) { // adding instruction to draw y axis
        Path * newPath = new Path();
        Coordinate firstPoint = coordSystem.getOriginPosition() + parentFigure.getOrigin(); // The first point is at the origin of the system
        Coordinate secondPoint = firstPoint - Coordinate(0, coordSystem.getHeight()); // The last point is shifted up by the height of the system
        newPath->addPoint(firstPoint);
        newPath->addPoint(secondPoint);
        instructions.push_back(newPath);
      }
      
      if (coordSystem.ticksXon()) {
        Path * newPath = new Path();
        // Going through all ticks and adding them as subpaths
        coordSystem.getXticksValues();
      }
    }
    return 1;
  }
  
  std::string tostr(const float value, const int precision) { // converting a float to a string with given precision
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
  }
  
  std::string tostr(const int value, const int precision) { // converting an integer
    return std::to_string(value);
  }


}