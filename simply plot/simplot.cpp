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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

void Parse(const char* pcFilename);
void writeSimple(const char* pcFilename);

int main(int argc, const char * argv[]) {
  std::string fileName = "figure.txt";
  
  // parse the plotting scrpt
  simplot::Plot plot;
  simplot::Parser::plotFromFile(plot, fileName);
  std::cout << plot.getWidth() << " " << plot.getHeight() << "\n";
  
  simplot::Plotter plotter;
  plotter.createFromPlot(plot);
  
  
  // convert the plot into XML
  //plot.writeSvg("figure.svg");
  return 0;
}

void writeSimple(const char* pcFilename) {
  ticpp::Document doc;
  ticpp::Declaration* decl = new ticpp::Declaration( "1.0", "UTF-8", "no" );
  doc.LinkEndChild(decl);
  
  ticpp::Element* root = new ticpp::Element("svg");
  doc.LinkEndChild(root);
  
  //ticpp::Attribute * att = new ticpp::Attribute("width", "400");
  root->SetAttribute("xmlns", "http://www.w3.org/2000/svg");
  root->SetAttribute("width", 400);
  root->SetAttribute("height", 210);
  
  ticpp::Element* path = new ticpp::Element("path");
  root->LinkEndChild(path);
  path->SetAttribute("d", "M150 0 L75 200 L225 200 Z");
  path->SetAttribute("fill", "teal");
  path->SetAttribute("stroke", "red");
  path->SetAttribute("stroke-width", 3);
  //doc.LinkEndChild(root);
  
  doc.SaveFile("test.svg");
}

void Parse(const char* pcFilename)
{
  // first load the xml file
  ticpp::Document doc(pcFilename);
  doc.LoadFile();
  
  // parse through all fruit elements
  ticpp::Iterator<ticpp::Element> child;
  for(child = child.begin(doc.FirstChildElement()); child != child.end(); child++)
  {
    // The value of this child identifies the name of this element
    std::string strName;
    std::string strValue;
    child->GetValue(&strName);
    std::cout << "fruit: " << strName << std::endl;
    std::cout << "-------------" << std::endl;
    
    // now parse through all the attributes of this fruit
    ticpp::Iterator< ticpp::Attribute > attribute;
    for(attribute = attribute.begin(child.Get()); attribute != attribute.end();
        attribute++)
    {
      attribute->GetName(&strName);
      attribute->GetValue(&strValue);
      std::cout << strName << ": " << strValue << std::endl;
    }
    std::cout << std::endl;
  }
}