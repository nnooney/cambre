////////////////////////////////////////////////////////////////////////////////
/// @file Region.hpp
/// @brief A class to handle multiple chunks.
///
/// This file contains the Region class. Multiple chunks get organized into a
/// region. The region is responsible for maintaining the list of chunks as well
/// as loading and unloading the chunks.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_REGION_H_
#define _CAMBRE_REGION_H_

#include <queue>
#include <unordered_map>

#include <glm/glm.hpp>

#include "CameraController.hpp"
#include "Chunk.hpp"
#include "DynamicObjectInterface.hpp"
#include "InputManager.hpp"
#include "ShaderProgram.hpp"
#include "Specialization.hpp"

/// @class Region
/// @brief A class to handle multiple chunks.
///
/// A Region is a logical grouping of chunks. The chunks belonging to a region
/// can be updated over time. One of the primary regions is the region around
/// the player.
class Region : public DynamicObjectInterface
{
public:
    Region(void);
    ~Region(void);
    void initialize(void);
    void update(void);
    void render(void);

    /// @brief Use the ShaderProgram for rendering.
    ///
    /// This call sets the shader for use when rendering the region.
    void useShader(ShaderProgram &shader);

    /// @brief Use the CameraController for rendering.
    ///
    /// This call sets the camera controller for use when rendering the region.
    void useCameraController(CameraController &cc);

    /// @brief Register to listen for inputs.
    ///
    /// This function attaches the region to an input manager so it can be
    /// updated via user input.
    void registerWith(InputManager &manager);

private:
    /// @brief The set of chunks managed by the Region.
    std::unordered_map<glm::ivec3, Chunk*> mChunks;

    /// @brief The distance used to render chunks.
    unsigned int mChunkDistance;

    /// @brief The rate used to load/unload chunks.
    unsigned int mChunkLoadRate;
    unsigned int mChunkUnloadRate;

    /// @brief The queues used to keep track of chunks to load and unload.
    std::queue<glm::ivec3> mChunkLoadList;
    std::queue<glm::ivec3> mChunkRemoveList;

    /// @brief The Shader Program used by this application.
    ShaderProgram mShaderProgram;
    GLuint mUniformVP;
    GLuint mUniformModel;

    /// @brief The Camera Controller that gives life to the camera.
    CameraController mCameraController;

    /// @brief Checks a chunk and it's neighbors for loading/unloading.
    ///
    /// This function is used to mark chunks for loading/unloading.
    void updateChunkLists(std::pair<glm::ivec3, Chunk*> ci);

    /// @brief The load algorithm for chunk loading/unloading.
    ///
    /// This function represents the algorithm for loading or unloading a chunk.
    /// Given a chunk's coordinates, this function will return true if the
    /// chunk should be loaded, or false if the chunk should be unloaded.
    bool chunkLoadAlgorithm(glm::ivec3 coords);

    /// @brief Loads chunks from the chunk load list.
    ///
    /// This function will load chunks from the list and insert them into the
    /// chunk map.
    void loadChunks(void);

    /// @brief Unloads chunks from the map.
    ///
    /// This function will unload chunks from the map based upon the chunk
    /// remove list.
    void unloadChunks(void);
};

#endif
