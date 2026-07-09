// based on learnopengl.com guild. probably the best one I've seen.


#include <randerer.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"

#include <iostream>

void processInput(GLFWwindow *window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main() {

  initWindowSystem();

  Window window("window", 600, 800);
  
  window.makeCurrent();

  initGraphicSystem();

  glfwSetWindowUserPointer(window.glfwWindow, &window);
  window.setAutoResizeFrameBufferSAVERATIO();
  window.setAutoOffsetCalcMouseCallback([](GLFWwindow* window, double xoffset, double yoffset)
                                        {camera.ProcessMouseMovement(xoffset, yoffset);});
  window.setScollOffsetCallback([](GLFWwindow* window, double xoffset, double yoffset)
                                        {camera.ProcessMouseScroll(yoffset);});
  glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

  float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };

  VertexAttrib attrib[] = {
    {0, 3, 5 * sizeof(float), 0},
    {1, 2, 5 * sizeof(float), 3 * sizeof(float)}
  };

  Sprite sprite(Shader("shaders/vertex.glsl", "shaders/fragment.glsl"),
                BufferSet(vertices, sizeof(vertices) / sizeof(float), nullptr, -1, attrib, sizeof(attrib) / sizeof(VertexAttrib)),
                {Texture("textures/container.jpg", GL_RGB, GL_TEXTURE0),
                Texture("textures/awesomeface.png", GL_RGBA, GL_TEXTURE1)});

  float bgVertices[] = {
   -1.0f,  1.0f,
    1.0f,  1.0f,
   -1.0f, -1.0f,
    1.0f, -1.0f
  };

  unsigned int bgIndices[] = {
    0, 1, 2,
    1, 2, 3
  };

  VertexAttrib bgAttrib[] = {
    {0, 2, 2 * sizeof(float), 0}
  };

  Sprite bgSprite(Shader("shaders/background/vertex.glsl", "shaders/background/fragment.glsl"),
                  BufferSet(bgVertices, 8, bgIndices, 6, bgAttrib, 1));

  sprite.shader.bind();
  sprite.shader.setInt("tex", 0);
  sprite.shader.setInt("tex2", 1);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  sprite.shader.bind();
  sprite.shader.setMat4("model", model);

  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
  };
  
  while(!window.shouldClose()) {

    window.updateDeltaTime();

    processInput(window.glfwWindow);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glDisable(GL_DEPTH_TEST);
    bgSprite.draw();

    glEnable(GL_DEPTH_TEST);

    sprite.bind();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)window.width / (float)window.height, 0.1f, 100.0f);
    sprite.shader.setMat4("projection", projection);

    glm::mat4 view = camera.GetViewMatrix();
    sprite.shader.setMat4("view", view);

    for(unsigned int i = 0; i < 10; i++) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i; 
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      sprite.shader.setMat4("model", model);
      sprite.drawNOBIND();
    }

    window.swapAndPollEvents();
  }


  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  Window* windowClass = (Window*)glfwGetWindowUserPointer(window);
  const float cameraSpeed = 2.5f * windowClass->deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, windowClass->deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, windowClass->deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, windowClass->deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, windowClass->deltaTime);
}

