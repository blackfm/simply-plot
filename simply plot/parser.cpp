//
//  parser.cpp
//  simply plot
//
//  Created by Andrey Denisov on 22/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "parser.hpp"

namespace simplot {
  // Command names
  const std::string Parser::CommandPlotSize = "plotsize";
  const std::string Parser::CommandFigureSize = "figuresize";
  const std::string Parser::CommandLoadData = "loaddata";
  const std::string Parser::CommandPlotXY = "plotxy";
  
  int Parser::plotFromFile(Plot& plot, std::string filename) {
    std::ifstream instructions(filename);
    std::string line;
    
    while (std::getline(instructions, line)) {
      std::stringstream ss(line);
      std::string buf; // have a buffer string
      std::vector<std::string> command; // create vector to hold our words
      while (ss >> buf) {
        // Converting current token to lowercase and adding it to the vector
        std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);
        command.push_back(buf);
      }
      
      // Processing the command while checking if it went okay
      if (processCommand(plot, command)) {
        ;
      }
    }
    return 1;
  }
  int Parser::processCommand(simplot::Plot &plot, const std::vector<std::string> &command) {
    if (command.size() == 0) // empty line, skip
      return 1;
    else if (command[0][0] == '%') // comment, skip
      return 1;
    else if (command[0] == CommandFigureSize) { // setting figure size
      std::vector<std::string> options(command.begin() + 1, command.end());
      return setPlotDimensions(plot, options);
    }
    else if (command[0] == CommandLoadData) { // creating a dataset and adding it to current coordinate system
      std::vector<std::string> options(command.begin() + 1, command.end());
      loadDataSet(plot, options);
    }
    else if (command[0] == CommandPlotXY) { // adding a plot to the current coordinate system
      std::vector<std::string> options(command.begin() + 1, command.end());
      plotxy(plot, options);
    }
    return 0; // unknown command
  }
  
  int Parser::setPlotDimensions(Plot& plot, const std::vector<std::string>& options) { // set width and height of the plot
    if (options.size() < 2) // not enough arguments
      return 0;
    else {
      // ADD checking validity of arguments
      float width = std::stod(options[0]);
      float height = std::stod(options[1]);
      plot.setWidth(width);
      plot.setHeight(height);
    }
    if (options.size() >= 3) { // there is a third argument which is supposed to be theunit
      std::string unit = options[2];
      if (plot.setUnit(unit)) {;} // the unit is set correctly
    }
    if (options.size() > 3) { // there are too many arguments
      // report that the arguments will be ignored
    }
    return 1;
  }
  
  int Parser::loadDataSet(Plot& plot, const std::vector<std::string>& options) { // add a new dataset and initialise it from file
    std::string filename = options[0];
    std::vector<std::string> newOptions(options.begin() + 1, options.end());
    plot.addDataSet(filename, newOptions);
    return 1;
  }
  
  int Parser::plotxy(Plot& plot, const std::vector<std::string>& options) { // add a new (x,y) graph to the plot
    // NOTE for now not considering case of single column given
    if (options.size() < 2) {
      return 0;
    }
    int colX = std::stod(options[0]);
    int colY = std::stod(options[1]);
    std::vector<std::string> newOptions(options.begin() + 2, options.end());
    plot.plotxy(colX, colY, newOptions);
    return 1;
  }
}