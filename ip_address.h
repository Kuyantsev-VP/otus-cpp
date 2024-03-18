#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>


typedef int byte;


class IPAddress : std::array<byte, 4> {
public:
  IPAddress(int a, int b, int c, int d);
  static IPAddress fromString(const std::string &ip_address_str);
  const int& operator[](std::size_t index) const {
      return std::array<byte, 4>::operator[](index);
  }
  friend std::ostream &operator<<(std::ostream &stream,
                                  const IPAddress &ip_address) {
    stream << ip_address[0] << '.' << ip_address[1] << '.'
           << ip_address[2] << '.' << ip_address[3];
    return stream;
  }
  // // Overload comparison operators
  bool operator<(const IPAddress& other) const;
};
