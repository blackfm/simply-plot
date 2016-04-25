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
#include "ticpp.h"
#include "plot.hpp"

namespace simplot {
  class Plotter {
  public:
    Plotter();
    int createFromPlot(const simplot::Plot& plot); // create an SVG from Plot
  private:
    ticpp::Document svgPlot; // output SVG structure to be written in file
    ticpp::Element* svgRoot; // pointer to the SVG element, for convenience
    
    int plotPath(const std::vector<simplot::Coordinate>& values); // create and add a path element to SVG
  };
}
#endif /* plotter_hpp */
