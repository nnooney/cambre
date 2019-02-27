////////////////////////////////////////////////////////////////////////////////
/// @file Event.hpp
/// @brief Data to manage the logical events released by the input manager.
///
/// This file contains data that relates to events emitted by the input manager.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_EVENT_H_
#define _CAMBRE_EVENT_H_

typedef enum ApplicationEventEnum
{
    AE_NO_EVENT = 0,
    AE_MOVE_FORWARD,
    AE_MOVE_BACKWARD,
    AE_MOVE_LEFT,
    AE_MOVE_RIGHT,
    AE_MOVE_UP,
    AE_MOVE_DOWN,
    AE_LOOK_AROUND,
    AE_MAX_EVENT_ENUM
} app_event_enum_t;

typedef enum ApplicationEventType
{
    AE_NONE = 0,
    AE_BEGIN,
    AE_END,
    AE_REPEAT,
    AE_SINGLE,
    AE_MAX_EVENT_TYPE_ENUM
} app_event_type_t;

typedef struct ApplicationEventAxisStruct
{
    double x;
    double y;
    double z;
} app_event_axis_t;

typedef struct ApplicationEventDataStruct
{
    app_event_axis_t axis;
} app_event_data_t;

typedef struct ApplicationEventStruct
{
    app_event_enum_t code;
    app_event_type_t type;
    app_event_data_t data;
} app_event_struct_t;

#endif
