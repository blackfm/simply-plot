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
#include "coordsystem.hpp"

namespace simplot {
  class CoordSystem;
  class Graph {
  public:
    Graph(const CoordSystem& parentSystem);
    Graph(Dataset data, int colX, int colY, const CoordSystem& parentSystem); // creating an x,y graph from two columns of a dataset
    //Graph(Dataset data, int colY); // creating an graph from one column (plot it against 1, 2, 3...)
    
    float getminX() const {return minX;}
    float getmaxX() const {return maxX;}
    float getminY() const {return minY;}
    float getmaxY() const {return maxY;}
    double getSize() const {return values.size();}
    const std::vector<Coordinate>& getValues() const;
    const std::vector<Coordinate> getPhysicalPositions() const;
  private:
    const CoordSystem& parentSystem;
    
    std::vector<Coordinate> values; // x,y pairs of values to be plotted
    float minX; // Ranges of variables, useful to set axes limits
    float maxX;
    float minY;
    float maxY;
    int updateMinMax(float x, float y); // Setting new values for min/max X/Y based on given two values
  };
}

#endif /* graph_hpp */
