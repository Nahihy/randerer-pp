#pragma once

#include "bufferSet.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "bufferSet.hpp"

#include <initializer_list>
#include <vector>

class Sprite {

  public:
    std::vector<Texture> textures;
    Shader shader;
    BufferSet bufferSet;


    Sprite(Shader shader, BufferSet bufferSet = BufferSet(), std::initializer_list<Texture> textures = {})
    : shader(shader), bufferSet(bufferSet), textures(textures) {}

    void draw() const {
      this->shader.bind();
      for(const Texture& tex : this->textures) tex.bind();
      this->bufferSet.draw();
    }

    void drawNOBIND() const {
      this->bufferSet.drawNOBIND();
    }

    void bind() const {
      this->shader.bind();
      for(const Texture& tex : this->textures) tex.bind();
      this->bufferSet.bind();
    }

};
