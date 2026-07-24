#pragma once

#include "bufferSet.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "bufferSet.hpp"

#include <initializer_list>
#include <vector>

namespace rndr {

  class Sprite {

    public:
      std::vector<Texture> textures;
      rndr::Shader shader;
      rndr::BufferSet bufferSet;


      Sprite(rndr::Shader shader, rndr::BufferSet bufferSet = rndr::BufferSet(), std::initializer_list<Texture> textures = {})
      : shader(shader), bufferSet(bufferSet), textures(textures) {}

      void draw() const {
        this->shader.bind();
        for(const rndr::Texture& tex : this->textures) tex.bind();
        this->bufferSet.draw();
      }

      void drawNOBIND() const {
        this->bufferSet.drawNOBIND();
      }

      void bind() const {
        this->shader.bind();
        for(const rndr::Texture& tex : this->textures) tex.bind();
        this->bufferSet.bind();
      }

  };

}
