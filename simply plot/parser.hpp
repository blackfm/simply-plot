//
//  parser.hpp
//  simply plot
//
//  Created by Andrey Denisov on 22/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//
//  Parses the instruction file and gives Plot building commands

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include "plot.hpp"

namespace simplot {
  class Parser {
  public:
    static int plotFromFile(Plot& plot, std::string filename);
    static int processCommand(Plot& plot, const std::vector<std::string>& command); // making changes to the plot according to the command
    
    static int setPlotDimensions(Plot& plot, const std::vector<std::string>& options); // set width and height of the plot
    static int loadDataSet(Plot& plot, const std::vector<std::string>& options); // add a new dataset and initialise it from file
    static int plotxy(Plot& plot, const std::vector<std::string>& options); // add a new (x,y) graph to the plot
    
    // List of commands used in instructions file
    static const std::string CommandPlotSize;
    static const std::string CommandFigureSize;
    static const std::string CommandLoadData;
    static const std::string CommandPlotXY;
    
  private:
    
  };
}

#endif /* parser_hpp */
