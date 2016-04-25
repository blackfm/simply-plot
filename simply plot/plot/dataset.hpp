//
//  dataset.hpp
//  simply plot
//
//  Created by Andrey Denisov on 17/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//
//  Dataset contains a vector of columns of data file

#ifndef dataset_hpp
#define dataset_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>   // to build the plot from a file
#include <sstream>   // to parse the instructions file

namespace simplot {
  class Dataset {
  public:
    Dataset();
    Dataset(const std::vector<std::string>& tokens); // loading datafile given instructions
    const std::vector<double>& getColumn(int col); // returns the column
    int loadFromFile(std::string filename, const std::vector<std::string>& options); // loading data from file
  private:
    std::vector<std::vector<double>> data;
  };
}
#endif /* dataset_hpp */
