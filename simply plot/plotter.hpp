//
//  plotter.hpp
//  simply plot
//
//  Created by Andrey Denisov on 19/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//
//  Plotter does all the job of converting a Figure into the final file

#ifndef plotter_hpp
#define plotter_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "ticpp.h"
#include "plot.hpp"
#include "instruction.hpp"
#include "coordinate.hpp"

namespace simplot {
  class Instruction;
  class Path;
  class SetSize;
  class Plotter {
  public:
    
    Plotter();
    //int createFromPlot(const Plot& plot); // create an SVG from Plot
    //int createFromInstructions(const std::vector<Instruction*> instructions);
    int runInstruction (const Instruction& instruction); // run a single instruction
    int runInstruction (const Path& path); // add a path element
    int runInstruction (const SetSize& setsize); // set plot's size
    int plotPath(const std::vector<Coordinate>& values); // create and add a path element to SVG
    int finish(); // finalising the plot and saving it into the file
  private:
    ticpp::Document svgPlot; // output SVG structure to be written in file
    ticpp::Element* svgRoot; // pointer to the SVG element, for convenience
    
  };
}
#endif /* plotter_hpp */
