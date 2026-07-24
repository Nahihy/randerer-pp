// showcase for the randerer++ lib

#include <randerer.hpp>
#include <vector>


int main() {
  // init the window system (init glfw), create a window and call makeCurrent, only after init graphic system (init glad)
  rndr::initWindowSystem();

  rndr::Window window("lib showcase", 600, 800);
  window.makeCurrent();
  // also set callbacks, one to auto resize the framebuffer (with keeping the ratio or not),
  // one for mouse movement that calcs the offset automaticly, one for scrolling etc.
  // DO NOT SET WINDOW USER POINTER AFTER SETTING ONE OF THOSE FUNCTIONS
  window.setAutoResizeFrameBufferSAVERATIO();

  rndr::initGraphicSystem();

  // setup a sprite with it's shaders, buffers and optionaly textures 
  std::vector<float> vertices = {
    -0.5f,  0.5f,  0.0f, 1.0f,
     0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  1.0f, 0.0f
  };

  std::vector<unsigned int> indices = {
    0, 1, 2,
    1, 2, 3
  };

  std::vector<rndr::VertexAttrib> attribs = {
    {0, 2, 4 * sizeof(float), 0},
    {1, 2, 4 * sizeof(float), 2 * sizeof(float)}
  };


  rndr::Sprite sprite(rndr::Shader("shaders/showcase/vertex.glsl", "shaders/showcase/fragment.glsl"),
                      rndr::BufferSet(vertices, indices, attribs), 
                      {rndr::Texture("textures/container.jpg", GL_TEXTURE0, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST)});

  // set uniform for textures, set render loop and draw the sprite
  sprite.shader.setInt("tex", 0);

  while(!window.shouldClose()) {

    sprite.draw();

    window.swapAndPollEvents();
  }
  // close the randerer system afterwords
  rndr::closeRandererSystem();
  return 0;
}
