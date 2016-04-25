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
#include "figure.hpp"
#include "dataset.hpp"
#include "coordsystem.hpp"
#include "graph.hpp"
#include "dimensions.hpp"

namespace simplot {
  
  class Plot {
  public:
    Plot();
    Plot(std::string filename);
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
    
    // Getting physical positions of points of a graph with respect to the bottom-left of the plot
    std::vector<Coordinate> getGraphPhysicalPositions(int nGraph) const;
    
  private:
    Dimensions dimensions;
    std::string unit; // the same unit is used for all the measures within the plot
    
    // Structural elements of the plot
    std::vector<Figure> figures;
    std::vector<Dataset> datasets; // datasets to be used inside figures
    std::vector<CoordSystem> coordSystems; // coordinate systems which belong to figures
    std::vector<unsigned long> parentsCoordSystems; // which figure the coordinate system belongs to
    std::vector<Graph> graphs; // graphs which belong to coordinate systems
    std::vector<unsigned long> parentsGraphs; // which coordinate system the graph belongs to
    
    CoordSystem * getCoordinateSystem(); // get a pointer to most recently created coordinate system
    int addGraph(Graph graph); // add a graph to the vector
    
    /*
    // Script processing commands
    int processCommand(const std::vector<std::string>& tokens); // making changes according to the command
    int setPlotSize(const std::vector<std::string>& tokens); // setting figure size using an instruction line
    int loadDataSet(const std::vector<std::string>& tokens); // loading a dataset and adding it to the system
    int plotxy(const std::vector<std::string>& tokens); // creates a plot to be put within coordinate system
    */
  };
}
#endif /* plot_hpp */
