#include "ip_address.h"
#include "utils.h"

IPAddress::IPAddress(int byte_0, int byte_1, int byte_2, int byte_3)
    : array<byte, 4>{(byte)byte_0, (byte)byte_1, (byte)byte_2, (byte)byte_3} {}

IPAddress IPAddress::fromString(const std::string &ip_address_str) {
  std::vector<std::string> bytes_str;
  split(ip_address_str, '.', bytes_str);
  IPAddress ip_address = {
      (byte)std::stoi(bytes_str[0]), (byte)std::stoi(bytes_str[1]),
      (byte)std::stoi(bytes_str[2]), (byte)std::stoi(bytes_str[3])};
  return ip_address;
}

bool IPAddress::operator<(const IPAddress &other) const {
  return std::lexicographical_compare(other.begin(), other.end(), this->begin(),
                                      this->end());
}
