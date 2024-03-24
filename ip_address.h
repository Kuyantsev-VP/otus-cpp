#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>


using byte = uint16_t;

class IPAddress : public std::array<byte, 4> {
public:
  static IPAddress fromString(const std::string &ip_address_str);
  friend std::ostream &operator<<(std::ostream &stream,
                                  const IPAddress &ip_address) {
    stream << ip_address[0] << '.' << ip_address[1] << '.'
           << ip_address[2] << '.' << ip_address[3];
    return stream;
  }
};
