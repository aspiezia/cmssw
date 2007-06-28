#ifndef SiPixelConfigParser_H
#define SiPixelConfigParser_H

/** \class SiPixelConfigParser
 * *
 *  Class that handles the SiPixel Quality Tests
 * 
 *  $Date: 2007/03/29 14:22:52 $
 *  $Revision: 1.4 $
 *  \author Petra Merkel
  */

#include "DQMServices/ClientConfig/interface/DQMParserBase.h"
#include <vector>
#include <fstream>
#include <string>
#include <map>


class SiPixelConfigParser : public DQMParserBase {

 public:
  

  // Constructor
  SiPixelConfigParser();
  
  // Destructor
  ~SiPixelConfigParser();

  // get List of MEs for TrackerMap
  bool getMENamesForTrackerMap(std::string& tkmap_name,std::vector<std::string>& me_names);
  bool getFrequencyForTrackerMap(int& u_freq);
  bool getMENamesForTree(std::string &structure_name, std::vector<std::string>& me_names);
  bool getMENamesForBarrelSummary(std::string &structure_name, std::vector<std::string>& me_names);
  bool getMENamesForEndcapSummary(std::string &structure_name, std::vector<std::string>& me_names);
  bool getFrequencyForBarrelSummary(int& u_freq);
  bool getFrequencyForEndcapSummary(int& u_freq);
  bool getMENamesForGrandBarrelSummary(std::string &structure_name, std::vector<std::string>& me_names);
  bool getMENamesForGrandEndcapSummary(std::string &structure_name, std::vector<std::string>& me_names);
  bool getFrequencyForGrandBarrelSummary(int& u_freq);
  bool getFrequencyForGrandEndcapSummary(int& u_freq);

 private:
  
};

#endif
