attribute vec3 aPosition;
attribute vec2 aTexCoord;
// This is a varying variable, which in shader terms means that it will be passed from the vertex shader to the fragment shader
varying vec2 vTexCoord;
void main() {
  // Copy the texcoord attributes into the varying variable
  vTexCoord = aTexCoord;
   
  vec4 positionVec4 = vec4(aPosition, 1.0);
  positionVec4.xy = positionVec4.xy * 2.0 - 1.0;
  gl_Position = positionVec4;
}
