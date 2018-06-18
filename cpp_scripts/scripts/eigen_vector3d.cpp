//
//test the format of Eigen/vector3d
//
//

#include <iostream>
#include <eigen3/Eigen/Dense>

int main(){

    Eigen::Vector3d a(0.1, 0.2, 0.3);

    std::cout<<a.x()<<" "<<a.y()<<" "<<a.z()<<std::endl;

    return 0;
}
