//
//  dataset.cpp
//  simply plot
//
//  Created by Andrey Denisov on 17/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//

#include "dataset.hpp"

namespace simplot {
  Dataset::Dataset() {
    std::vector<double> temp;
    data.push_back(temp);
  }
  
  Dataset::Dataset(const std::vector<std::string>& tokens) {
    if (tokens.size() == 1) {
      return;
    }
    // first token is the loading command, does not matter for now
    
    // opening the file
    std::ifstream datafile(tokens[1]);
    std::string line;
    
    // Considering that it contains only numbers and only rectangular
    while (std::getline(datafile, line)) {
      int column = 0;
      std::stringstream ss(line);
      std::string num; // have a buffer string
      while (ss >> num) {
        if (data.size() <= column) { // there are not enough columns in the 'data'
          std::vector<double> temp;
          data.push_back(temp);
        }
        data[column].push_back(std::stod(num));
        ++column;
      }
    }
  }
  
  const std::vector<double>& Dataset::getColumn(int col) { // returns the column
    // if the column is invalid, return the pointer to the first
    if ( (col < 0) || (col > data.size()) ) {
      return data[0];
    }
    return data[col - 1];
  }
  
  int Dataset::loadFromFile(std::string filename, const std::vector<std::string>& options) {
    // opening the file
    std::ifstream datafile(filename);
    std::string line;
    
    // Considering that it contains only numbers and is rectangular
    while (std::getline(datafile, line)) {
      int column = 0;
      std::stringstream ss(line);
      std::string num; // have a buffer string
      
      while (ss >> num) {
        if (data.size() <= column) { // there are not enough columns in the 'data' add new
          std::vector<double> temp;
          data.push_back(temp);
        }
        data[column].push_back(std::stod(num));
        ++column;
      }
    }
    // for now the options are ignored
    return 1;
  }
}