////////////////////////////////////////////////////////////////////////////////
/// @file Specialization.hpp
/// @brief Specialization of standard library functions.
///
/// This file contains specializations of standard library functions. These
/// functions allow custom types to be used in the standard template library.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_SPECIALIZATION_H_
#define _CAMBRE_SPECIALIZATION_H_

#include <functional>

#include <glm/glm.hpp>

namespace std
{
    // This template
    template<> struct hash<glm::ivec3>
    {
        typedef glm::ivec3 argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& a) const noexcept
        {
            // Use the C++ builtin hashing algorithm on each method and combine
            // the hashes.
            result_type h = std::hash<int>()(a.x);
            h ^= std::hash<int>()(a.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= std::hash<int>()(a.z) + 0x9e3779b9 + (h << 6) + (h >> 2);
            return h;
        }
    };
}

#endif
