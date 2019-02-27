////////////////////////////////////////////////////////////////////////////////
/// @file LifecycleInterface.hpp
/// @brief An interface that implements the lifecycle of objects.
///
/// This file implements the interface for the lifecycle of objects as they are
/// used throughout the Application. Each lifecycle method is described in
/// greater detail below.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_LIFECYCLE_INTERFACE_H_
#define _CAMBRE_LIFECYCLE_INTERFACE_H_

class LifecycleInterface
{
public:
    /// @brief The initialize function, called once before the main loop.
    ///
    /// This function allows any variables to be set up, buffers to be created,
    /// and any other operations that need to be performed only once before the
    /// main loop is run.
    virtual void initialize(void);

    /// @brief The wrapup function, called once after exiting the main loop.
    ///
    /// This function is called once the main loop exits, which allows the
    /// object to wrapup any resources that may have been created during
    /// initialization.
    virtual void wrapup(void);
};

#endif
