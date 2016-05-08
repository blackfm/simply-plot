//
//  main.cpp
//  simply plot
//
//  Created by Andrey Denisov on 11/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include <iostream>
#include <string>
#include "ticpp.h"
#include "plot.hpp"
#include "plotter.hpp"
#include "parser.hpp"
#include "settings.hpp"

void checkSettings();

int main(int argc, const char * argv[]) {
  simplot::Settings settings("settings.ini");
  std::string fileName = "figure.txt";
  
  // parse the plotting scrpt
  simplot::Plot plot(settings);
  simplot::Parser::plotFromFile(plot, fileName);
  std::cout << plot.getWidth() << " " << plot.getHeight() << "\n";
  
  simplot::Plotter plotter;
  plot.render(plotter);
  

  return 0;
}