#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 uResolution;
uniform float uTime;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float speed;
uniform float iteration;

in vec2 vTexCoord;
out vec4 outputColor;

#define PI 3.1415926

const float it = 5.0; // Number of iterations

vec2 rotate(vec2 pos, float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return mat2(c, s, -s, c) * pos;
}

void main()
{
    outputColor = vec4(0);
    float mx = max(uResolution.x, uResolution.y);
   
    vec2 uv = gl_FragCoord.xy / min(uResolution.x,uResolution.y);
    uv.x -= 0.40;
    
	vec2 q= gl_FragCoord.xy / uResolution.xy;
   
    float t=uTime;
	   
    // let's rotate ... 2D! gtr
    uv = rotate( uv*2.-1.,sin(t/4.));
    // if(iMouse.z>0.)  uv = rotate( uv*2.-1.,1.);
	
	float v = pow(3.0,it)+10.0;

	for (float i = 0.0; i < it; i++)
	{
		if(floor(mod(uv.x*v,3.0))==1.0 && floor(mod(uv.y*v,3.0))==1.0){
            // Fabrice..     
            outputColor = vec4(sin(i*uv.y-t*0.5+vec4(3,4,5,0)*PI/3.)+1.);
            outputColor *= vec4(texture(texture1,uv).xyz,1.0)*1.;
        }
		v/=3.0;	
		uv.x =uv.x+speed;// let's scrolling gtr 
       
	}
    
    outputColor *= vec4(texture(texture2,q).xyz,1.0);
}
