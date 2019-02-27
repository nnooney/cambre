////////////////////////////////////////////////////////////////////////////////
/// @file UpdateInterface.hpp
/// @brief The interface used by the Application class to handle updates.
///
/// This file defines the interface methods available for applications to update
/// objects. This interface is meant to be implemented by a class; once an
/// object that implements this interface is instantiated, it can be attached to
/// the Application via addUpdater. Note that none of the updater code will
/// execute until the Application is running.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_UPDATE_INTERFACE_H_
#define _CAMBRE_UPDATE_INTERFACE_H_

#include "LifecycleInterface.hpp"

class UpdateInterface : public virtual LifecycleInterface
{
public:
    /// @brief The update function, called each iteration of the main loop.
    ///
    /// This is the main function that a updateable object must implement in
    /// order to be used by the application. It is called repeatedly in the main
    /// display loop.
    virtual void update(void) = 0;
};

#endif
