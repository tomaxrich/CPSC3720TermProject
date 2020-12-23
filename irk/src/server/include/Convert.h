#ifndef CONVERT_H
#define CONVERT_H

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class Convert {
 public:
  Convert() {}
  json convertToJson(std::string s);
  std::string convertToString(json j);
  ~Convert() {}
};
#endif  // CONVERT_H
