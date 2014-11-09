#ifndef JSONPARSER_HH
#define JSONPARSER_HH

#include "json_spirit/json_spirit_reader_template.h"
#include "json_spirit/json_spirit_writer_template.h"
#include <boost/filesystem.hpp>
#include <exception>
#include <complex>

class jsonParserIterator;

/// jsonParser allows for reading / writing JSON data
///
/// JSON consists of values, which can be of type:
///     object, array, float, int, str, null, bool
///   object: map/dict of <string, JSON value>
///   array: vector/list of JSON values
///
///   value[string] -> value iff object
///   value[int] -> value iff array
///   value.get<type>() -> type must be correct type
///
/// Assumes functions exist for each type T to read/write:
///   jsonParser& to_json( const T &value, jsonParser &json)
///   void from_json( T &value, const jsonParser &json);
///
///   These functions exist for basic types (bool, int, double, std::string),
///   and the containers:
///      Eigen::MatrixXd, CASM::Array, CASM::Matrix, CASM::Vector,
///   So if they also exist for the type being contained,
///   you can read/write the entire object as a JSON array or nested JSON arrays
///
/// Simple Usage:
///
///   Reading data from a JSON file:
///
///     jsonParser json("myfile.json");
///
///   Three ways to get data of type T:
///
///     T t;
///     from_json(t, json["path"]["to"]["object"]["data"]);  <-- use [std::string] for JSON values of any type
///     t = json["path"]["to"]["object"]["data"].get<T>();
///     t = from_json<T>(json["path"]["to"]["array"][0]);   <-- use [int] for JSON arrays only
///
///   Check if 'name' in JSON object:
///
///     if( json.contains("other_data") )
///       from_json( array, json["other_data"]);
///
///   Writing data to a JSON file:
///
///     jsonParser json;
///     json["mydata"].put(mydata);        <-- if ["mydata"] does not exist, it is created, else overwrites
///     json["more_data"].put(more_data);
///
///     ofstream file("myfile.json");
///     json.write(file);
///     file.close();
///
class jsonParser : public json_spirit::mValue {

public:
  /// Class constructors

  /// Create a new empty jsonParser
  jsonParser() : json_spirit::mValue(json_spirit::mObject()) {
  }

  /// Create a jsonParser from a stream
  jsonParser(std::istream &stream) {
    read(stream);
  }

  /// Create a jsonParser from a file name string
  jsonParser(const std::string &file_name) {
    read(file_name);
  }

  /// Create a jsonParser from a file path
  jsonParser(const boost::filesystem::path &mypath) {
    read(mypath.string());
  }

  /// Reads the json file
  void read(std::istream &stream);
  void read(const std::string &file_name);
  void read(const boost::filesystem::path &mypath);

  /// Value level printing options:
  /// Force array printing as column/row
  /// Remove trailing zeros for real (double) values
  using json_spirit::mValue::set_force_column;
  using json_spirit::mValue::set_force_row;
  using json_spirit::mValue::set_remove_trailing_zeros;
  using json_spirit::mValue::unset_force_column;
  using json_spirit::mValue::unset_force_row;
  using json_spirit::mValue::unset_remove_trailing_zeros;
  using json_spirit::mValue::operator==;

  bool operator!=(const jsonParser &json) {
    return !(json_spirit::mValue::operator==(json));
  }

  /// Print json to stream
  void print(std::ostream &stream, unsigned int indent = 2, unsigned int prec = 12) const;

  /// Write json to file
  void write(const std::string &file_name, unsigned int indent = 2, unsigned int prec = 12) const;
  void write(const boost::filesystem::path &mypath, unsigned int indent = 2, unsigned int prec = 12) const;


  /// Navigate the JSON data:

  /// Return a reference to the sub-jsonParser (JSON value) with 'name' if it exists
  ///   If it does not exist, create it with value == 'null' and return a reference to it
  jsonParser &operator[](const std::string &name);
  const jsonParser &operator[](const std::string &name) const;
  /// Return a reference to the sub-jsonParser (JSON value) from index 'element' iff this jsonParser is a JSON array
  jsonParser &operator[](const int &element);
  const jsonParser &operator[](const int &element) const;


  /// Methods for iterating and checking what is in the json:
  typedef jsonParserIterator iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef jsonParser value_type;
  typedef jsonParser *pointer;
  typedef jsonParser &reference;

  /// Returns iterator to beginning of JSON object or JSON array
  iterator begin();
  /// Returns iterator to end of JSON object or JSON array
  iterator end();

  /// Return iterator to JSON object value with 'name'
  iterator find(const std::string &name);
  /// Returns find('name') != end()
  bool contains(const std::string &name) const;

  /// Tries 'contain' for series of elements, T must dereference as std::string
  template<class T>
  bool contains(const T &begin, const T &end) const;

  /// Type Checking Methods
  bool is_null() const;
  bool is_bool() const;
  bool is_int() const;
  bool is_number() const;
  bool is_string() const;
  bool is_obj() const;
  bool is_array() const;



  /// Returns array size if *this is a JSON array, object size if *this is a JSON object
  int size() const;


  /// Data-retrieval Methods

  /// Get data from json, for any type T for which 'void from_json( T &value, const jsonParser &json)' is defined
  ///   Call using: T t = json.get<T>();
  template< class T >
  T get() const;


  /// Data addition Methods (Overwrites any existing data with same 'name')

  /// Puts new empty JSON object
  jsonParser &put_obj();

  /// Puts new empty JSON array
  jsonParser &put_array();
  /// Puts new JSON array
  jsonParser &put_array(int N);
  /// Puts new 'null' element at end of array
  jsonParser &push_back();
  /// Puts new valued element at end of array of any type T for which 'jsonParser& to_json( const T &value, jsonParser &json)' is defined
  template< class T >
  jsonParser &push_back(const T &value);


  /// Puts 'null' data
  jsonParser &put();
  /// Puts data of any type T for which 'jsonParser& to_json( const T &value, jsonParser &json)' is defined (same as 'operator=')
  template< class T >
  jsonParser &put(const T &value);


  /// Alternatives to 'put', using '=' operator: 'json = T'

  /// Puts data of any type T for which 'jsonParser& to_json( const T &value, jsonParser &json)' is defined (same as 'put')
  template< class T >
  jsonParser &operator=(const T &value);
  /// Returns an empty json object
  static jsonParser object() {
    jsonParser json;
    return json = json_spirit::mValue(json_spirit::mObject());
  }
  /// Returns an empty json array
  static jsonParser array() {
    jsonParser json;
    return json = json_spirit::mValue(json_spirit::mArray());
  }
  /// Returns an empty json array
  static jsonParser array(int N) {
    jsonParser json;
    return json = json_spirit::mValue(json_spirit::mArray(N));
  }
  /// Returns a null JSON value
  static jsonParser null() {
    jsonParser json;
    return json = json_spirit::mValue();
  }

private:

  jsonParser &operator=(const json_spirit::mValue &value) {
    this->json_spirit::mValue::operator=(value);
    return *this;
  }


};

std::ostream &operator<< (std::ostream &stream, const jsonParser &json);
std::istream &operator>>(std::istream &stream, jsonParser &json);

/// To JSON for basic types
jsonParser &to_json(const bool &value, jsonParser &json);
jsonParser &to_json(const int &value, jsonParser &json);
jsonParser &to_json(const double &value, jsonParser &json);
jsonParser &to_json(const std::string &value, jsonParser &json);
jsonParser &to_json(const char *value, jsonParser &json);
jsonParser &to_json(const jsonParser &value, jsonParser &json);

/// From JSON for basic types
void from_json(bool &value, const jsonParser &json);
void from_json(int &value, const jsonParser &json);
void from_json(double &value, const jsonParser &json);
void from_json(std::string &value, const jsonParser &json);
void from_json(jsonParser &value, const jsonParser &json);

/// To JSON for complex
template<typename T>
jsonParser &to_json(const std::complex<T> &value, jsonParser &json) {
  json.put_obj();
  json["real"] = value.real();
  json["imag"] = value.imag();
  return json;
}

/// From JSON for complex
template<typename T>
void from_json(std::complex<T> &value, const jsonParser &json) {
  try {
    value = std::complex<T>(json["real"].get<T>(), json["imag"].get<T>());
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}

/// Convenience function, enables json.get<T>() if T::T() exists
template< class T>
T from_json(const jsonParser &json) {
  T value;
  from_json(value, json);
  return value;
}


/// jsonParser bidirectional Iterator class
///   Can iterate over a JSON object or JSON array or JSON value (though this is only one value)
///   When iterating over a JSON object, can return the 'name' of the current 'name':value pair being pointed at
class jsonParserIterator {

  jsonParser *parser;

  json_spirit::Value_type type;

  json_spirit::mObject::iterator obj_iter;

  json_spirit::mArray::iterator array_iter;

  int val_iter;

public:

  jsonParserIterator() {}

  jsonParserIterator(const jsonParserIterator &iter)
    : parser(iter.parser), type(iter.type), obj_iter(iter.obj_iter), array_iter(iter.array_iter), val_iter(iter.val_iter) {
  }

  jsonParserIterator &operator=(jsonParserIterator iter) {
    swap(*this, iter);
    return *this;
  }

  jsonParserIterator(jsonParser *j, const json_spirit::mObject::iterator &iter)
    : parser(j), type(json_spirit::obj_type), obj_iter(iter) {
  }

  jsonParserIterator(jsonParser *j, const json_spirit::mArray::iterator &iter)
    : parser(j), type(json_spirit::array_type), array_iter(iter) {
  }

  jsonParserIterator(jsonParser *j, const int &iter)
    : parser(j), type(json_spirit::null_type), val_iter(iter) {
  }

  jsonParser &operator*() {
    if(type == json_spirit::obj_type)
      return (jsonParser &) obj_iter->second;
    else if(type == json_spirit::array_type)
      return (jsonParser &) * array_iter;
    else
      return *parser;
  }

  jsonParser *operator->() {
    if(type == json_spirit::obj_type)
      return (jsonParser *) &obj_iter->second;
    else if(type == json_spirit::array_type)
      return (jsonParser *) & (*array_iter);
    else
      return parser;
  }

  bool operator==(const jsonParserIterator &iter) {
    if(parser != iter.parser)
      return false;

    if(type == json_spirit::obj_type)
      return obj_iter == iter.obj_iter;
    else if(type == json_spirit::array_type)
      return array_iter == iter.array_iter;
    else
      return true;
  }

  bool operator!=(const jsonParserIterator &iter) {
    return !(*this == iter);
  }

  jsonParserIterator &operator++() {
    if(type == json_spirit::obj_type) {
      ++obj_iter;
      return *this;
    }
    else if(type == json_spirit::array_type) {
      ++array_iter;
      return *this;
    }
    else {
      ++val_iter;
      return *this;
    }
  }

  jsonParserIterator operator++(int) {

    jsonParserIterator cp(*this);

    if(type == json_spirit::obj_type) {
      ++obj_iter;
      return cp;
    }
    else if(type == json_spirit::array_type) {
      ++array_iter;
      return cp;
    }
    else {
      ++val_iter;
      return cp;
    }
  }

  jsonParserIterator &operator--() {
    if(type == json_spirit::obj_type) {
      --obj_iter;
      return *this;
    }
    else if(type == json_spirit::array_type) {
      --array_iter;
      return *this;
    }
    else {
      --val_iter;
      return *this;
    }
  }

  jsonParserIterator operator--(int) {

    jsonParserIterator cp(*this);

    if(type == json_spirit::obj_type) {
      --obj_iter;
      return cp;
    }
    else if(type == json_spirit::array_type) {
      --array_iter;
      return cp;
    }
    else {
      --val_iter;
      return cp;
    }
  }

  /// When iterating over a JSON object, returns the 'name' of the 'name':value pair the iterator is pointing at
  std::string name() {
    if(type == json_spirit::obj_type)
      return obj_iter->first;
    else
      throw std::runtime_error("Calling 'name' on non-object jsonParserIterator");
  }

  friend void swap(jsonParserIterator &a, jsonParserIterator &b) {
    using std::swap;

    std::swap(a.parser, b.parser);
    swap(a.type, b.type);
    swap(a.obj_iter, b.obj_iter);
    swap(a.array_iter, b.array_iter);
    swap(a.val_iter, b.val_iter);
  }
};

/// Puts new valued element at end of array of any type T for which 'jsonParser& to_json( const T &value, jsonParser &json)' is defined
template< class T >
jsonParser &jsonParser::push_back(const T &value) {
  try {
    jsonParser json;
    get_array().push_back(to_json(value, json));
    return *this;
  }
  catch(...) {
    /// re-throw exceptions
    throw;
  }
}

/// Get data from json, for any type T for which 'void from_json( T &value, const jsonParser &json)' is defined
template< class T >
T jsonParser::get() const {
  return from_json<T>(*this);
}

/// Puts data of any type T for which 'jsonParser& to_json( const T &value, jsonParser &json)' is defined (same as operator=)
template <typename T>
jsonParser &jsonParser::put(const T &value) {
  return to_json(value, *this);
}

/// Puts data of any type T for which 'jsonParser& to_json( const T &value, jsonParser &json)' is defined (same as put)
template <typename T>
jsonParser &jsonParser::operator=(const T &value) {
  return to_json(value, *this);
}




#endif
