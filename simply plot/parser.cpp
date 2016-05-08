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
  const std::string Parser::CMD_PLOT_SIZE   = "plotsize";
  const std::string Parser::CMD_FIGURE_SIZE = "figuresize";
  const std::string Parser::CMD_LOAD_DATA   = "loaddata";
  const std::string Parser::CMD_PLOT_XY     = "plotxy";
  const std::string Parser::CMD_XTICK       = "xtick";
  const std::string Parser::CMD_YTICK       = "ytick";
  const std::string Parser::CMD_XTICK_LABEL = "xticklabel";
  const std::string Parser::CMD_YTICK_LABEL = "yticklabel";
  
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
      else {
        ;
      }
      
      // Setting sizes and positions of all the elements
    }
    return 1;
  }
  int Parser::processCommand(simplot::Plot &plot, const std::vector<std::string> &command) {
    if (command.size() == 0) // empty line, skip
      return 1;
    else if (command[0][0] == '%') // comment, skip
      return 1;
    else if (command[0] == CMD_PLOT_SIZE) { // setting figure size
      std::vector<std::string> options(command.begin() + 1, command.end());
      return setPlotDimensions(plot, options);
    }
    else if (command[0] == CMD_LOAD_DATA) { // creating a dataset and adding it to current coordinate system
      std::vector<std::string> options(command.begin() + 1, command.end());
      return loadDataSet(plot, options);
    }
    else if (command[0] == CMD_PLOT_XY) { // adding a plot to the current coordinate system
      std::vector<std::string> options(command.begin() + 1, command.end());
      return plotxy(plot, options);
    }
    else if (command[0] == CMD_XTICK) { // setting positions of x-axis ticks
      std::vector<std::string> options(command.begin() + 1, command.end());
      std::vector<float> values;
      for (auto value : options) {
        values.push_back(std::stof(value));
      }
      return setXticksValues(plot, values);
    }
    else if (command[0] == CMD_YTICK) { // setting positions of y-axis ticks
      std::vector<std::string> options(command.begin() + 1, command.end());
      std::vector<float> values;
      for (auto value : options) {
        values.push_back(std::stof(value));
      }
      return setYticksValues(plot, values);
    }
    else if (command[0] == CMD_XTICK_LABEL) { // setting labels for x-axis ticks
      std::vector<std::string> labels(command.begin() + 1, command.end());
      return setXticksLabels(plot, labels);
    }
    else if (command[0] == CMD_YTICK_LABEL) { // setting labels for y-axis ticks
      std::vector<std::string> labels(command.begin() + 1, command.end());
      return setYticksLabels(plot, labels);
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
  
  int Parser::setXticksValues(Plot& plot, const std::vector<float>& values) { // set values where x-axis ticks are placed
    plot.setXticksValues(values);
    return 1;
  }
  int Parser::setYticksValues(Plot& plot, const std::vector<float>& values) { // set values where y-axis ticks are placed
    plot.setYticksValues(values);
    return 1;
  }
  int Parser::setXticksLabels(Plot& plot, const std::vector<std::string>& labels) { // set labels to be put at x ticks
    plot.setXticksLabels(labels);
    return 1;
  }
  int Parser::setYticksLabels(Plot& plot, const std::vector<std::string>& labels) { // set labels to be put at x ticks
    plot.setYticksLabels(labels);
    return 1;
  }
}