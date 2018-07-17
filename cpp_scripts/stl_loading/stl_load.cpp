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
#include <smpl/geometry/voxelize.h>


int main(){

    // load the stl file
    try {
        stl_reader::StlMesh <float, unsigned int> mesh ("mount.stl");

        for(size_t isolid = 0; isolid < mesh.num_solids(); ++isolid) {
            std::cout << "solid " << isolid << std::endl;

            for(size_t itri = mesh.solid_tris_begin(isolid);
                    itri < mesh.solid_tris_end(isolid); ++itri)
            {
                const float* n = mesh.tri_normal (itri);
                std::cout	<< "normal of triangle " << itri << ": "
                    << "(" << n[0] << ", " << n[1] << ", " << n[2] << ")\n";
            }
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // voxelize the mesh


    return 0;
}
