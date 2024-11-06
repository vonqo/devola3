// precision mediump float;
#version 410

// varying vec2 vTexCoord;

uniform sampler2DRect uTexture;
uniform vec2 uScale;

in vec2 vTexCoord;
out vec4 outColor;

void main() {
  vec2 uv = vTexCoord;
  uv.y = 1.0 - uv.y;
  vec2 wiggle = sin(uv * uScale) * 0.02;
  vec4 color = texture(uTexture, uv + wiggle);
  
  // vec4 color = vec4(0.2, 1.0, 0.2, 0.5);
  // Send the color to the screen
  // gl_FragColor = color;
  outColor = color;
}
