////////////////////////////////////////////////////////////////////////////////
/// @file RenderInterface.hpp
/// @brief The interface used by the Application class to render graphics.
///
/// This file defines the interface methods available for applications to render
/// objects. This interface is meant to be implemented by a class; once an
/// object that implements this interface is instantiated, it can be attached to
/// the Application via addRenderer. Note that none of the renderer code will
/// execute until the Application is running.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_RENDER_INTERFACE_H_
#define _CAMBRE_RENDER_INTERFACE_H_

#include "LifecycleInterface.hpp"

class RenderInterface : public virtual LifecycleInterface
{
public:
    /// @brief The render function, called each iteration of the main loop.
    ///
    /// This is the main function that a renderable object must implement in
    /// order to be used by the application. It is called repeatedly in the main
    /// display loop.
    virtual void render(void) = 0;
};

#endif
