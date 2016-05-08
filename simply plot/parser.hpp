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
    static int setXticksValues(Plot& plot, const std::vector<float>& values); // set values where x-axis ticks are placed
    static int setYticksValues(Plot& plot, const std::vector<float>& values); // set values where y-axis ticks are placed
    static int setXticksLabels(Plot& plot, const std::vector<std::string>& labels); // set labels to be put at x ticks
    static int setYticksLabels(Plot& plot, const std::vector<std::string>& labels); // set labels to be put at x ticks
    
    // List of commands used in instructions file
    static const std::string CMD_PLOT_SIZE;
    static const std::string CMD_FIGURE_SIZE;
    static const std::string CMD_LOAD_DATA;
    static const std::string CMD_PLOT_XY;
    static const std::string CMD_XTICK;
    static const std::string CMD_YTICK;
    static const std::string CMD_XTICK_LABEL;
    static const std::string CMD_YTICK_LABEL;
    
  private:
    
  };
}

#endif /* parser_hpp */
