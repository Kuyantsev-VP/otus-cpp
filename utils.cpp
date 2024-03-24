#include "utils.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

void split(const std::string &str, char sep,
           std::vector<std::string> &seglist) {
  std::stringstream str_stream(str);
  std::string segment;
  while (std::getline(str_stream, segment, sep)) {
    seglist.push_back(segment);
  }
}
