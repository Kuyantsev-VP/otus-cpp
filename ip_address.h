#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>


typedef size_t byte;
typedef std::tuple<byte, byte, byte, byte> ip_tuple;


class IPAddress : public ip_tuple {
public:
  IPAddress(int byte_1, int byte_2, int byte_3, int byte_4);
  IPAddress &operator=(IPAddress &&);
  IPAddress(const IPAddress &);
  static IPAddress fromString(const std::string &ip_address_str);
  uint64_t toNumber();

  friend std::ostream &operator<<(std::ostream &stream,
                                  const IPAddress &ip_address) {
    stream << std::get<0>(ip_address) << '.' << std::get<1>(ip_address) << '.'
           << std::get<2>(ip_address) << '.' << std::get<3>(ip_address);
    return stream;
  }
};
