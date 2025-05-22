#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 resolution;
uniform sampler2D texture1;
uniform vec2 scale;

in vec2 vTexCoord;
out vec4 outputColor;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    uv.y = 1.0 - uv.y;
    vec2 ww = uv * scale;
    vec2 wiggle = (cos(ww+(scale * 0.2))) * 0.02;
    vec4 color = texture(texture1, uv + wiggle);
    
    outputColor = color;
}


