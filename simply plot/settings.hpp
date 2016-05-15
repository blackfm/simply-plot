//
//  settings.hpp
//  simply plot
//
//  Created by Andrey Denisov on 26/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.
//
//  Reads and stores settings for the whole program

#ifndef settings_hpp
#define settings_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>

namespace simplot {
  namespace po = boost::program_options;
  
  class Settings {
  public:
    
    Settings();
    ~Settings();
    Settings(std::string filename); // create and load from file
    
    int loadFromFile(std::string filename);
    
    float getNumber(std::string setting);
    
    // Keys for settings
    // Components of keys from which the actual keys will be built
    // Categories
    static const std::string KEY_PLOT;
    static const std::string KEY_GENERAL;
    static const std::string KEY_AXIS;
    static const std::string KEY_GRAPH;
    // Properties
    static const std::string KEY_MARGIN;
    static const std::string KEY_FONTSIZE;
    static const std::string KEY_LINEWIDTH;
    static const std::string KEY_TICKLENGTH;
    static const std::string KEY_LONGTICKLENGTH;
    
  private:
    po::variables_map vm; // Map storing key:value pairs
  };
}

#endif /* settings_hpp */
