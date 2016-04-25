//
//  graph.hpp
//  simply plot
//
//  Created by Andrey Denisov on 16/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <numeric> // to initialise x values with 1, 2, 3...
#include "coordinate.hpp"
#include "dataset.hpp"

namespace simplot {
  class Graph {
  public:
    Graph();
    Graph(Dataset data, int colX, int colY); // creating an x,y graph from two columns
    Graph(Dataset data, int colY); // creating an graph from one column (plot against 1, 2, 3...)
    
    Graph(Dataset data, const std::vector<std::string>& tokens); //DEPRECATE
    float getminX() const {return minX;}
    float getmaxX() const {return maxX;}
    float getminY() const {return minY;}
    float getmaxY() const {return maxY;}
    double getSize() const {return values.size();}
    const std::vector<Coordinate>& getValues() const;
  private:
    std::vector<Coordinate> values; // x,y pairs of values to be plotted
    float minX; // Ranges of variables, useful to set axes limits
    float maxX;
    float minY;
    float maxY;
    int updateMinMax(float x, float y); // Setting new values for min/max X/Y
  };
}

#endif /* graph_hpp */
