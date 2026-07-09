#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>

class Texture {

  private:
    unsigned int ID;

  public:
    GLenum unit;
    std::string texFile;
    GLenum colorType;
    GLenum texWrap;
    GLenum minFilter;
    GLenum maxFilter;

    Texture(std::string texFile, GLenum colorType = GL_RGB, GLenum unit = GL_TEXTURE0,
            GLenum texWrap = GL_NEAREST, GLenum minFilter = GL_LINEAR_MIPMAP_LINEAR, GLenum maxFilter = GL_NEAREST)
            : texFile(texFile), colorType(colorType), unit(unit), texWrap(texWrap), minFilter(minFilter), maxFilter(maxFilter) {
      glGenTextures(1, &this->ID);
      glActiveTexture(this->unit);
      glBindTexture(GL_TEXTURE_2D, this->ID); 
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->texWrap);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->texWrap);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->minFilter);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->maxFilter);
      int width, height, nrChannels;
      stbi_set_flip_vertically_on_load(true);
      unsigned char *data = stbi_load(this->texFile.c_str(), &width, &height, &nrChannels, 0);
      if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, this->colorType, width, height, 0, this->colorType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
      } else std::cout << "Failed to load texture: " << this->texFile << std::endl;
      stbi_image_free(data);
    }

    ~Texture() {
      glDeleteTextures(1, &this->ID);
    }

    Texture(const Texture& other) noexcept 
    : Texture(other.texFile, other.colorType, other.unit, other.texWrap, other.minFilter, other.maxFilter) {}

    Texture& operator=(const Texture& other) noexcept {

      if(this == &other) return *this;

      this->unit = other.unit;
      this->texFile = other.texFile;
      this->texWrap = other.texWrap;
      this->colorType = other.colorType;
      this->maxFilter = other.maxFilter;
      this->minFilter = other.minFilter;

      glGenTextures(1, &this->ID);
      glActiveTexture(this->unit);
      glBindTexture(GL_TEXTURE_2D, this->ID); 
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->texWrap);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->texWrap);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->minFilter);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->maxFilter);
      int width, height, nrChannels;
      stbi_set_flip_vertically_on_load(true);
      unsigned char *data = stbi_load(this->texFile.c_str(), &width, &height, &nrChannels, 0);
      if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, this->colorType, width, height, 0, this->colorType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
      } else std::cout << "Failed to load texture: " << this->texFile << std::endl;
      stbi_image_free(data);

      return *this;
    }

    Texture(Texture&& other) noexcept  
      : ID(other.ID), unit(other.unit), texFile(other.texFile) {
      other.ID = 0;
    }

    Texture& operator=(Texture&& other) noexcept {
      if (this != &other) {
        glDeleteTextures(1, &this->ID);
        ID = other.ID;
        unit = other.unit;
        texFile = other.texFile;
        other.ID = 0;
      }
      return *this;
    }

    void bind() const {
      glActiveTexture(this->unit);
      glBindTexture(GL_TEXTURE_2D, this->ID);
    }

    
    


};
