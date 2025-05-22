// Fork of "Pale Silk" by R3N. https://shadertoy.com/view/NdVXDw
// 2022-11-24 01:10:01

// Updated have more configuration and add photoshop blend modes on existing textures
// Description : Array and textureless GLSL 2D/3D/4D simplex 
//               noise functions.
//      Author : Ian McEwan, Ashima Arts.
//  Maintainer : ijm
//     Lastmod : 20151020 (hassoncs)
//     License : Copyright (C) 2011 Ashima Arts. All rights reserved.
//               Distributed under the MIT License. See LICENSE file.
//               https://github.com/ashima/webgl-noise
// 
//    Modified : vonqo (2025-05-20)

#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texture1;
uniform vec2 resolution;
uniform float time;
in vec2 vTexCoord;
out vec4 outputColor;

const float noiseSizeCoeff = 0.61; // Bigger => larger glitter spots
const float noiseDensity = 53.0;  // Bigger => larger glitter spots

vec3 mod289(vec3 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 mod289(vec4 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x) {
     return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
  return 1.79284291400159 - 0.85373472095314 * r;
}

float snoise(vec3 v)
  { 
  const vec2  C = vec2(1.0/6.0, 1.0/3.0) ;
  const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);

  // First corner
  vec3 i  = floor(v + dot(v, C.yyy) );
  vec3 x0 =   v - i + dot(i, C.xxx) ;

  // Other corners
  vec3 g = step(x0.yzx, x0.xyz);
  vec3 l = 1.0 - g;
  vec3 i1 = min( g.xyz, l.zxy );
  vec3 i2 = max( g.xyz, l.zxy );

  //   x0 = x0 - 0.0 + 0.0 * C.xxx;
  //   x1 = x0 - i1  + 1.0 * C.xxx;
  //   x2 = x0 - i2  + 2.0 * C.xxx;
  //   x3 = x0 - 1.0 + 3.0 * C.xxx;
  vec3 x1 = x0 - i1 + C.xxx;
  vec3 x2 = x0 - i2 + C.yyy; // 2.0*C.x = 1/3 = C.y
  vec3 x3 = x0 - D.yyy;      // -1.0+3.0*C.x = -0.5 = -D.y

  // Permutations
  i = mod289(i); 
  vec4 p = permute( permute( permute( 
             i.z + vec4(0.0, i1.z, i2.z, 1.0 ))
           + i.y + vec4(0.0, i1.y, i2.y, 1.0 )) 
           + i.x + vec4(0.0, i1.x, i2.x, 1.0 ));

  // Gradients: 7x7 points over a square, mapped onto an octahedron.
  // The ring size 17*17 = 289 is close to a multiple of 49 (49*6 = 294)
  float n_ = 0.142857142857; // 1.0/7.0
  vec3  ns = n_ * D.wyz - D.xzx;

  vec4 j = p - 49.0 * floor(p * ns.z * ns.z);  //  mod(p,7*7)

  vec4 x_ = floor(j * ns.z);
  vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)

  vec4 x = x_ *ns.x + ns.yyyy;
  vec4 y = y_ *ns.x + ns.yyyy;
  vec4 h = 1.0 - abs(x) - abs(y);

  vec4 b0 = vec4( x.xy, y.xy );
  vec4 b1 = vec4( x.zw, y.zw );

  vec4 s0 = floor(b0)*2.0 + 1.0;
  vec4 s1 = floor(b1)*2.0 + 1.0;
  vec4 sh = -step(h, vec4(0.0));

  vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
  vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;

  vec3 p0 = vec3(a0.xy,h.x);
  vec3 p1 = vec3(a0.zw,h.y);
  vec3 p2 = vec3(a1.xy,h.z);
  vec3 p3 = vec3(a1.zw,h.w);

  // Normalise gradients
  vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
  p0 *= norm.x;
  p1 *= norm.y;
  p2 *= norm.z;
  p3 *= norm.w;

  // Mix final noise value
  vec4 m = max(noiseSizeCoeff - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);
  m = m * m;
  return noiseDensity * dot( m*m, vec4( dot(p0,x0), dot(p1,x1), 
                                dot(p2,x2), dot(p3,x3) ) );
}


float softLight( float s, float d )
{
	return (s < 0.5) ? d - (1.0 - 2.0 * s) * d * (1.0 - d) 
		: (d < 0.25) ? d + (2.0 * s - 1.0) * d * ((16.0 * d - 12.0) * d + 3.0) 
					 : d + (2.0 * s - 1.0) * (sqrt(d) - d);
}

vec3 softLight( vec3 s, vec3 d )
{
	vec3 c;
	c.x = softLight(s.x,d.x);
	c.y = softLight(s.y,d.y);
	c.z = softLight(s.z,d.z);
	return c;
}

float hardLight( float s, float d )
{
	return (s < 0.5) ? 2.0 * s * d : 1.0 - 2.0 * (1.0 - s) * (1.0 - d);
}

vec3 hardLight( vec3 s, vec3 d )
{
	vec3 c;
	c.x = hardLight(s.x,d.x);
	c.y = hardLight(s.y,d.y);
	c.z = hardLight(s.z,d.z);
	return c;
}

float vividLight( float s, float d )
{
	return (s < 0.5) ? 1.0 - (1.0 - d) / (2.0 * s) : d / (2.0 * (1.0 - s));
}

vec3 vividLight( vec3 s, vec3 d )
{
	vec3 c;
	c.x = vividLight(s.x,d.x);
	c.y = vividLight(s.y,d.y);
	c.z = vividLight(s.z,d.z);
	return c;
}

vec3 linearLight( vec3 s, vec3 d )
{
	return 2.0 * s + d - 1.0;
}

float pinLight( float s, float d )
{
	return (2.0 * s - 1.0 > d) ? 2.0 * s - 1.0 : (s < 0.5 * d) ? 2.0 * s : d;
}

vec3 pinLight( vec3 s, vec3 d )
{
	vec3 c;
	c.x = pinLight(s.x,d.x);
	c.y = pinLight(s.y,d.y);
	c.z = pinLight(s.z,d.z);
	return c;
}

float vignette(vec2 uv) {
    uv *=  1.0 - uv.yx;   //vec2(1.0)- uv.yx; -> 1.-u.yx; Thanks FabriceNeyret !
    
    float vig = uv.x*uv.y * 15.0; // multiply with sth for intensity
    
    vig = pow(vig, 0.1); // change pow for modifying the extend of the  vignette
    return vig;
}

// Convert RGB to HSL
vec3 rgb2hsl(vec3 rgb) {
    float maxVal = max(max(rgb.r, rgb.g), rgb.b);
    float minVal = min(min(rgb.r, rgb.g), rgb.b);
    float delta = maxVal - minVal;
    
    float h = 0.0;
    float s = 0.0;
    float l = (maxVal + minVal) * 0.5;
    
    if (delta > 0.0) {
        s = (l < 0.5) ? delta / (maxVal + minVal) : delta / (2.0 - maxVal - minVal);
        
        if (maxVal == rgb.r) {
            h = (rgb.g - rgb.b) / delta + (rgb.g < rgb.b ? 6.0 : 0.0);
        } else if (maxVal == rgb.g) {
            h = (rgb.b - rgb.r) / delta + 2.0;
        } else {
            h = (rgb.r - rgb.g) / delta + 4.0;
        }
        h /= 6.0;
    }
    
    return vec3(h, s, l);
}

// Helper function for HSL to RGB conversion
float hue2rgb(float p, float q, float t) {
    if (t < 0.0) t += 1.0;
    if (t > 1.0) t -= 1.0;
    if (t < 1.0/6.0) return p + (q - p) * 6.0 * t;
    if (t < 1.0/2.0) return q;
    if (t < 2.0/3.0) return p + (q - p) * (2.0/3.0 - t) * 6.0;
    return p;
}

// Convert HSL to RGB
vec3 hsl2rgb(vec3 hsl) {
    float h = hsl.x;
    float s = hsl.y;
    float l = hsl.z;
    
    if (s == 0.0) {
        return vec3(l); // achromatic
    }
    
    float q = (l < 0.5) ? l * (1.0 + s) : l + s - l * s;
    float p = 2.0 * l - q;
    
    float r = hue2rgb(p, q, h + 1.0/3.0);
    float g = hue2rgb(p, q, h);
    float b = hue2rgb(p, q, h - 1.0/3.0);
    
    return vec3(r, g, b);
}


void main()
{
    vec2 uv = gl_FragCoord.xy/resolution.y;
    float t = 0.5*time;
	  uv.y += 0.03*sin(9.0*uv.x-(t*1.5));
    vec4 txt = texture(texture1, uv * vec2(0.5,1));
    
    // add colorize to texture
    float lg = 0.5f; // lightness
    float st = 0.9f; // saturation
    float hue = 0.13f; // hue

    float lume = dot(txt.rgb, vec3(0.299, 0.587, 0.114));
    float adjustedLume = clamp(lume + lg, 0.0, 1.0);
    vec3 hsl = vec3(hue, st, adjustedLume);
    vec3 colorizedTexture = hsl2rgb(hsl);
    txt = vec4(colorizedTexture, txt.a);

    // add saturation to texture
    float saturation = 0.32f;
    vec3 weights_ = vec3(0.2125, 0.7154, 0.0721); // sums to 1
    float luminance_ = dot(txt.rgb, weights_);
    txt = mix(vec4(luminance_), txt, vec4(saturation) * 5.);

    // add contrast to texture
    float contrast = 0.8;
    txt = (txt - .5) * contrast * 2. + .5; // 0 to 2 contrast
    
    float f = 0.6+0.4*sin(5.0*(uv.x+uv.y+cos(3.0*uv.x+5.0*uv.y)+0.02*t)+sin(20.0*(uv.x+uv.y-0.1*t)));
    float b = 1.8;
    // outputColor = vec4(0.3988235294*b, 0.324901961*b, 0.0149019608*b, 1.)*vec4(f);
    outputColor = vec4(0.475 * b, 0.4 * b, 0.11 * b, 1.0)*vec4(f);

    uv = gl_FragCoord.xy / resolution.xy;
    float vig = vignette(uv);
 
    float fadeLR = .7 - abs(uv.x - .4);
    float fadeTB = 1.1 - uv.y;
    vec3 pos = vec3(uv * vec2( 3. , 1.) - vec2(0., time * .00005), time * .006);
   
    float n = fadeLR * fadeTB * smoothstep(.50, 1.2, snoise(pos * resolution.y / 10.)) * 8.;
  
    // a bunch of constants here to shift the black-white of the noise to a greyer tone
    vec3 noiseGreyShifted = min((vec3(n) + 1.) / 3. + .3, vec3(1.)) * .91;
    
    vec3 mixed = outputColor.xyz;
    // mixed = softLight(noiseGreyShifted, s);
    mixed = mix(outputColor.xyz, hardLight(noiseGreyShifted, outputColor.xyz), .2);
    // mixed = mix(outputColor.xyz, vividLight(noiseGreyShifted, outputColor.xyz), .02);
    mixed = mix(mixed, txt.xyz, 0.6);
    // mixed = pinLight(noiseGreyShifted, outputColor.xyz);
    // mixed = linearLight(noiseGreyShifted, s);
    
	  outputColor = vec4(mixed, 1.0) * vig;
    
    // float k = (sin(time / 1.0) + 1.0)/2.0 + 0.55;
   
    // #define heartoffset vec2(sin(uv.x + time)*10., cos(uv.x * 10. + 0.01*sin(time) + time)*15.*(1.5-uv.y)*0.4)
    // #define heartcoord fract(((fragCoord.xy + heartoffset) - resolution.xy/2.) / cellsize)
    
    //vec3 outputColor = vec3(0.2588235294, 0.1254901961, 0.2549019608);
    // Add a bit of shading to make things seem more 3-dimensional
    // outputColor -= (heartoffset.y + heartoffset.x) * 0.01 * k * (1.-uv.y)*0.4;
    // outputColor -= vec4((1.-uv.y)*0.1*k,0,0,1.);
    // outputColor -= (vec4(uv.y, uv.y * 0.8, uv.y, 1.)) / 8.0;
}