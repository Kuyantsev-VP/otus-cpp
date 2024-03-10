#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>



void split(const std::string &str, char sep,
           std::vector<std::string> &seglist);


template <typename T>
void print_filtered(std::vector<T> container, bool filter(T &a)) {
  std::for_each(container.begin(), container.end(), [&filter](T &a) {
    if (filter(a))
      std::cout << a << std::endl;
  });
}
