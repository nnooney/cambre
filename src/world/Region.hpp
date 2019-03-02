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

#include <unordered_map>

#include <glm/glm.hpp>

#include "Chunk.hpp"
#include "DynamicObjectInterface.hpp"
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
private:
    /// @brief The set of chunks managed by the Region.
    std::unordered_map<glm::ivec3, Chunk*> mChunks;
};

#endif
