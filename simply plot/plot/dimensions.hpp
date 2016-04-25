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

namespace simplot {
  class Dimensions {
  public:
    Dimensions();
    float getWidth() const {return width;}
    float getHeight() const {return height;}
    int setWidth(float w);
    int setHeight(float h);
    int set(float w, float h);
  private:
    float width;
    float height;
  };
}

#endif /* dimensions_hpp */
