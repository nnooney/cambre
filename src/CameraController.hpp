////////////////////////////////////////////////////////////////////////////////
/// @file CameraController.hpp
/// @brief A class that generates camera commands from events.
///
/// This class listens for applicable camera events and generates a stream of
/// commands that it forwards onto a Camera instance.
////////////////////////////////////////////////////////////////////////////////

#ifndef _NOONCRAFT_CAMERA_CONTROLLER_H_
#define _NOONCRAFT_CAMERA_CONTROLLER_H_

#include "Camera.hpp"
#include "EventObserver.hpp"
#include "InputManager.hpp"

class CameraController : public EventObserver
{
public:
    CameraController(Camera *camera);
    void registerWith(InputManager *manager);
    virtual void onEvent(ApplicationEventStruct event);
private:
    Camera *mpCamera;

    CameraController(void) = delete;
};

#endif
