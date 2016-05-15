//
//  plot.hpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//
//  Plot is the topmost class, it contains members of Figure
//  and information on its size

#ifndef plot_hpp
#define plot_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>   // to build the plot from a file
#include <sstream>   // to parse the instructions file
#include <algorithm> // to use 'transform' with 'tolower'
#include <iomanip>   // for to string conversion with precision

#include "figure.hpp"
#include "dataset.hpp"
#include "coordsystem.hpp"
#include "graph.hpp"
#include "dimensions.hpp"
#include "settings.hpp"
#include "instruction.hpp"
#include "plotter.hpp"

namespace simplot {
  class Instruction;
  class Plotter;
  class Figure;
  class CoordSystem;
  class Graph;
  class Plot {
  public:
    Plot(Settings& settings);
    ~Plot();
    int setWidth(float width) {return dimensions.setWidth(width);}
    int setHeight(float height) {return dimensions.setHeight(height);}
    int setUnit(std::string unit);
    
    float getWidth() const {return dimensions.getWidth();}
    float getHeight() const {return dimensions.getHeight();}
    Dimensions getDimensions() const {return dimensions;}
    std::string getUnit() const {return unit;}
    
    int addFigure(Figure fig);
    int addDataSet(std::string filename, const std::vector<std::string>& options); // add a dataset and initialise it from file
    int plotxy(int colX, int colY, const std::vector<std::string>& options); // add (x,y) graph using columns colX, colY from the current dataset
    int setXticksValues(const std::vector<float>& values); // set values where x-axis ticks are placed
    int setYticksValues(const std::vector<float>& values); // set values where y-axis ticks are placed
    int setXticksLabels(const std::vector<std::string>& labels); // set labels to be put at x ticks
    int setYticksLabels(const std::vector<std::string>& labels); // set labels to be put at Y ticks
    
    
    // Getting various numbers
    unsigned long int numberOfFigures() const {return figures.size();}
    unsigned long int numberOfCoordSystems() const {return coordSystems.size();}
    unsigned long int numberOfGraphs() const {return graphs.size();}
    
    // Getting physical positions of points of a graph with respect to the top-left of the plot
    std::vector<Coordinate> getGraphPhysicalPositions(int nGraph) const;
    
    int render(Plotter& plotter); // rendering the plot using the given plotter
    
  private:
    Dimensions dimensions;
    std::string unit; // the same unit is used for all the measures within the plot
    
    // Structural elements of the plot
    std::vector<Figure> figures;
    std::vector<Dataset> datasets; // datasets to be used inside figures
    std::vector<CoordSystem> coordSystems; // coordinate systems which belong to figures
    // REMOVED 14.05.2016 std::vector<unsigned long> parentsCoordSystems; // which figure the coordinate system belongs to
    std::vector<Graph> graphs; // graphs which belong to coordinate systems
    //REMOVED 14.05.2016 std::vector<unsigned long> parentsGraphs; // which coordinate system the graph belongs to
    
    CoordSystem * getCoordinateSystem(); // get a pointer to most recently created coordinate system
    CoordSystem& currentCoordSystem(); // get a reference to currently active coordinate system
    Figure& currentFigure(); // get a reference to currently active figure
    
    int addGraph(Graph graph); // add a graph to the vector
    
    Settings& settings;
    
    std::vector<Instruction*> instructions; // stores instructions for the plotter
    int generateInstructions(); // generate the instructions set
  };
  
  std::string tostr(const float value, const int precision = 2);
  std::string tostr(const int value, const int precision = 2);
}
#endif /* plot_hpp */
