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
		stl_reader::ReadStlFile ("mount.stl", coords, normals, tris, solids);


		const size_t numTris = tris.size() / 3;
        // loop through triangles
        // itri: indices of the current triangle
		for(size_t itri = 0; itri < numTris; ++itri) {

			//std::cout << "coordinates of triangle " << itri << ": ";
            //std::cout<< "tirangle index: " << itri;
            indices.push_back((std::uint32_t)itri);

            //icorner: the ith corner of current triangle
            for(size_t icorner = 0; icorner < 3; ++icorner) {
                float* c = &coords[3 * tris [3 * itri + icorner]];
                //std::cout<<" push_back vertices   ";
                //std::cout << "(" << c[0] << ", " << c[1] << ", " << c[2] << ") "<< std::endl;
                Eigen::Vector3d currentVertex((double)c[0],(double)c[1], (double)c[2]);
                vertices.push_back(currentVertex);
		  	}

            // norm of current triangle
/*
 *            std::cout << std::endl;
 *            float* n = &normals [3 * itri];
 *            std::cout	<< "normal of triangle " << itri << ": "
 *                << "(" << n[0] << ", " << n[1] << ", " << n[2] << ")\n";
 *
 */
		}   // end for 


	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

    bool fill = false;

    std::cout<< "index size: "<< indices.size() %3<<std::endl;

    VoxelizeMesh(vertices, indices, res, voxels, fill);
    std::cout<< "number of triangles: "<< indices.size()<<std::endl;
    std::cout<< "number of triangles: "<< voxels.size()<<std::endl;

    // convert mesh data into voxels

    std::cout<< "finish voxelizing mesh." << std::endl;
    
 
    return 0;
}
