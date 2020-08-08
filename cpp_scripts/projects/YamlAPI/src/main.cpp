/*
 *
 *
 *
 */

// STL include
#include <iostream>
#include <string>

// other dependencies
#include <yaml-cpp/yaml.h>

int main(int argc, char** argv) {

  YAML::Node config = YAML::LoadFile(argv[1]);

  std::string name = config["name"].as<std::string>();
  double age = config["age"].as<double>();

  std::cout << "Name: "<< name << ", age: " << age << std::endl;
  return 0;
}
