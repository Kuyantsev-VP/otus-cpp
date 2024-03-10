#include "ip_address.h"
#include "utils.h"


IPAddress::IPAddress(int byte_0, int byte_1, int byte_2, int byte_3)
    : ip_tuple(byte_0, byte_1, byte_2, byte_3) {}

IPAddress &IPAddress::operator=(IPAddress &&other) {
  if (this != &other) {
    static_cast<ip_tuple &>(*this) = std::move(static_cast<ip_tuple &>(other));
  }
  return *this;
}

IPAddress::IPAddress(const IPAddress &ip_address)
    : ip_tuple(std::get<0>(ip_address), std::get<1>(ip_address),
               std::get<2>(ip_address), std::get<3>(ip_address)) {}

IPAddress IPAddress::fromString(const std::string &ip_address_str) {
  std::vector<std::string> bytes_str;
  split(ip_address_str, '.', bytes_str);
  return IPAddress(std::stoi(bytes_str[0]), std::stoi(bytes_str[1]),
                   std::stoi(bytes_str[2]), std::stoi(bytes_str[3]));
}

uint64_t IPAddress::toNumber() {
  uint64_t _ip_address_num;
  _ip_address_num = 0;
  _ip_address_num |= std::get<0>(*this);
  _ip_address_num = _ip_address_num << 8;
  _ip_address_num |= std::get<1>(*this);
  _ip_address_num = _ip_address_num << 8;
  _ip_address_num |= std::get<2>(*this);
  _ip_address_num = _ip_address_num << 8;
  _ip_address_num |= std::get<3>(*this);
  return _ip_address_num;
}
