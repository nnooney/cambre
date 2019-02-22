////////////////////////////////////////////////////////////////////////////////
/// @file Region.hpp
/// @brief A class to handle multiple chunks.
///
/// This file contains the Region class. Multiple chunks get organized into a
/// region. The region is responsible for maintaining the list of chunks as well
/// as loading and unloading the chunks.
////////////////////////////////////////////////////////////////////////////////

#ifndef _NOONCRAFT_REGION_H_
#define _NOONCRAFT_REGION_H_

#include <vector>

#include "Chunk.hpp"

/// @class Region
/// @brief A class to handle multiple chunks.
///
/// A Region is a logical grouping of chunks. The chunks belonging to a region
/// can be updated over time. One of the primary regions is the region around
/// the player.
class Region
{
public:
    Region(void);

private:
    /// @brief The array of chunks to render.
    std::vector<Chunk> mChunks;
};

#endif
