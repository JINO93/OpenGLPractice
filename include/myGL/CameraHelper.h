#ifndef _CAMERAHELPER_H
#define _CAMERAHELPER_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
    class CameraHelper
    {
    public:
        float fov;
        glm::vec3 camPos;
        glm::vec3 frontPos;
        glm::vec3 upPos;
        float camSpeed = 0.005f;

        bool firstMouseMove = true;
        float moveSensitivity = 0.05f;
        float lastX = 0;
        float lastY = 0;
        float yaw = -90.0f;
        float pitch = 0.0f;

        CameraHelper(glm::vec3 _camPos = glm::vec3(0.0, 0.0, 3.0),glm::vec3 _frontPos = glm::vec3(0.0, 0.0, -1.0),glm::vec3 _upPos = glm::vec3(0.0, 1.0, 0.0)){
            camPos = _camPos;
            frontPos = _frontPos;
            upPos = _upPos;
        }
    };

#ifdef __cplusplus
}
#endif
#endif // _CAMERAHELPER_H