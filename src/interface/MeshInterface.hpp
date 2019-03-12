////////////////////////////////////////////////////////////////////////////////
/// @file MeshInterface.hpp
/// @brief The interface to provide a mesh for converting data into geometry.
///
/// This file defines the mesh interface. A mesh interface can generate geometry
/// from voxel data and provide it to a renderer for drawing.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_MESH_INTERFACE_H_
#define _CAMBRE_MESH_INTERFACE_H_

class MeshInterface
{
public:
    /// @brief Generate the mesh.
    ///
    /// This function generates a mesh from voxel data.
    virtual void generate(uint8_t aData[16][16][16], int size) = 0;
};

#endif
