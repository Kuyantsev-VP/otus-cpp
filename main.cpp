#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

typedef size_t byte;
typedef std::tuple<byte, byte, byte, byte> ip_tuple;

void split(const std::string &str, char sep,
           std::vector<std::string> &seglist) {
  std::stringstream str_stream(str);
  std::string segment;
  while (std::getline(str_stream, segment, sep)) {
    seglist.push_back(segment);
  }
}

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

template <typename T>
void print_filtered(std::vector<T> container, bool filter(T &a)) {
  std::for_each(container.begin(), container.end(), [&filter](T &a) {
    if (filter(a))
      std::cout << a << std::endl;
  });
}

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
