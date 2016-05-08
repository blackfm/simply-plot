//
//  instruction.cpp
//  simply plot
//
//  Created by Andrey Denisov on 05/05/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "instruction.hpp"
namespace simplot {
  Instruction::~Instruction() {;}
  
  Path::Path(std::vector<Coordinate> points) {
    this->points.push_back(points);
  }
  Path::~Path() {
    
  }
  int Path::render(Plotter& plotter) {
    plotter.runInstruction(*this);
    return 1;
  }
  
  SetSize::SetSize() {
    // default constructor, width and height of 0
  }
  
  SetSize::SetSize(float width, float height) {
    dimensions.setWidth(width);
    dimensions.setHeight(height);
  }
  
  SetSize::SetSize(Dimensions dimensions) {
    this->dimensions = dimensions;
  }

  SetSize::~SetSize() {
  }
  
  int SetSize::render(simplot::Plotter &plotter) {
    plotter.runInstruction(*this);
    return 1;
  }
}