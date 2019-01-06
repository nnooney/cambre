////////////////////////////////////////////////////////////////////////////////
/// @file RenderInterface.cpp
/// @brief The interface used by the Application class to render graphics.
///
/// This file defines the interface methods available for applications to render
/// objects. This interface is meant to be implemented by a class; once an
/// object that implements this interface is instantiated, it can be attached to
/// the Application via addRenderer. Note that none of the renderer code will
/// execute until the Application is running.
////////////////////////////////////////////////////////////////////////////////

#include "RenderInterface.hpp"

void RenderInterface::initialize(void)
{
    // Do nothing.
}

void RenderInterface::wrapup(void)
{
    // Do nothing.
}
