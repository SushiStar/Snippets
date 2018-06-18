/*
 * This is the test program for loading process of a stl file
 * stl_reader is used in loading the file.
 * the smpl library is used in voxelizing the mesh.
 *
 * Finally the mesh surface is converted to the point clouds
 *
 * Author: Wei Du
 * Date: Jun/14/2018
 *
 */

#include <vector>
#include <iostream>
#include <fstream>
#include "stl_reader.h"
#include <eigen3/Eigen/Dense>
#include <smpl/geometry/voxelize.h>

using namespace std;
using namespace sbpl;
using namespace geometry;

int main(){
    
    // data storage
    std::vector<Eigen::Vector3d> vertices;
    std::vector<std::uint32_t> indices;
    std::vector<Eigen::Vector3d> voxels;
    double res = 0.025;     // in meters 
    vertices.clear();
    indices.clear();
    voxels.clear();


    // load stl file
	std::vector<float> coords, normals;
	std::vector<std::uint32_t> tris, solids;

	try {
        const char* sEnvFile = "mount.stl";

        // triangles are loaded successfully
		stl_reader::ReadStlFile (sEnvFile, coords, normals, tris, solids);


		const size_t numTris = tris.size() / 3;

		for(size_t itri = 0; itri < numTris; ++itri) {

            indices.push_back((std::uint32_t)itri*3 + 0);
            indices.push_back((std::uint32_t)itri*3 + 1);
            indices.push_back((std::uint32_t)itri*3 + 2);

            for(size_t icorner = 0; icorner < 3; ++icorner) {
                float* c = &coords[3 * tris [3 * itri + icorner]];
                
                Eigen::Vector3d currentVertex((double)c[0],(double)c[1], (double)c[2]);
                vertices.push_back(currentVertex);
            }

        }   // end for 

	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

    bool fill = false;

    std::cout<< "number of triangles: "<< indices.size()/3<<std::endl;
    VoxelizeMesh(vertices, indices, res, voxels, fill);

    std::cout<< "finish voxelizing mesh." << std::endl;
    


    // write those voxels into a txt file and check
    std::ofstream vxls;
    vxls.open("voxels.txt");
    for(auto voxel:voxels){
        vxls << voxel.x() << " " << voxel.y() << " " << voxel.z() <<std::endl;             
    }
 
    return 0;
}
