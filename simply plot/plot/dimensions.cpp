//
//  dimensions.cpp
//  simply plot
//
//  Created by Andrey Denisov on 22/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "dimensions.hpp"

namespace simplot {
  Dimensions::Dimensions() {
    width  = 0;
    height = 0;
    unit   = std::string("mm");
  }
  
  int Dimensions::setWidth(float w) {
    if (w <= 0) {
      width = 0;
      return 0;
    }
    else {
      width = w;
      return 1;
    }
  }
  
  int Dimensions::setHeight(float h) {
    if (h <= 0) {
      height = 0;
      return 0;
    }
    else {
      height = h;
      return 1;
    }
  }
  
  int Dimensions::set(float w, float h) {
    if (!(setWidth(w) && setHeight(h))) { // at least one wrong arument
      return 0;
    }
    else {
      return 1;
    }
  }
  
  int Dimensions::set(const simplot::Dimensions& dimensions) {
    width  = dimensions.getWidth();
    height = dimensions.getHeight();
    return 1;
  }
  
  int Dimensions::setUnit(const std::string& unit) {
    this->unit = unit;
    return 1;
  }
}
