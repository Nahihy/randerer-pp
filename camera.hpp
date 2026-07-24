#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  UP,
  DOWN
};

constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 45.0f;


class Camera {
  public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldup;
    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED),
           mouseSensitivity(SENSITIVITY), zoom(ZOOM), position(position), worldup(up),
          yaw(yaw), pitch(pitch) {updateCameraVectors();}

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
           front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM),
           position(glm::vec3(posX, posY, posZ)), worldup(glm::vec3(upX, upY, upZ)),
           yaw(yaw), pitch(pitch) {updateCameraVectors();}

    glm::mat4 getViewMatrix() {
      return glm::lookAt(position, position + front, up);
    }

    void processKeyboard(Camera_Movement direction, float deltaTime) {
      float velocity = movementSpeed * deltaTime;
      if (direction == FORWARD)
        position += front * velocity;
      if (direction == BACKWARD)
        position -= front * velocity;
      if (direction == LEFT)
        position -= right * velocity;
      if (direction == RIGHT)
        position += right * velocity;
      if (direction == UP)
        position += up * velocity;
      if (direction == DOWN)
        position -= up * velocity;

    }

    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainpitch = true) {
      xoffset *= mouseSensitivity;
      yoffset *= mouseSensitivity;

      yaw   += xoffset;
      pitch += yoffset;

      if (constrainpitch) {
        if (pitch > 89.0f)
          pitch = 89.0f;
        if (pitch < -89.0f)
          pitch = -89.0f;
      }

      updateCameraVectors();
    }

    void processMouseScroll(float yoffset) {
      zoom -= (float)yoffset;
      if (zoom < 1.0f)
        zoom = 1.0f;
      if (zoom > 45.0f)
        zoom = 45.0f;
    }

  private:
    void updateCameraVectors() {
      glm::vec3 front;
      front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
      front.y = sin(glm::radians(pitch));
      front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
      this->front = glm::normalize(front);
      this->right = glm::normalize(glm::cross(front, worldup));
      this->up = glm::normalize(glm::cross(right, front));
    }
};
