//
//  instruction.hpp
//  simply plot
//
//  Created by Andrey Denisov on 05/05/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//
//  Instructions are basic commands (text, path, etc.) that are passed
//  to the plotter to be converted to the format-specific instruction
//  written into the final figure file

#ifndef instruction_hpp
#define instruction_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "plotter.hpp"
#include "coordinate.hpp"
#include "dimensions.hpp"

namespace simplot {
  class Plotter;
  
  class Instruction {
  public:
    virtual ~Instruction() = 0;
    virtual int render(Plotter& plotter) = 0;
  private:
    
  };
  
  class Path : public Instruction { // path is a set of sections to be plot
  public:
    Path();
    ~Path();
    Path(std::vector<Coordinate> points); // initialising the Path with a given set of points
    int addPoint(Coordinate value);
    std::vector<std::vector<Coordinate>> getPoints() const {return points;}
    int render(Plotter& plotter);
  private:
    std::vector<std::vector<Coordinate>> points; // each subpath is drawn, the section between two subpaths is not
    // LineStyle style
  };
  
  class Text : public Instruction { // text consists of multiple labels, e.g. labels for axis ticks
  public:
    int render(Plotter& plotter);
  private:
    std::vector<std::string> labels; // text labels
    std::vector<Coordinate> positions; // positions of each label
    // TextStyle style ;
  };
  
  class SetSize : public Instruction { // setting size of the whole plot
  public:
    SetSize();
    SetSize(float width, float height);
    SetSize(Dimensions dimensions);
    ~SetSize();
    int render(Plotter& plotter);
    float getWidth() const {return dimensions.getWidth();}
    float getHeight() const {return dimensions.getHeight();}
    std::string getUnit() const {return dimensions.getUnit();}
  private:
    Dimensions dimensions;
  };
}

#endif /* instruction_hpp */
