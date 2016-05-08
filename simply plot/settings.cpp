//
//  settings.cpp
//  simply plot
//
//  Created by Andrey Denisov on 26/04/16.
//  Copyright © 2016 Andrey Denisov. All rights reserved.


#include "settings.hpp"
namespace simplot {
  Settings::Settings(std::string filename) {
    // Setup options.
    po::options_description desc("Options");
    
    // Settings names with types, to be put in a separate file
    typedef float t_margin;
    typedef float t_fontsize;
    
    desc.add_options()
    ((KEY_GENERAL + "." + KEY_FONTSIZE).c_str(), po::value<t_fontsize>(),
     "Default font size for all the plot elements")
    ((KEY_PLOT + "." + KEY_MARGIN).c_str(), po::value<t_margin>(),
     "Blank space reserved around the plot borders")
    ((KEY_GRAPH + "." + KEY_LINEWIDTH).c_str(), po::value<t_fontsize>(),
     "Default linewidth for graphs")
    ((KEY_AXIS + "." + KEY_LINEWIDTH).c_str(), po::value<t_fontsize>(),
     "Default linewidth for axes")
    ;
    // Load setting file.
    std::ifstream fileSettings(filename, std::ifstream::in);
    po::store(po::parse_config_file(fileSettings, desc), vm);
    fileSettings.close();
    po::notify(vm);
  }
  
  Settings::Settings() {
  }
  
  Settings::~Settings() {
  }
  
  float Settings::getNumber(std::string setting) {
    return vm[setting].as<float>();
  }
  
  // Keys for settings
  // Components of keys from which the actual keys will be built
  // Categories
  const std::string Settings::KEY_PLOT = "plot";
  const std::string Settings::KEY_GENERAL = "general";
  const std::string Settings::KEY_AXIS = "axis";
  const std::string Settings::KEY_GRAPH = "graph";
  // Properties
  const std::string Settings::KEY_MARGIN = "margin";
  const std::string Settings::KEY_FONTSIZE = "fontsize";
  const std::string Settings::KEY_LINEWIDTH = "linewidth";
  
}