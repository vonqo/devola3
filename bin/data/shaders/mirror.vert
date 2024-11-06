#version 410

// attribute vec3 aPosition;
// attribute vec2 aTexCoord;
// This is a varying variable, which in shader terms means that it will be passed from the vertex shader to the fragment shader
// varying vec2 vTexCoord;

// in vec3 aPosition;
// in vec2 aTexCoord;
// // out vec2 vTexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;

in vec4 position;
// in vec4 color;
// in vec4 normal;
in vec2 texcoord;

// uniform vec2 vTexCoord;

// out Vertex {
//   vec4 normal;
//   vec4 color;
//   vec2 texCoord;
// } vertex;

out vec2 vTextCoord;

void main() {
  // Copy the texcoord attributes into the varying variable
  // vTexCoord = aTexCoord;
  
  // vec4 positionVec4 = vec4(aPosition, 1.0);
  // positionVec4.xy = positionVec4.xy * 2.0 - 1.0;
  // gl_Position = positionVec4;
  
  // varyingtexcoord = vTexCoord;
  // gl_Position = modelViewProjectionMatrix * position;

  vTextCoord = texcoord;
  gl_Position = position;
  // vertex.normal = normal;
  // vertex.color =  color;
  // vertex.texCoord = texcoord;
}
