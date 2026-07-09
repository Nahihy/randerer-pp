#version 330 core

in vec2 texCoord;

uniform sampler2D tex;
uniform sampler2D tex2;

void main() {
  gl_FragColor = mix(texture(tex, texCoord), texture(tex2, texCoord), 0.2f);
}
