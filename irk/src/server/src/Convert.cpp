#include <nlohmann/json.hpp>
#include <string>
#include "Convert.h"
#include <iostream>

using json = nlohmann::json;

json Convert::convertToJson(std::string s) {
  auto j3 = json::parse(s);
  return j3;
}

std::string Convert::convertToString(json j) {
  return j.dump();
}
