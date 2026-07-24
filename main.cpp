
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/fwd.hpp"
#include "mesh.hpp"

#include "camera.hpp"

#include <iostream>
#include <vector>

void processInput(GLFWwindow *window);


using namespace rndr;
using namespace tdf;

Camera camera(glm::vec3(0.5f, 0.0f, 5.0f));


int main() {

  initWindowSystem();

  Window window("model", 600, 800);

  window.makeCurrent();
  window.setAutoResizeFrameBufferSAVERATIO();
  window.setScollOffsetCallback([](GLFWwindow* window, double xoffset, double yoffset)
                                {camera.processMouseScroll(static_cast<float>(yoffset));});
  window.setAutoOffsetCalcMouseCallback([](GLFWwindow* window, double xoffset, double yoffset)
                                        {camera.processMouseMovement(xoffset, yoffset);});

  glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


  initGraphicSystem();
  
  glEnable(GL_DEPTH_TEST);

  std::vector<float> bgVertices = {
    -1.0f,  1.0f,
     1.0f,  1.0f,
    -1.0f, -1.0f,
     1.0f, -1.0f
  };

  std::vector<unsigned int> bgIndices = {
    0, 1, 2,
    1, 2, 3
  };

  std::vector<VertexAttrib> bgAttribs = {
    {0, 2, 2 * sizeof(float), 0}
  };

  Sprite bgSprite(Shader("shaders/background/vertex.glsl", "shaders/background/fragment.glsl"),
                  BufferSet(bgVertices, bgIndices, bgAttribs), {});


  Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

  Model model("textures/backpack/backpack.obj");


  shader.setFloat("material.shininess", 32.0f);

  while (!window.shouldClose()) {
    window.updateDeltaTime();
    processInput(window.glfwWindow);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    bgSprite.draw();
    glEnable(GL_DEPTH_TEST);

    glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)window.width / (float)window.height, 0.1f, 100.0f);
    glm::mat4 view = camera.getViewMatrix();

    shader.bind();

    shader.setVec3NOBIND("spotLight.position", camera.position);
    shader.setVec3NOBIND("spotLight.direction", camera.front);
    shader.setVec3NOBIND("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    shader.setVec3NOBIND("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    shader.setVec3NOBIND("spotLight.specular", 1.0f, 1.0f, 1.0f);
    shader.setFloatNOBIND("spotLight.constant", 1.0f);
    shader.setFloatNOBIND("spotLight.linear", 0.09f);
    shader.setFloatNOBIND("spotLight.quadratic", 0.032f);
    shader.setFloatNOBIND("spotLight.cutOff", glm::cos(glm::radians(22.5f)));
    shader.setFloatNOBIND("spotLight.outerCutOff", glm::cos(glm::radians(25.0f))); 

    shader.setMat4NOBIND("projection", projection);
    shader.setMat4NOBIND("view", view);
    glm::mat4 modell = glm::mat4(1.0f);
    modell = glm::translate(modell, glm::vec3(0.0f, 0.0f, 0.0f));
    modell = glm::scale(modell, glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setMat4NOBIND("model", modell);

    model.Draw(shader);


    window.swapAndPollEvents();

  }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
  Window* windowClass = (Window*)glfwGetWindowUserPointer(window);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.processKeyboard(FORWARD, windowClass->deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.processKeyboard(BACKWARD, windowClass->deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.processKeyboard(LEFT, windowClass->deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.processKeyboard(RIGHT, windowClass->deltaTime);
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    camera.processKeyboard(UP, windowClass->deltaTime);
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    camera.processKeyboard(DOWN, windowClass->deltaTime);

}
