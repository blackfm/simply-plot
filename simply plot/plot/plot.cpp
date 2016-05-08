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
    Graph newGraph(datasets.back(), colX, colY);
    addGraph(newGraph);
    return 1;
  }
  
  int Plot::addGraph(Graph graph) { // add a graph to the vector with proper checks
    graphs.push_back(graph);
    // Checking whether there are figures in plot, creating one if there are none
    if (figures.empty()) {
      Figure newFigure;
      float plotMargin = settings.getNumber(Settings::KEY_PLOT + "." + Settings::KEY_MARGIN);
      newFigure.setWidth(this->getWidth() - 2*plotMargin); // setting size equal to the one of the plot - margins
      newFigure.setHeight(this->getHeight() - 2*plotMargin);
      newFigure.setOrigin(Coordinate(plotMargin, plotMargin));
      
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
    std::vector<Coordinate> values = graphs[nGraph].getValues();
    double numberOfValues = values.size();
    
    unsigned long nSystem = parentsGraphs[nGraph];
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
  
  // Axes ticks settings
  int Plot::setXticksValues(const std::vector<float>& values) { // set values where x-axis ticks are placed
    CoordSystem& lastSystem = coordSystems.back();
    return lastSystem.setXticksValues(values);
  }
  int Plot::setYticksValues(const std::vector<float>& values) { // set values where y-axis ticks are placed
    CoordSystem& lastSystem = coordSystems.back();
    return lastSystem.setYticksValues(values);
  }
  int Plot::setXticksLabels(const std::vector<std::string>& labels) { // set labels to be put at x ticks
    CoordSystem& lastSystem = coordSystems.back();
    return lastSystem.setXticksLabels(labels);
  }
  int Plot::setYticksLabels(const std::vector<std::string>& labels) { // set labels to be put at x ticks
    CoordSystem& lastSystem = coordSystems.back();
    return lastSystem.setYticksLabels(labels);
  }
  
  std::vector<Instruction*> Plot::getInstructions() const {
    std::vector<Instruction*> instructions;
    // plotting graphs (lines, markers)
    for (int nGraph = 0; nGraph < graphs.size(); ++ nGraph) {
      Path path(getGraphPhysicalPositions(nGraph));
    }
    // plotting coordinate systems (axes, ticks, labels)
    return instructions;
  }
  
  int Plot::render(Plotter& plotter) { // rendering the plot using the given plotter
    if (instructions.size() == 0) {
      // create instructions
      generateInstructions();
    }
    for (auto instruction : instructions) {
      instruction->render(plotter);
    }
    plotter.finish(); // finalising the plot and saving it into the file
    return 1;
  }
  
  int Plot::generateInstructions() { // generate the instructions set
    // Plot properties
    SetSize * newInstruction = new SetSize(dimensions);
    instructions.push_back(newInstruction);
    // Instructions for graphs
    for (int nGraph = 0; nGraph < numberOfGraphs(); ++nGraph) { // going through each graph
      Path * newInstruction = new Path(getGraphPhysicalPositions(nGraph));
      instructions.push_back(newInstruction);
    }
    // TODO Instructions for axes (lines, ticks, labels)
    
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