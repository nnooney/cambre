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

#ifndef _NOONCRAFT_RENDER_INTERFACE_H_
#define _NOONCRAFT_RENDER_INTERFACE_H_

class RenderInterface
{
public:
    /// @brief The initialize function, called once before the main loop.
    ///
    /// This function allows any variables to be set up, buffers to be created,
    /// and any other operations that need to be performed only once before the
    /// main loop to be run.
    virtual void initialize(void);

    /// @brief The render function, called each iteration of the main loop.
    ///
    /// This is the main function that a renderable object must implement in
    /// order to be used by the application. It is called repeatedly in the main
    /// display loop.
    virtual void render(void) = 0;

    /// @brief The wrapup function, called once after exiting the main loop.
    ///
    /// This function is called once the main loop exits, which allows the
    /// renderer to teardown any objects that may have been created during
    /// initialization.
    virtual void wrapup(void);
};

#endif
