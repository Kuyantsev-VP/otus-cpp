#include "ip_address.h"
#include "utils.h"

IPAddress IPAddress::fromString(const std::string &ip_address_str) {
  std::vector<std::string> bytes_str;
  split(ip_address_str, '.', bytes_str);
  return IPAddress{
      (byte)std::stoi(bytes_str[0]), (byte)std::stoi(bytes_str[1]),
      (byte)std::stoi(bytes_str[2]), (byte)std::stoi(bytes_str[3])};
}
