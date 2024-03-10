#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "ip_address.h"
#include "utils.h"


/**
 * пройти все строчки файла, сплитить их по табуляции, первый элемент -- ip
 * адрес сохранить все ip адреса в массив ip адреса сохраняются в класс
 * IPAddress, методы:
 *  - static fromString
 *  - toString
 *  - toNumber
 *  - getByte
 *  -
 * сортируем в обратном порядке по числовому представлению ip адреса
 * (uint32_t), получаем отсортированный массив делаем 4 фильтра
 * (лямбда-функции):
 *  - пустой
 *  - первый байт равен 1
 *  - первый байт равен 46, а второй 70
 *  - любой байт равен 46
 * бежим по отсортированным адресам, применяем фильтры, если адрес подходит
 * под фильтр, выводим его
 */
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
    auto a = IPAddress::fromString(tokens[0]);
    ip_addresses.push_back(a);
  }
  std::sort(
      ip_addresses.begin(), ip_addresses.end(),
      [](IPAddress &a, IPAddress &b) { return a.toNumber() > b.toNumber(); });

  auto filter_I = [](IPAddress &a) { return true; };
  auto filter_II = [](IPAddress &a) { return std::get<0>(a) == 1; };
  auto filter_III = [](IPAddress &a) {
    return std::get<0>(a) == 46 && std::get<1>(a) == 70;
  };
  auto filter_IV = [](IPAddress &a) {
    return std::get<0>(a) == 46 || std::get<1>(a) == 46 || std::get<2>(a) == 46 ||
          std::get<3>(a) == 46;
  };

  print_filtered<IPAddress>(ip_addresses, filter_I);
  print_filtered<IPAddress>(ip_addresses, filter_II);
  print_filtered<IPAddress>(ip_addresses, filter_III);
  print_filtered<IPAddress>(ip_addresses, filter_IV);
  return 0;
}
