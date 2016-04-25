//
//  plotter.cpp
//  simply plot
//
//  Created by Andrey Denisov on 19/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "plotter.hpp"

namespace simplot{
  Plotter::Plotter() { // initialising the root
    
    ticpp::Declaration* decl = new ticpp::Declaration( "1.0", "UTF-8", "no" ); // basic XML
    svgPlot.LinkEndChild(decl);
    
    ticpp::Element* root = new ticpp::Element("svg"); // root element
    svgPlot.LinkEndChild(root);
    svgRoot = root;
    root->SetAttribute("xmlns", "http://www.w3.org/2000/svg"); // declaring it to be SVG
  }
  
  int Plotter::createFromPlot(const simplot::Plot& plot) { // create an SVG from Plot
    svgRoot->SetAttribute("width", std::to_string(plot.getWidth()) + plot.getUnit());
    svgRoot->SetAttribute("height", std::to_string(plot.getHeight()) + plot.getUnit());
    // viewbox set to "0 0 w h" to match physical coordinates to the canvas
    svgRoot->SetAttribute( "viewBox", "0 0 " + std::to_string(plot.getWidth())
                          + " " + std::to_string(plot.getHeight()) );
    
    // For now, plotting just the first graph
    std::vector<simplot::Coordinate> graphValues = plot.getGraphPhysicalPositions(1);
    plotPath(graphValues);
    
    svgPlot.SaveFile("test_figure.svg");
    return 1;
  }
  
  int Plotter::plotPath(const std::vector<simplot::Coordinate>& values) { // create and add a path element to SVG
    std::string strPlot = "";
    for (auto it = begin(values); it != end(values); ++it) {
      if (strPlot.empty()) { // starting the path, have to move to the first point
        strPlot += "M";
      }
      else { // continuing the path, making a line to the next point
        strPlot += "L";
      }
      strPlot += std::to_string(it->getX()) + " " + std::to_string(it->getY()) + " ";
    }
    //strPlot += "Z"; // closing the path
    
    ticpp::Element* svgPath = new ticpp::Element("path");
    svgPath->SetAttribute("d", strPlot);
    svgPath->SetAttribute("fill", "none");
    svgPath->SetAttribute("stroke", "black");
    svgRoot->LinkEndChild(svgPath);
    return 1;
  }
}
