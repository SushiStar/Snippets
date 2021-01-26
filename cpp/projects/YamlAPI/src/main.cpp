/*
 *
 *
 *
 */

// STL include
#include <iostream>
#include <string>
#include <vector>

// other dependencies
#include <yaml-cpp/yaml.h>

int main(int argc, char** argv) {

  YAML::Node config = YAML::LoadFile(argv[1]);

  int freq = config["Frequency"].as<int>();
  std::cout << "Frequency: " << freq << std::endl;

  const YAML::Node &obslist = config["Obstacle List"];

  for (YAML::const_iterator it = obslist.begin(); it != obslist.end(); ++it) {
    const YAML::Node& obj(*it);
    std::cout << "Type: " << obj["type"].as<std::string>() << std::endl;

    std::vector<double> pose(obj["pose"].as<std::vector<double>>());
    std::cout << "Pose: " << pose[0] << " " << pose[1] << " " << pose[2] << std::endl;

    std::cout << "Velocity: " << obj["velocity"].as<double>() << std::endl;
    std::cout << "Acceleration: " << obj["acceleration"].as<double>() << std::endl << std::endl;
  }

  return 0;
}
