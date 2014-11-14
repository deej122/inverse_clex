#include "jsonParser.hh"

// An example of writing and reading json
int main(int argc, char *argv[]) {
  
  // Create a JSON object
  jsonParser json;
  json["a"] = 6;
  json["b"] = jsonParser::object();
  json["b"]["c"] = "a_string";
  json["b"]["d"] = 10;
  json["e"] = jsonParser::array();
  json["e"].push_back(1);
  json["e"].push_back(2);
  json["e"].push_back("hi");
  
  // Write the JSON object to a file
  json.write(std::string("example.json"));
  std::cout << "Wrote example.json" << std::endl;
  
  // Read the JSON file
  json.read(std::string("example.json"));
  std::cout << "Read example.json:" << std::endl;
  std::cout << json << std::endl << std::endl;
  
  // Access the contents of the JSON
  std::cout << "json[\"a\"]: " << json["a"].get<int>() << std::endl;
  int b_d;
  from_json( b_d, json["b"]["d"]);
  std::cout << "json[\"b\"][\"d\"]: " << b_d << std::endl;
  std::cout << "json[\"e\"][\"0\"]: " << json["e"][0].get<int>() << std::endl;
  std::cout << "json[\"e\"][\"0\"] as double: " << json["e"][0].get<double>() << std::endl;
  std::cout << "json[\"e\"][\"2\"] is int?: " << json["e"][2].is_int() << std::endl;
  std::cout << "json[\"e\"][\"2\"]: " << json["e"][2].get<std::string>() << std::endl;
  
  return 0;
}