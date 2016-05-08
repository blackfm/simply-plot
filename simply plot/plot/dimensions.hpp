//
//  dimensions.hpp
//  simply plot
//
//  Created by Andrey Denisov on 22/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//
//  Stores width and height

#ifndef dimensions_hpp
#define dimensions_hpp

#include <stdio.h>
#include <string>

namespace simplot {
  class Dimensions {
  public:
    Dimensions();
    float getWidth() const {return width;}
    float getHeight() const {return height;}
    std::string getUnit() const {return unit;}
    int setWidth(float w);
    int setHeight(float h);
    int set(float w, float h);
    int set(const Dimensions& dimensions);
    int setUnit(const std::string& unit);
  private:
    float width;
    float height;
    std::string unit;
  };
}

#endif /* dimensions_hpp */
