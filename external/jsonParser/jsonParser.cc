#ifndef JSONPARSER_CC
#define JSONPARSER_CC

#include <boost/filesystem/fstream.hpp>
#include "jsonParser.hh"


/// Functions for converting basic types to/from json

jsonParser &to_json(const bool &value, jsonParser &json) {
  *((json_spirit::mValue *) &json) = json_spirit::mValue(value);
  return json;
}

jsonParser &to_json(const int &value, jsonParser &json) {
  *((json_spirit::mValue *) &json) = json_spirit::mValue(value);
  return json;
}

jsonParser &to_json(const double &value, jsonParser &json) {
  if(value != value) {
    return to_json("nan", json);
  }
  else if(value == 1.0 / 0.0) {
    return to_json("inf", json);
  }
  else if(value == -1.0 / 0.0) {
    return to_json("-inf", json);
  }
  else {
    *((json_spirit::mValue *) &json) = json_spirit::mValue(value);
    return json;
  }

}

jsonParser &to_json(const std::string &value, jsonParser &json) {
  *((json_spirit::mValue *) &json) = json_spirit::mValue(value);
  return json;
}

jsonParser &to_json(const char *value, jsonParser &json) {
  *((json_spirit::mValue *) &json) = json_spirit::mValue(value);
  return json;
}

jsonParser &to_json(const jsonParser &value, jsonParser &json) {
  return json = value;
}


void from_json(bool &value, const jsonParser &json) {
  try {
    value = json.get_bool();
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}

void from_json(int &value, const jsonParser &json) {
  try {
    value = json.get_int();
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}

void from_json(double &value, const jsonParser &json) {
  try {
    if(json.is_string()) {
      std::string str = json.get_str();
      if(str == "nan") {
        value = sqrt(-1.0);
      }
      else if(str == "inf") {
        value = 1.0 / 0.0;
      }
      else if(str == "-inf") {
        value = -1.0 / 0.0;
      }
      else {
        throw std::runtime_error("Expected json real, received string other than 'nan', 'inf', or '-inf': '" + str + "'");
      }
    }
    else {
      value = json.get_real();
    }
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}

void from_json(std::string &value, const jsonParser &json) {
  try {
    value = json.get_str();
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}

void from_json(jsonParser &value, const jsonParser &json) {
  try {
    value = json;
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}


/// jsonParser Functions

void jsonParser::read(std::istream &stream) {
  json_spirit::read_stream(stream, (json_spirit::mValue &) *this);
}

void jsonParser::read(const std::string &file_name) {
  std::ifstream stream(file_name.c_str());
  read(stream);
}

void jsonParser::read(const boost::filesystem::path &mypath) {
  boost::filesystem::ifstream stream(mypath);
  read(stream);
}

std::istream &operator>>(std::istream &stream, jsonParser &json) {
  json.read(stream);
  return stream;
}

/// Writes json to stream
void jsonParser::print(std::ostream &stream, unsigned int indent, unsigned int prec) const {
  json_spirit::write_stream((json_spirit::mValue &) *this, stream, indent, prec,
                            json_spirit::pretty_print | json_spirit::single_line_arrays);
};

std::ostream &operator<< (std::ostream &stream, const jsonParser &json) {
  json.print(stream);
  return stream;
}

/// Write json to file
void jsonParser::write(const std::string &file_name, unsigned int indent, unsigned int prec) const {
  std::ofstream file(file_name.c_str());
  print(file, indent, prec);
  file.close();
}

void jsonParser::write(const boost::filesystem::path &mypath, unsigned int indent, unsigned int prec) const {
  boost::filesystem::ofstream file(mypath);
  print(file, indent, prec);
  file.close();
}


/// Move down the JSON path

/// Return a reference to the sub-jsonParser (JSON value) with 'name' if it exists
///   If it does not exist, create it with value == 'null' and return a reference
jsonParser &jsonParser::operator[](const std::string &name) {

  try {

    json_spirit::mObject &obj = get_obj();
    json_spirit::mObject::iterator it = obj.find(name);

    // if 'name' not found, add it and with value 'null'
    if(it == obj.end()) {
      obj[name] = json_spirit::mValue();
    }
    return (jsonParser &) obj[name];
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}

/// Const access will throw if the 'name' doesn't exist
const jsonParser &jsonParser::operator[](const std::string &name) const {

  try {

    const json_spirit::mObject &obj = get_obj();
    json_spirit::mObject::const_iterator it = obj.find(name);

    // if 'name' not found, add it and with value 'null'
    if(it == obj.end()) {
      throw std::runtime_error("Const operator[] access, but " + name + " does not exist");
    }
    return (const jsonParser &) it->second;
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}

/// Return a reference to sub-jsonParser (JSON value) from index 'element' iff jsonParser is a JSON array
jsonParser &jsonParser::operator[](const int &element) {

  try {
    return (jsonParser &) get_array()[element];
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}

/// Const array access
const jsonParser &jsonParser::operator[](const int &element) const {

  try {
    return (const jsonParser &) get_array()[element];
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}


/// Type Checking Methods

/// Check if null type
bool jsonParser::is_null() const {
  return type() == json_spirit::null_type;
}

/// Check if bool type
bool jsonParser::is_bool() const {
  return type() == json_spirit::bool_type;
}

/// Check if int type
bool jsonParser::is_int() const {
  return type() == json_spirit::int_type;
}

/// Check if number type (not including int)
bool jsonParser::is_number() const {
  return type() == json_spirit::real_type;
}

/// Check if number type (not including int)
bool jsonParser::is_string() const {
  return type() == json_spirit::str_type;
}

/// Check if object type
bool jsonParser::is_obj() const {
  return type() == json_spirit::obj_type;
}

/// Check if array type
bool jsonParser::is_array() const {
  return type() == json_spirit::array_type;
}


/// Data Retrieval Methods


/// Returns iterator to beginning of JSON object or JSON array
jsonParser::iterator jsonParser::begin() {
  if(is_obj())
    return iterator(this, get_obj().begin());
  else if(is_array())
    return iterator(this, get_array().begin());
  else
    return iterator(this, 0);
}

/// Returns iterator to end of JSON object or JSON array
jsonParser::iterator jsonParser::end() {
  if(is_obj())
    return iterator(this, get_obj().end());
  else if(is_array())
    return iterator(this, get_array().end());
  else
    return iterator(this, 0);
}

/// Return iterator to JSON object value with 'name'
jsonParser::iterator jsonParser::find(const std::string &name) {
  try {
    return iterator(this, get_obj().find(name));
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}

/// Returns find('name') != end()
bool jsonParser::contains(const std::string &name) const {
  try {
    return (get_obj().find(name) != get_obj().end());
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}

/// Tries 'contain' for series of elements, T must dereference as std::string
template<class T>
bool jsonParser::contains(const T &begin, const T &end) const {
  T iter = begin;
  while(iter != end) {
    if(!contains(*iter)) {
      return false;
    }
    iter++;
  }
  return true;
}


/// Puts new 'null' element at end of array
int jsonParser::size() const {
  if(is_obj())
    return get_obj().size();
  else if(is_array())
    return get_array().size();
  else
    return 1;
}



/// Data Modification Methods

/// Puts new empty JSON object
jsonParser &jsonParser::put_obj() {
  return *this = json_spirit::mValue(json_spirit::mObject());
};

/// Puts new empty JSON array
jsonParser &jsonParser::put_array() {
  return *this = json_spirit::mValue(json_spirit::mArray());
}

/// Puts new empty JSON array
jsonParser &jsonParser::put_array(int N) {
  return *this = json_spirit::mValue(json_spirit::mArray(N));
}

/// Push back 'null' data to array
jsonParser &jsonParser::push_back() {
  get_array().push_back(json_spirit::mValue());
  return *this;
}

/// Puts 'null' data
jsonParser &jsonParser::put() {
  return *this = json_spirit::mValue();
}

#endif
