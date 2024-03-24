#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

void split(const std::string &str, char sep, std::vector<std::string> &seglist);

template <typename T>
void print_filtered(const std::vector<T> &container, bool filter(const T& a)) {
  std::for_each(container.begin(), container.end(), [&filter](const T& a) {
    if (filter(a))
      std::cout << a << std::endl;
  });
}
