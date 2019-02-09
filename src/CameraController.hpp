////////////////////////////////////////////////////////////////////////////////
/// @file CameraController.hpp
/// @brief A class that generates camera commands from events.
///
/// This class listens for applicable camera events and generates a stream of
/// commands that it forwards onto a Camera instance.
////////////////////////////////////////////////////////////////////////////////

#ifndef _NOONCRAFT_CAMERA_CONTROLLER_H_
#define _NOONCRAFT_CAMERA_CONTROLLER_H_

#include <vector>

#include "Camera.hpp"
#include "EventObserver.hpp"
#include "InputManager.hpp"

class CameraController : public EventObserver
{
public:
    CameraController(Camera *camera);
    void registerWith(InputManager *manager);
    virtual void onEvent(ApplicationEventStruct event);
    void update(void);
private:
    Camera *mpCamera;
    std::vector<ApplicationEventType> mEventStates;
    ApplicationEventDataStruct mCursorData;
    ApplicationEventDataStruct mPrevCursorData;

    void updatePosition(void);
    void updateFacing(void);

    CameraController(void) = delete;
};

#endif
