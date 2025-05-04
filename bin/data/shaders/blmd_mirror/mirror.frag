#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 uResolution;
uniform sampler2D uTexture;
uniform vec2 uScale;

in vec2 vTexCoord;
out vec4 outputColor;

void main() {
    vec2 uv = gl_FragCoord.xy / uResolution.xy;
    // vec2 uv = vTexCoord;
    uv.y = 1.0 - uv.y;
    
    vec2 wiggle = sin(uv * uScale) * 0.02;
    vec4 color = texture(uTexture, uv + wiggle);
  
    outputColor = color;
}


