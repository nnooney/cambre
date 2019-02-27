////////////////////////////////////////////////////////////////////////////////
/// @file EventObserver.hpp
/// @brief An observer pattern implementation to receive events.
///
/// This file contains a base class representation of the interface used to
/// observe events that are passed throughout the application. The input manager
/// is one source of generating events.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_EVENT_OBSERVER_H_
#define _CAMBRE_EVENT_OBSERVER_H_

#include "Event.hpp"

/// @class EventObserver
/// @brief A class to observe events.
///
/// This is the base class for listening to events. All subclasses must
/// implement the onEvent method to receive an event.
class EventObserver
{
public:
    virtual ~EventObserver();
    virtual void onEvent(ApplicationEventStruct event) = 0;
};

#endif
