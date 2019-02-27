////////////////////////////////////////////////////////////////////////////////
/// @file DynamicObjectInterface.hpp
/// @brief An interface that combines the update and render interfaces.
///
/// This file contains the dynamic object interface, which is the base interface
/// for handling both updates and renders.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_DYNAMIC_OBJECT_INTERFACE_H_
#define _CAMBRE_DYNAMIC_OBJECT_INTERFACE_H_

#include "RenderInterface.hpp"
#include "UpdateInterface.hpp"

class DynamicObjectInterface : public RenderInterface, public UpdateInterface
{
public:
};

#endif
