#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "ip_address.h"
#include "utils.h"


int main() {
  std::vector<IPAddress> ip_addresses;
  ip_addresses.reserve(1000);
  std::ifstream infile("ip_filter.tsv");
  std::string line;
  while (std::getline(infile, line)) {
    if (line.size() == 0)
      break;
    std::vector<std::string> tokens;
    split(line, '\t', tokens);
    auto ip_address = IPAddress::fromString(tokens[0]);
    ip_addresses.push_back(ip_address);
  }

  std::sort(ip_addresses.begin(), ip_addresses.end());

  auto filter_I = [](const IPAddress &a) { return true; };
  auto filter_II = [](const IPAddress &a) { return a[0] == 1; };
  auto filter_III = [](const IPAddress &a) { return a[0] == 46 && a[1] == 70; };
  auto filter_IV = [](const IPAddress &a) {
    return a[0] == 46 || a[1] == 46 || a[2] == 46 || a[3] == 46;
  };

  print_filtered<IPAddress>(ip_addresses, filter_I);
  print_filtered<IPAddress>(ip_addresses, filter_II);
  print_filtered<IPAddress>(ip_addresses, filter_III);
  print_filtered<IPAddress>(ip_addresses, filter_IV);
  return 0;
}
