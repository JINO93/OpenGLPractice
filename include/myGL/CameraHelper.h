#ifndef _CAMERAHELPER_H
#define _CAMERAHELPER_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

    enum Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class CameraHelper
    {
    public:
        float fov = 45.0f;
        glm::vec3 camPos;
        glm::vec3 frontPos;
        glm::vec3 upPos;
        glm::vec3 right;
        float camSpeed = 0.05f;

        float moveSensitivity = 2.5f;
        float yaw = -90.0f;
        float pitch = 0.0f;

        CameraHelper(glm::vec3 _camPos = glm::vec3(0.0, 0.0, 3.0), glm::vec3 _frontPos = glm::vec3(0.0, 0.0, -1.0), glm::vec3 _upPos = glm::vec3(0.0, 1.0, 0.0))
        {
            camPos = _camPos;
            frontPos = _frontPos;
            upPos = _upPos;

            updataMatrix();
        }

        void handleKeyboardEvent(Camera_Movement direction,float deltaTime){
            std::cout << "d:" << direction << " dT:" << deltaTime << std::endl;
            float velocity = moveSensitivity * deltaTime;
            if (direction == FORWARD)
                camPos += frontPos * velocity;
            if (direction == BACKWARD)
                camPos -= frontPos * velocity;
            if (direction == LEFT)
                camPos -= right * velocity;
            if (direction == RIGHT)
                camPos += right * velocity;

            updataMatrix();
        }

        void onMove(float offsetX, float offsetY)
        {
            pitch += offsetY * camSpeed;
            yaw += offsetX * camSpeed;
            std::cout << "p:" << pitch << " y:" << yaw<<std::endl;

            if (pitch > 89.0f)
            {
                pitch = 89.0f;
            }
            else if (pitch < -89.0f)
            {
                pitch = -89.0f;
            }

            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            frontPos = glm::normalize(front);
            updataMatrix();
        }

        void onScroll(double xoffset, double yoffset)
        {
            fov += yoffset * 1.0f;
            if (fov > 90.0f)
            {
                fov = 90.0f;
            }
            else if (fov < 12.0f)
            {
                fov = 12.0f;
            }
            updataMatrix();
        }

        glm::mat4 getViewMatrix()
        {
            return view;
        }

        glm::mat4 getProjectionMatrix()
        {
            return projection;
        }

    private:
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        void updataMatrix()
        {
            right = glm::normalize(glm::cross(frontPos,upPos));
            view = glm::lookAt(camPos, camPos + frontPos, upPos);
            projection = glm::perspective(glm::radians(fov), 1.33f, 0.2f, 100.0f);
        }
    };

#ifdef __cplusplus
}
#endif
#endif // _CAMERAHELPER_H