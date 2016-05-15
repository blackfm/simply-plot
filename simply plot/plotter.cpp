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
  
  int Plotter::runInstruction(const simplot::Path &path) {
    std::string strPlot = "";
    std::vector<std::vector<Coordinate>> segments = path.getPoints();
    
    for(auto segment : segments) { // going through each segment
      strPlot += "M"; // setting mode to move before the first point of the segment
      bool lineToMode = false; // tracking whether the mode was changed to lineTo
      for (auto point : segment) {
        strPlot += tostr(point.getX()) + " " + tostr(point.getY()) + " "; // adding the point coordinates
        if (lineToMode == false) {
          strPlot += "L "; // setting mode to line-to
          lineToMode = true;
        }
      }
    }
    
    ticpp::Element* svgPath = new ticpp::Element("path");
    
    // Setting the style
    svgPath->SetAttribute("fill", "none");
    svgPath->SetAttribute("stroke", "black");
    svgPath->SetAttribute("stroke-width", "0.5");
    svgPath->SetAttribute("d", strPlot);
    svgRoot->LinkEndChild(svgPath);
    return 1;
  }
  
  int Plotter::runInstruction(const simplot::SetSize &setsize) {
    svgRoot->SetAttribute("width", tostr(setsize.getWidth()) + setsize.getUnit());
    svgRoot->SetAttribute("height", tostr(setsize.getHeight()) + setsize.getUnit());
    // viewbox set to "0 0 w h" to match physical coordinates to the canvas
    svgRoot->SetAttribute("viewBox", "0 0 " + tostr(setsize.getWidth())
                          + " " + tostr(setsize.getHeight()) );
    return 1;
  }
  
  int Plotter::saveFile(const std::string& filename) { // finalising the plot and saving it into the file
    svgPlot.SaveFile(filename);
    return 1;
  }
  
  /*
  int Plotter::createFromPlot(const Plot& plot) { // create an SVG from Plot
    
    svgRoot->SetAttribute("width", tostr(plot.getWidth()) + plot.getUnit());
    svgRoot->SetAttribute("height", tostr(plot.getHeight()) + plot.getUnit());
    // viewbox set to "0 0 w h" to match physical coordinates to the canvas
    svgRoot->SetAttribute("viewBox", "0 0 " + tostr(plot.getWidth())
                          + " " + tostr(plot.getHeight()) );
    
    // Plotting just the graphs
    for (int graph = 0; graph < plot.numberOfGraphs(); ++graph) {
      std::vector<simplot::Coordinate> graphValues = plot.getGraphPhysicalPositions(graph);
      plotPath(graphValues);
    }
    
    // Plotting the coordinate systems: axes, ticks, labels
    for (int system = 0; system < plot.numberOfCoordSystems(); ++system) {
      
      //plotPath(graphValues);
    }
    
    svgPlot.SaveFile("test_figure.svg");
    return 1;
  }
   
  
  int Plotter::plotPath(const simplot::Path &path) {
    std::string strPlot = "";
    std::vector<std::vector<Coordinate>> segments = path.getPoints();
    
    for(auto segment : segments) { // going through each segment
      strPlot += "M"; // setting mode to move before the first point of the segment
      bool lineToMode = false; // tracking whether the mode was changed to lineTo
      for (auto point : segment) {
        strPlot += tostr(point.getX()) + " " + tostr(point.getY()) + " "; // adding the point coordinates
        if (lineToMode == false) {
          strPlot += "L "; // setting mode to line-to
          lineToMode = true;
        }
      }
    }
    
    ticpp::Element* svgPath = new ticpp::Element("path");
    svgPath->SetAttribute("fill", "none");
    svgPath->SetAttribute("stroke", "black");
    svgPath->SetAttribute("stroke-width", "0.5");
    svgPath->SetAttribute("d", strPlot);
    svgRoot->LinkEndChild(svgPath);
    return 1;
  }
   */

  
  /*int Plotter::plotPath(const std::vector<simplot::Coordinate>& values) { // create and add a path element to SVG
    std::string strPlot = "";
    for (auto it = begin(values); it != end(values); ++it) {
      if (strPlot.empty()) { // starting the path, have to move to the first point then set mode to lineto
        strPlot += "M" + tostr(it->getX()) + " " + tostr(it->getY()) + " L";
      }
      else { // continuing the path, making a line to the next point
        strPlot += tostr(it->getX()) + " " + tostr(it->getY()) + " ";
      }
    }
    
    ticpp::Element* svgPath = new ticpp::Element("path");
    svgPath->SetAttribute("fill", "none");
    svgPath->SetAttribute("stroke", "black");
    svgPath->SetAttribute("stroke-width", "0.5");
    svgPath->SetAttribute("d", strPlot);
    svgRoot->LinkEndChild(svgPath);
    return 1;
  }*/
}
