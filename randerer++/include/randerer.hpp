#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../src/shader.hpp"
#include "../src/texture.hpp"
#include "../src/bufferSet.hpp"
#include "../src/window.hpp"
#include "../src/sprite.hpp"


int initWindowSystem() {

  if(!glfwInit()) {
    std::cout << "Failed to initialize GLFW\n";
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  return 0;

}

int initGraphicSystem() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  return 0;
}
